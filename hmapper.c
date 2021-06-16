#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DEFAULT_CAPACITY 10
#define DEFAULT_LOAD_FACTOR 1.0
#define MAX_ARGS 3
#define MAX_LINE_LENGTH 1002
#define BUFFER 2

void printHelp()
{
    printf("\nUsage: ./hmapper [OPTION(S)] [FILE]\n\n");
    printf("Reads from an optional [FILE], or stdin by default, to convert each line\n");
    printf("into a key for a hash map with value equal to the line number. After each line\n");
    printf("it will print the key value pair.\n");
    printf("When a line is repeats, it will print its previous line number.\n");
    printf("Lines of input greater than 1000 characters are not accepted.\n\n");
    printf("Options: \n");
    printf("\t-h\tprints the help page and exits.\n\n");
    printf("Press Ctrl+D on an empty line to exit.\n");
}

struct chain_link
{
    char *val;
    char *key;
    struct chain_link *next; //owned
};

//Takes in a key and a value and returns a pointer to a new
//chain link with thoes values
struct chain_link *make_root_chain(char key_val[], char val[])
{
    struct chain_link *result = malloc(sizeof(struct chain_link));
    //printf("allocated a chain_link in make_root_chain\n");
    result->val = malloc(sizeof(char) * (strlen(val) + 1));
    strcpy(result->val, val);
    result->key = malloc(sizeof(char) * (strlen(key_val) + 1));
    strcpy(result->key, key_val);
    result->next = NULL;
    return result;
}

//Takes in a chain link pointer, a key, and a value and inserts a new
//chain link between the next chain link from base and base with that
//key and value.
//Returns 0 on a successful insert
//Returns -1 if you insert onto a node that doesn't exist.
int insert_next(struct chain_link *base, char key[], char ins_val[])
{
    struct chain_link *conn = make_root_chain(key, ins_val);
    if (!base)
    {
        printf("ERROR: Tried to insert onto a node that didn't exist.\n");
        return -1;
    }
    if (base->next)
    {
        struct chain_link *old_link_cpy = base->next;
        free(base->next);
        //printf("freed a chain_link in insert\n");
        conn->next = old_link_cpy;
    }
    base->next = conn;
    return 0;
}

//Takes in a chain link pointer, a key, and a value and replaces the next
//chain link from base with a new chain link with that key and value. returns
//the value of the replaced node or NULL if the node or its next field is NULL
char *replace_next(struct chain_link *base, char key[], char ins_val[])
{
    char *ret = NULL;
    if (base && base->next)
    {
        struct chain_link *old_link_cpy = base->next->next;
        ret = base->next->val;
        free(base->next->key);
        //printf("freed a key in replace\n");
        free(base->next->val);
        //printf("freed a value in replace\n");
        free(base->next);
        //printf("freed a chain_link in replace\n");
        base->next = old_link_cpy;
    }
    insert_next(base, key, ins_val);
    return ret;
}

//Takes in a root chain link and removes the next node from the chain
//returns NULL if the node can't be torn and returns the value of the
//torn node otherwise.
char *tear_next(struct chain_link *base)
{
    if (!base || !base->next)
    {
        printf("ERROR: Tried to tear a node that didn't exist.\n");
        return NULL;
    }

    struct chain_link *old_link_cpy = NULL;
    memcpy(old_link_cpy, base->next, sizeof(struct chain_link));
    char *ret = old_link_cpy->next->val;
    free(base->next->key);
    //printf("freed a key in tear\n");
    free(base->next->val);
    //printf("freed a value in tear\n");
    free(base->next);
    //printf("freed a chain_link in tear\n");
    base->next = old_link_cpy->next;
    return ret;
}

struct hmap
{
    unsigned int size;
    unsigned int capacity;
    double load_factor;
    struct chain_link **data; //owned
};

//I need these declarations since I call one inside the other.
char *put(struct hmap *h, char *key, char *val);
void facor_resize(struct hmap *h, double factor);

// Transforms a string into a hash code (this is the java
// string hashing function)
unsigned int get_hash_code(char hashed[])
{
    unsigned int n = strlen(hashed);
    unsigned int hash_code = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        hash_code = 31 * hash_code + hashed[i];
    }
    return hash_code;
}

