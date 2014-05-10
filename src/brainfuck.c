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
struct BrainfuckScript * brainfuck_compile_string(struct BrainfuckCompilerContext *ctx, char *source, int *error)
{
	struct BrainfuckScript *script = NULL;
	struct BrainfuckListNode *node = NULL;
	struct BrainfuckInstruction *instruction = (struct BrainfuckInstruction *) malloc(sizeof(BrainfuckInstruction));

	int level = 0;
	int difference = 0;

	BRAINFUCK_DEFAULT_VALUE(ctx, NULL); /* useless code used to ignore the unused field error */

	while(*source) {
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
			level++;
			break;
		case ']':
			if (level <= 0) {
				*error = BRAINFUCK_ESYNTAX;
				return NULL;
			}
			break;
		}
		if (instruction == NULL)
			continue;
		node = brainfuck_list_node_new();
		node->payload = instruction;
		BRAINFUCK_DEFAULT_VALUE(script, node);
		source++;
	}
	BRAINFUCK_SET_ERROR(error, BRAINFUCK_OK);
	return script;
}
