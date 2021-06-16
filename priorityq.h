struct PriorityNode
{
    unsigned long priority;
    char *val; // owned by user
};

struct PriorityQueue
{
    int capacity;
    int size;
    unsigned long gravity;
    struct PriorityNode **data; //owned
};

unsigned long long_abs(unsigned long ind1, unsigned long ind2);
void free_node(struct PriorityNode *garbage);
void free_node_head(struct PriorityNode *garbage);
void swap_two(struct PriorityQueue *pq, int ind1, int ind2);
void percolate_down(struct PriorityQueue *pq, int ind);
void percolate_up(struct PriorityQueue *pq, int ind);
void floyd_build(struct PriorityQueue *pq);
struct PriorityQueue *make_priority_queue(unsigned long grav, struct PriorityNode **init, int size);
struct PriorityQueue *make_min_priority_queue(struct PriorityNode **init, int size);
struct PriorityQueue *make_max_priority_queue(struct PriorityNode **init, int size);
void pq_resize(struct PriorityQueue *pq, int factor);
char *pq_peek(struct PriorityQueue *pq);
char *pq_remove(struct PriorityQueue *pq);
void pq_remove_returnless(struct PriorityQueue *pq);
int pq_size(struct PriorityQueue *pq);
void pq_regravitate(struct PriorityQueue *pq, unsigned long grav);
int pq_contains(struct PriorityQueue *pq, char *value);
void pq_add(struct PriorityQueue *pq, char *in_val, unsigned long new_prio);
void pq_clear(struct PriorityQueue *pq);
void pq_print(struct PriorityQueue *pq);
void free_pq(struct PriorityQueue *pq);