// Opens a map with a certain capacity.
struct hmap *map_open_with_capacity(unsigned int cap)
{
    unsigned int datasize = sizeof(struct chain_link);
    struct hmap *h = malloc(sizeof(struct hmap) + (cap * datasize));
    //printf("allocated a new hmap\n");
    h->size = 0;
    h->capacity = cap;
    h->data = malloc(cap * datasize);
    //printf("allocated the data for the hmap\n");
    for (unsigned int i = 0; i < cap; i++)
    {
        h->data[i] = NULL;
    }
    h->load_factor = DEFAULT_LOAD_FACTOR;
    return h;
}

// Opens an empty map with the default capacity
struct hmap *map_open()
{
    return map_open_with_capacity(DEFAULT_CAPACITY);
}

// Closes a map fully removing the data and the overhead.
void full_map_close(struct hmap *h)
{
    for (unsigned int i = 0; i < h->capacity; i++)
    {
        struct chain_link *root = h->data[i];
        while (root)
        {
            struct chain_link *temp = root;
            root = root->next;
            free(temp->key);
            free(temp->val);
            free(temp);
            //printf("freed a chain_link in full map close\n");
        }
        h->data[i] = NULL;
    }
    free(h->data);
    //printf("freed data in full map close\n");
    free(h);
    //rintf("freed a map in full map close\n");
}

//Takes a map and frees all the over head in it, but keeps the data.
void map_close(struct hmap *h)
{
    free(h->data);
    //printf("freed data in map close\n");
    free(h);
    //printf("freed a map in map close\n");
}

//Takes a map and frees all the data in it, but keeps the map.
void dump_data(struct hmap *h)
{
    for (unsigned int i = 0; i < h->capacity; i++)
    {
        struct chain_link *root = h->data[i];
        while (root)
        {
            struct chain_link *temp = root;
            root = root->next;
            free(temp->key);
            free(temp->val);
            free(temp);
            //printf("freed a chain_link in dump data\n");
        }
        h->data[i] = NULL;
    }
}

// Returns the size of a given map
int size(struct hmap *h)
{
    return h->size;
}

//Takes in a map and factor. Resizes the capacity of the map and rehashes
// its elements. Returns the pointer to the new map.
void factor_resize(struct hmap *h, double factor)
{
    unsigned int new_cap = (unsigned int)(((double)h->capacity * factor) + 0.5);
    struct hmap *new_map = map_open_with_capacity(new_cap);
    for (unsigned int i = 0; i < h->capacity; i++)
    {
        struct chain_link *root = h->data[i];
        while (root)
        {
            put(new_map, root->key, root->val);
            root = root->next;
        }
    }
    dump_data(h);
    h->data = realloc(h->data, new_cap * sizeof(struct chain_link));
    h->capacity = new_cap;
    //printf("reallocated data in factor resize\n");
    memcpy(h->data, new_map->data, new_cap * sizeof(struct chain_link));
    map_close(new_map);
}

//Returns a boolean value (i.e. 1 if true 0 if false) for whether a map
//contains a certain key
int contains_key(struct hmap *h, char key[])
{
    if (!h)
    {
        //printf("first return contains\n");
        return 0;
    }

    unsigned int hash = get_hash_code(key);
    unsigned int index = hash % h->capacity;

    if (!h->data[index])
    {
        //printf("second return contains\n");
        return 0;
    }
    struct chain_link *root = h->data[index];
    //printf("key given: %s\n", key);
    while (root)
    {
        //printf("key compared to: %s\n", root->key);
        //printf("strcmp: %d\n", strcmp(root->key, key));
        if (!strcmp(root->key, key))
        {
            return 1;
        }
        root = root->next;
    }
    //printf("third return contains\n");
    return 0;
}

//Takes in a map, a key, and a value and adds the key-value pair to
//the map. Returns the previous value of the key or -1 if nothing was
//assigned to that key before.
char *put(struct hmap *h, char *key, char *val)
{
    printf("put key %s, put val %s\n", key, val);
    if (!contains_key(h, key))
    {
        if ((((double)h->size + 1.0) / (double)h->capacity) > h->load_factor)
        {
            factor_resize(h, 2);
        }
    }

    h->size = h->size + 1;

    unsigned int hash = get_hash_code(key);
    unsigned int index = hash % h->capacity;
    char *ret = NULL;

    struct chain_link *root = h->data[index];
    if (root)
    {
        if (!strcmp(root->key, key))
        {
            ret = root->val;
            free(root->key);
            free(root->val);
            free(h->data[index]);
            h->data[index] = make_root_chain(key, val);
        }
        else
        {
            while (root->next && strcmp(root->next->key, key))
            {
                root = root->next;
            }

            ret = replace_next(root, key, val);
        }
    }
    else
    {
        h->data[index] = make_root_chain(key, val);
    }
    return ret;
}

