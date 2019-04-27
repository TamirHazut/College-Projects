#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "hw2.h"

Stack* initStack(int size, int totalElements) {
	Stack* stack = (Stack*) malloc(sizeof(Stack));
	stack->top = -1;
	stack->memberSize = size;
	stack->totalElements = totalElements;
	stack->data = malloc(totalElements * size);
	return stack;
}

int freeStack(Stack* stack) {
	free(stack->data);
	free(stack);
	return 0;
}

int expandStack(Stack* stack) {
	stack->data = realloc(stack->data, stack->totalElements * 2);
	stack->totalElements *= 2;
	return 0;
}

int isEmpty(Stack* stack) {
	if (stack->top == -1) {
		return 1;
	}
	return 0;
}

int isFull(Stack* stack) {
	if (stack->top == stack->totalElements - 1) {
		return 1;
	}
	return 0;
}

int push(Stack* stack, void* element) {
	if (stack->top == stack->totalElements - 1) {
		expandStack(stack);
	}
	stack->top++;
	void* target = (char*) stack->data + (stack->top * stack->memberSize);
	memcpy(target, element, stack->memberSize);
	return 0;
}

int pop(Stack* stack, void* target) {
	if (isEmpty(stack)) {
		return 1;
	}
	void* source = (char*) stack->data + (stack->top * stack->memberSize);
	memcpy(target, source, stack->memberSize);
	stack->top--;
	return 0;
}

int peek(Stack* stack, void* target) {
	if (isEmpty(stack)) {
		return 1;
	}
	void* source = (char*) stack->data + (stack->top * stack->memberSize);
	memcpy(target, source, stack->memberSize);
	return 0;
}
