#ifndef _H_STACK
#define _H_STACK

struct stack* create_stack(int size);
bool is_full(struct stack* stack);
bool is_empty(struct stack* stack);
void push(struct stack* stack, int item);
int pop(struct stack* stack);
int get_top(struct stack* stack);

#endif // _H_STACK
