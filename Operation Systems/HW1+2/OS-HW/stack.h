#ifndef STACK_H_
#define STACK_H_

typedef struct {
	void* data;
	int top;
	int totalElements;
	int memberSize;
} Stack;

Stack* initStack(int size, int totalElements);
int freeStack(Stack* stack);
int expandStack(Stack* stack);
int isEmpty(Stack* stack);
int isFull(Stack* stack);
int push(Stack* stack, void* element);
int pop(Stack* stack, void* target);
int peek(Stack* stack, void* target);

#endif /* STACK_H_ */
