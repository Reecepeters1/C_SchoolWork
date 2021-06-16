#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Takes in two unsigned long values and returns their absolute valued difference in the
//Form of an unsigned long. Returns that unsigned long.
unsigned long long_abs(unsigned long ind1, unsigned long ind2)
{
    unsigned long ret = 0;
    if (ind1 > ind2)
    {
        ret = (unsigned long)((long long)ind1 - (long long)ind2);
    }
    else if (ind2 > ind1)
    {
        ret = (unsigned long)((long long)ind2 - (long long)ind1);
    }
    return ret;
}

//Abbreviated PN
struct PriorityNode
{
    unsigned long priority;
    char *val; // owned by PQ most of the time
    //Documented where PQ gives ownership to user
};

//Abbreviated PQ
struct PriorityQueue
{
    int capacity;
    int size;
    unsigned long gravity;
    struct PriorityNode **data; //owned by PQ
};

//Takes in a priority value and a piece of string data to make
//into a new PriorityNode struct. Returns a pointer to that struct.
struct PriorityNode *make_node(unsigned long prio, char *value)
{
    struct PriorityNode *ret = malloc(sizeof(struct PriorityNode));
    //printf("Allocated node in make_node\n");
    ret->priority = prio;
    char *new_val = malloc((strlen(value) + 1) * sizeof(char));
    //printf("Allocated string in make_node\n");
    strcpy(new_val, value);
    ret->val = new_val;
    return ret;
}

//Frees a node, including its value. This is what the PQ
//Uses to free a node it has in its data.
void free_node(struct PriorityNode *garbage)
{
    free(garbage->val);
    //printf("Freed value in free_node\n");
    free(garbage);
    //printf("Freed node in free_node\n");
}

//Frees the header of a node, but not the data. Used when the PQ
//gives ownership of a piece of data in the PN to the user
void free_node_head(struct PriorityNode *garbage)
{
    free(garbage);
    //printf("Freed node in free_node_head\n");
}

//Swaps two PNs in the PQ with eachother in the heap specified by two
//indices
void swap_two(struct PriorityQueue *pq, int ind1, int ind2)
{
    struct PriorityNode *temp = pq->data[ind1];
    pq->data[ind1] = pq->data[ind2];
    pq->data[ind2] = temp;
}

//Takes in a PQ and an index, percolating that PN at the index
//down to its appropriate spot
void percolate_down(struct PriorityQueue *pq, int ind)
{
    int pqsize = pq->size;
    long grav = pq->gravity;
    struct PriorityNode **tab = pq->data;
    while (2 * ind + 1 < pqsize)
    {
        unsigned long leftDiff = long_abs(tab[2 * ind + 1]->priority, grav);
        unsigned long rightDiff = ULONG_MAX;
        if (2 * ind + 2 < pqsize)
        {
            rightDiff = long_abs(tab[2 * ind + 2]->priority, grav);
        }
        if (leftDiff < rightDiff && long_abs(tab[ind]->priority, grav) > leftDiff)
        {
            swap_two(pq, ind, 2 * ind + 1);
            ind = 2 * ind + 1;
            continue;
        }
        if (rightDiff < leftDiff && long_abs(tab[ind]->priority, grav) > rightDiff)
        {
            swap_two(pq, ind, 2 * ind + 2);
            ind = 2 * ind + 2;
            continue;
        }
        break;
    }
}

//Takes a PQ and an index, percolating that PN at the index
//down to its appropriate spot
void percolate_up(struct PriorityQueue *pq, int ind)
{
    struct PriorityNode **tab = pq->data;
    long grav = pq->gravity;
    while (ind != 0 && long_abs(tab[(ind - 1) / 2]->priority, grav) > long_abs(tab[ind]->priority, grav))
    {
        swap_two(pq, (ind - 1) / 2, ind);
        ind = (ind - 1) / 2;
    }
}

//Uses Floyds heap building algorithm to order the elements of
//a heap
void floyd_build(struct PriorityQueue *pq)
{
    for (int i = pq->size - 1; i >= 0; i--)
    {
        percolate_down(pq, i);
    }
}

//Now is a good time to explain what "gravity" means. In my implementation, deciding how to
//organize the heap isn't based on the largest or smallest element. Rather it's based on
//how close its priority is to another dynamic value called the gravity of the heap. In that
//way, it's a generalization of the min/max priority queue (just set gravity to zero or the max
//value of an unsigned long).

//This method takes in an initial array of PNs, an initial gravity,
//and an initial size of that initial value array to make a PQ struct
//and returns a pointer to that struct.
struct PriorityQueue *make_priority_queue(unsigned long grav, struct PriorityNode **init, int size)
{
    struct PriorityQueue *ret = malloc(sizeof(struct PriorityQueue) + (size * sizeof(struct PriorityNode)));
    //printf("Allocated queue in make_priority_queue\n");
    ret->size = size;
    ret->gravity = grav;
    if (size <= 10)
    {
        ret->capacity = 10;
    }
    else
    {
        ret->capacity = size;
    }
    ret->data = malloc(ret->capacity * sizeof(struct PriorityNode));
    //printf("Allocated data in make_priority_queue\n");
    for (int i = 0; i < size; i++)
    {
        ret->data[i] = init[i];
    }
    floyd_build(ret);
    return ret;
}

