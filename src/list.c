/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Fabian M.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdlib.h>

#include "../include/list.h"

/*
 * Creates a new linked list.
 *
 * @return A new linked list.
 */
struct BrainfuckList * brainfuck_list_new() {
	return (struct BrainfuckList *) malloc(sizeof(BrainfuckList));
}

/* 
 * Determines if the given list is empty.
 *
 * @param list The list to check.
 * @return <code>true</code> if this list is empty, <code>false</code> otherwise.
 */
int brainfuck_list_empty(struct BrainfuckList *list)
{
	return list->root == NULL;
}


/*
 * Creates a new linked list node.
 *
 * @return A new linked list node.
 */
struct BrainfuckListNode * brainfuck_list_node_new()
{
	return (struct BrainfuckListNode *) malloc(sizeof(BrainfuckListNode));
}

/*
 * Returns the last node of a linked list.
 *
 * @param list The list to get the last node of.
 * @return The last node of a linked list.
 */
struct BrainfuckListNode * brainfuck_list_last(struct BrainfuckList *list)
{
	struct BrainfuckListNode *head = list->root;
	while (head != NULL)
		if (head->next == NULL)
			return head;
		brainfuck_list_next(head);
	return NULL;
}

/*
 * Removes the first node of a linked list.
 *
 * @param list The list to remove the first node of.
 * @return The removed node.
 */
struct BrainfuckListNode * brainfuck_list_shift(struct BrainfuckList *list)
{
	struct BrainfuckListNode *node = list->root;
	if (node == NULL)
		return node;
	list->root = node->next;
	return node;
}

/*
 * Adds the given node to the end of the given list.
 *
 * @param list The list to add the node to.
 * @param node The node to add.
 */
void brainfuck_list_push(struct BrainfuckList *list, struct BrainfuckListNode *node)
{
	struct BrainfuckListNode *head = brainfuck_list_last(list);
	if (head == NULL)
		list->root = node;
	head->next = node;
}

/*
 * Adds the given node to the front of the list.
 *
 * @param list The list to add the node to.
 * @param node The node to add to the front of the list.
 */
void brainfuck_list_unshift(struct BrainfuckList *list, struct BrainfuckListNode *node)
{
	struct BrainfuckListNode *original_root = list->root;
	list->root = node;
	list->root->next = original_root;
}