char *get(struct hmap *h, char key[])
{
    if (!contains_key(h, key))
    {
        printf("ERROR: Tried to get a key-value pair that didn't exist.\n");
        return NULL;
    }

    unsigned int hash = get_hash_code(key);
    unsigned int index = hash % h->capacity;

    struct chain_link *root = h->data[index];
    while (root)
    {
        if (!strcmp(root->key, key))
        {
            return root->val;
        }
        root = root->next;
    }
    return NULL;
}

char *map_remove(struct hmap *h, char key[])
{
    if (!contains_key(h, key))
    {
        printf("ERROR: Tried to remove a key-value pair that didn't exist.\n");
        return NULL;
    }

    unsigned int hash = get_hash_code(key);
    unsigned int index = hash % h->capacity;

    struct chain_link *root = h->data[index];
    if (!strcmp(root->key, key))
    {
        char *ret = root->val;
        h->size = h->size - 1;
        free(root->key);
        free(root->val);
        free(h->data[index]);
        //printf("freed a chain_link in map remove\n");
        h->data[index] = NULL;
        return ret;
    }
    while (root->next)
    {
        if (!strcmp(root->next->key, key))
        {
            h->size = h->size - 1;
            return tear_next(root);
        }
        root = root->next;
    }
    return NULL;
}

char *strrev(char *revved, int nullplace)
{
    char *ret = malloc(nullplace + 1);
    for (int i = nullplace - 1; i >= 0; i--)
    {
        ret[nullplace - i - 1] = revved[i];
    }
    ret[nullplace] = '\0';
    return ret;
}

/**
int main()
{
    struct hmap *test = map_open();
    char *index_str[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    char *test_keys[5] = {"zero", "one", "two", "three", "four"};
    for (int i = 0; i < 5; i++)
    {
        put(test, test_keys[i], index_str[2 * i]);
        put(test, test_keys[i], index_str[2 * i + 1]);
        printf("key get:%d, %s\n", i, get(test, test_keys[i]));
    }
    full_map_close(test);
}
*/

int main(int argc, char *argv[])
{
    if (argc > MAX_ARGS)
    {
        printf("Please input less arguments.\n");
        printf("See \"./hmapper -h\" for more help\n");
        return -1;
    }

    char *rdfile = NULL;

    if (argc > 1)
    {
        char *options = argv[1];

        if (options[0] == '-' && strlen(options) > 1)
        {
            //Iterates through the possible argument options
            for (unsigned long i = 1; i < strlen(options); i++)
            {
                if (options[i] == 'h')
                {
                    printHelp();
                    return 0;
                }
                else
                {
                    printf("Unrecognized argument.\n");
                    printf("See \"./hmapper -h\" for more help\n");
                    return -1;
                }
            }
            if (argc > 2)
            {
                rdfile = argv[2];
            }
        }
        else
        {
            rdfile = argv[1];
        }
    }

    FILE *fp;
    if (rdfile)
    {
        fp = fopen(rdfile, "r");
        if (!fp)
        {
            printf("Could not open file %s\n", rdfile);
            printf("See \"./heapify.c -h\" for more help.\n");
            return 0;
        }
    }
    else
    {
        fp = stdin;
    }

    char currline[MAX_LINE_LENGTH];
    struct hmap *linemap = map_open();
    int c = 0;
    char int_str[MAX_LINE_LENGTH];

    while (fgets(currline, MAX_LINE_LENGTH, fp))
    {
        if (strlen(currline) > MAX_LINE_LENGTH - BUFFER)
        {
            printf("Sorry, hmapper doesn't accept line inputs greater than 1000 characters.\n");
            printf("See \"./hmapper -h\" for more help.\n");
            return -1;
        }
        int len = strlen(currline);
        if (currline[len - 1] == '\n')
        {
            currline[len - 1] = '\0';
        }
        if (!contains_key(linemap, currline))
        {
            c++;
            int track = 0;
            int d = c;
            while (d != 0)
            {
                int_str[track] = d % 10 + '0';
                track++;
                d = d / 10;
            }
            int_str[track] = '\0';
            char *rev = strrev(int_str, track);
            memcpy(int_str, rev, (track + 1) * sizeof(char));
            free(rev);
            put(linemap, currline, int_str);
        }
        printf("Key: %s    Val: %s\n", currline, get(linemap, currline));
    }
    full_map_close(linemap);
    return 0;
}
