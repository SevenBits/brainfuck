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
#include <stdio.h>

#include "../include/brainfuck.h"
#include "../include/helper.h"

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
struct BrainfuckLoopInstruction * brainfuck_compile_string(struct BrainfuckCompilerContext *ctx, char *source, int *error)
{	
	struct BrainfuckList *loops = brainfuck_list_new();
	struct BrainfuckLoopInstruction *loop = (struct BrainfuckLoopInstruction *) malloc(sizeof(BrainfuckLoopInstruction));
	struct BrainfuckLoopState *loop_state = NULL;
	struct BrainfuckLoopInstruction *script = loop;
	struct BrainfuckListNode *node = NULL;
	struct BrainfuckInstruction *instruction = (struct BrainfuckInstruction *) loop;	
	int difference = 0;

	BRAINFUCK_DEFAULT_VALUE(ctx, NULL);
	instruction->id = BRAINFUCK_INSTRUCTION_LOOP;
	instruction->memory = &brainfuck_helper_handle_loop;
	instruction = NULL;

	while(*source) {
		printf("source: %c\n", *source);
		difference = 1;
		switch(*source) {
		case '+':
		case '-':
			while (*(++source) == '+' || *source == '-')
				difference += (*source == '+' ? 1 : -1);
			source--;
			instruction = brainfuck_helper_create_cell_mutation(difference);
			break;
		case '>':
		case '<':
			while (*(++source) == '>' || *source == '<')
				difference += (*source == '>' ? 1 : -1);
			source--;
			instruction = brainfuck_helper_create_index_mutation(difference);
			break;
		case '.':
			while (*(++source) == '.')
				difference++;
			source--;
			instruction = brainfuck_helper_create_output(difference);
			break;
		case ',':
			while (*(++source) == ',')
				difference++;
			source--;
			instruction = brainfuck_helper_create_input(difference);
			break;
		case '[':
			/* tricky stuff here TODO add comments */
			loop_state = (struct BrainfuckLoopState *) malloc(sizeof(BrainfuckLoopState));
			loop_state->loop = loop;
			loop_state->node = node;
			node = brainfuck_list_node_new();
			node->payload = loop_state;
			/* end tricky stuff */
			brainfuck_list_unshift(loops, node);

			loop = (struct BrainfuckLoopInstruction *) malloc(sizeof(BrainfuckLoopInstruction));
			instruction = (struct BrainfuckInstruction *) loop;
			instruction->id = BRAINFUCK_INSTRUCTION_LOOP;
			instruction->memory = &brainfuck_helper_handle_loop;

			node = NULL;
			source++;
			continue;
		case ']':
			if (brainfuck_list_empty(loops)) {
				*error = BRAINFUCK_ESYNTAX;
				return NULL;
			}

			/* tricky stuff again */
			loop_state = brainfuck_list_shift(loops)->payload;
			loop = loop_state->loop;
			node = loop_state->node;
			instruction = (struct BrainfuckInstruction *) loop;
			/* end tricky stuff */
			break;
		}
		if (instruction == NULL)
			continue;
		if (node == NULL) {
			node = brainfuck_list_node_new();
			node->payload = instruction;
			BRAINFUCK_DEFAULT_VALUE(loop->root, node);
		} else {
			node->next = brainfuck_list_node_new();
			node->next->payload = instruction;
			node = node->next;
		}
		source++;
	}
	BRAINFUCK_SET_ERROR(error, BRAINFUCK_OK);
	return script;
}
