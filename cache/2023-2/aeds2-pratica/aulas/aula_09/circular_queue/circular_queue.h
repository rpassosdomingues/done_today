#ifndef _H_QUEUE
#define _H_QUEUE

struct queue* create_queue(int size);
bool is_full(struct queue* queue);
bool is_empty(struct queue* queue);
void enqueue(struct queue* queue, int item);
int dequeue(struct queue* queue);
int get_element(struct queue* queue);

#endif // _H_QUEUE
