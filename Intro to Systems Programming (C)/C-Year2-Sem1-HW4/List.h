/*
 * List.h
 *
 *  Created on: Jan 3, 2019
 *      Author: tamir-ubuntu
 */

#ifndef LIST_H_
#define LIST_H_
typedef void* DATA;
typedef enum {
	False, True
} BOOL;

typedef struct node {
	DATA key;
	struct node* next;
} NODE;
typedef struct {
	NODE head;
} LIST;

BOOL L_init(LIST* pList);

NODE* L_insert(NODE* pNode, DATA Value);

BOOL L_delete(NODE* pNode);

NODE* L_find(NODE* pNode, DATA Value, int (*equal)(const void*, const void*));

BOOL L_free(LIST* pList);

int L_print(LIST* pList, void (*print)(const void*));

#endif /* LIST_H_ */
