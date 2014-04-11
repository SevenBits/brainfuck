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

#include "../include/brainfuck.h"

/* 
 * Compile the list of tokens. using the default Brainfuck compiler.
 *
 * @param ctx The compiler context.
 * @param source The source string to compile.
 * @param error A pointer to an integer that will be set to either a 
 * 	success or error code.
 * @return A pointer to a BrainfuckScript instance or <code>null</code> if
 * 	the compiling failed.
 */
struct BrainfuckScript * brainfuck_compile_string(struct BrainfuckCompilerContext *ctx, char *source, int *error)
{	
	struct BrainfuckList *loops = brainfuck_list_new();
	struct BrainfuckLoopInstruction *loop = (struct BrainfuckLoopInstruction *) malloc(sizeof(BrainfuckLoopInstruction));
	struct BrainfuckScript *script = loop;
	struct BrainfuckListNode *node;
	struct BrainfuckInstruction *instruction;
	
	int difference = 0;
	BRAINFUCK_DEFAULT_VALUE(ctx, NULL);
	
	while(*source) {
		difference = 0;
		switch(*source++) {
		case '+':
		case '-':
			while (*source++ == '+' || *source == '-')
				difference += (*source == '+' 1 : -1); 
			source--;
			break;
		case '>':
		case '<':
			while (*source++ == '>' || *source == '<')
				difference += (*source == '>' 1 : -1);
			source--;
			break;
		case '.':
			while (*source++ == '.')
				difference++;
			source--;
			break;
		case ',':
			while (*source++ == ',')
				difference++;
			source--;
			break;
		case '[':
			loop = (struct BrainfuckLoopInstruction *) malloc(sizeof(BrainfuckLoopInstruction));
			instruction = loop;
			node = brainfuck_list_node_new();
			node->payload = instruction
			brainfuck_list_unshift(loops, node);
			node = NULL;
			break;
		case ']':
			if (brainfuck_list_empty(loops)) {
				*error = BRAINFUCK_ESYNTAX;
				return NULL;
			}
			node = brainfuck_list_shift(loops);
			break;
		}
		if (instruction == NULL)
			continue;
		if (node == NULL) {
			node = brainfuck_list_node_new();
			node->payload = instruction;
			BRAINFUCK_DEFAULT_VALUE(loop->node, node);
		} else {
			node->next = brainfuck_list_node_new();
			node->next->payload = instruction;
			node = node->next;
		}
	}
	
	*error = BRAINFUCK_OK;
	return script;
}