//Does the same as the above method, but doesn't take in a gravity field because
//we set gravity to 0, making the returned pointer to a PQ struct
//functionally the samea as a min priority queue
struct PriorityQueue *make_min_priority_queue(struct PriorityNode **init, int size)
{
    return make_priority_queue(0, init, size);
}

//Does the same as the above method, but doesn't take in a gravity field because
//we set gravity to ULONG_MAX, making the returned pointer to a PQ struct
//functionally the samea as a max priority queue
struct PriorityQueue *make_max_priority_queue(struct PriorityNode **init, int size)
{
    return make_priority_queue(ULONG_MAX, init, size);
}

//Takes in a PQ and an int factor and resizes the capacity of the internal data
//array of the PQ and scales it multiplcatively by the factor given.
void pq_resize(struct PriorityQueue *pq, int factor)
{
    struct PriorityNode **temp = realloc(pq->data, (factor * pq->capacity) * (sizeof(struct PriorityNode)));
    printf("Reallocated data in resize\n");
    if (temp)
    {
        pq->data = temp;
    }
    pq->capacity = factor * pq->capacity;
}

//Takes in a PQ and returns the value of the node with the priority closest to
//the gravity of the PQ
char *pq_peek(struct PriorityQueue *pq)
{
    if (pq->data[0])
    {
        return pq->data[0]->val;
    }
    else
    {
        printf("ERROR: There is nothing in this PriorityQueue");
        return NULL;
    }
}

//Takes in a PQ and returns the value of the node with the priority closest to
//the gravity of the PQ and then removes the node from the PQ.
//THIS IS WHERE WE GIVE OWNERSHIP OF A VALUE STRING TO THE USER. THE USER
//MUST FREE THIS STRING USING FREE. If you don't want a return value, use the
//method pq_remove_returnless
char *pq_remove(struct PriorityQueue *pq)
{
    char *ret = pq_peek(pq);
    if (!ret)
    {
        return NULL;
    }
    swap_two(pq, 0, pq->size - 1);
    free_node_head(pq->data[pq->size - 1]);
    pq->data[pq->size - 1] = NULL;
    pq->size--;
    percolate_down(pq, 0);
    return ret;
}

//Takes in a PQ and simply removes the node with the value closest to the
//gravity of the PQ. Does not require the user to free the returned string.
void pq_remove_returnless(struct PriorityQueue *pq)
{
    free(pq_remove(pq));
}

//Takes in a PQ and returns the number of elements in it
int pq_size(struct PriorityQueue *pq)
{
    return pq->size;
}

//Changes a given PQ to have a new specified gravity, then rebuilds
//the PQ
void pq_regravitate(struct PriorityQueue *pq, unsigned long grav)
{
    pq->gravity = grav;
    floyd_build(pq);
}

//Takes in a PQ and a string value. Returns 1 if that value is contained
//within the PQ and returns 0 if not
int pq_contains(struct PriorityQueue *pq, char *value)
{
    for (int i = 0; i < pq->size; i++)
    {
        if (!strcmp(pq->data[i]->val, value))
        {
            return 1;
        }
    }
    return 0;
}

//Takes in a PQ, a string value, and a priority. Uses these values to make a
//new PN and add it to the PQ
void pq_add(struct PriorityQueue *pq, char *in_val, unsigned long new_prio)
{
    if (pq->size + 1 > pq->capacity)
    {
        pq_resize(pq, 2);
    }

    pq->data[pq->size] = make_node(new_prio, in_val);
    percolate_up(pq, pq->size);
    pq->size++;
}

//Empties a PQ of all of its nodes
void pq_clear(struct PriorityQueue *pq)
{
    for (int i = 0; i < pq->size; i++)
    {
        free_node(pq->data[i]);
        pq->data[i] = NULL;
    }
    pq->size = 0;
}

//Prints the internal array of the PQ
void pq_print(struct PriorityQueue *pq)
{
    printf("[");
    for (int i = 0; i < pq->size; i++)
    {
        if (i == pq->size - 1)
        {
            printf("%s", pq->data[i]->val);
        }
        else
        {
            printf("%s,", pq->data[i]->val);
        }
    }
    printf("]\n");
}

//Frees a PQ, except for returned strings given to the user
void free_pq(struct PriorityQueue *pq)
{
    for (int i = 0; i < pq->size; i++)
    {
        free_node(pq->data[i]);
    }
    free(pq->data);
    //printf("Freed data in free_pq\n");
    free(pq);
    //printf("Freed heap in free_pq\n");
}
