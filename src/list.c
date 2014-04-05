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
		brainfuck_list_iterate(head);
	return head;
}

/*
 * Adds the given element to the end of the given list.
 *
 * @param list The list to add the node to.
 * @param element The element to add.
 */
void brainfuck_list_add(struct BrainfuckList *list, void *element)
{
	struct BrainfuckListNode *node = brainfuck_list_node_new();
	node->payload = element;
	brainfuck_list_last(list)->next = node;
}
