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
#ifndef BRAINFUCK_LIST_H
#define BRAINFUCK_LIST_H

/* Linked list inteface */
#define brainfuck_list_next(head) head = head->next;

/*
 * This structure represents a node of the linked list.
 */
struct BrainfuckListNode {
	/*
 	 * The next node in the linked list.
	 */
	struct BrainfuckListNode *next;
	/*
 	 * Pointer to the payload of this node.
	 */
	void *payload;
} BrainfuckListNode;

/*
 * This structure represents a linked list.
 */ 
struct BrainfuckList {
	/*
	 * Pointer to the first instruction of this list.
	 */ 
	struct BrainfuckListNode *root;
} BrainfuckList;

/*
 * Creates a new linked list.
 *
 * @return A new linked list.
 */
struct BrainfuckList * brainfuck_list_new();

/*
 * Adds the given element to the end of the given list.
 *
 * @param list The list to add the node to.
 * @param element The element to add.
 */
void brainfuck_list_add(struct BrainfuckList *list, void *element);

#endif