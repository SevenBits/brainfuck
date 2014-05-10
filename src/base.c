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

#include "../include/base.h"

/*
 * Return the default execution context.
 * 
 * @param size Size of the memory block to allocate.
 * @return The default execution context.
 */
struct BrainfuckExecutionContext * brainfuck_execution_context_default(int size)
{
	struct BrainfuckExecutionContext *ctx = (struct BrainfuckExecutionContext *) malloc(sizeof(BrainfuckExecutionContext));
	
	ctx->input_handler = &getchar;
	ctx->output_handler = &putchar;
	ctx->index = 0;
	ctx->memory = malloc(size);
	
	return ctx;
}

/*
 * Run the given compiled script with the given context.
 *
 * @param script The script to run.
 * @param ctx The execution context that will provide the memory management and
 *	the environment for the execution. If <code>NULL</code> is given, it will
 *	use the default context.
 * @return a integer with a value of zero or higher if the script executed 
 *	successfully, a value lower than zero otherwise.
 */                                                                         
int brainfuck_run(struct BrainfuckScript *script, struct BrainfuckExecutionContext *ctx)
{
	BRAINFUCK_DEFAULT_VALUE(ctx, brainfuck_execution_context_default(BRAINFUCK_MEMORY_SIZE_DEFAULT));
	struct BrainfuckListNode *head = script;
	struct BrainfuckInstruction *instruction = NULL;
	while (head != NULL) {
		instruction = head->payload;
		if (instruction == NULL || instruction->memory == NULL) {
			brainfuck_list_next(head);
			continue;
		}
		int (*func)(struct BrainfuckExecutionContext *ctx, struct BrainfuckInstruction *instruction)  = instruction->memory;
		int result = func(ctx, instruction);
		if (result < BRAINFUCK_OK)
			return result;
		brainfuck_list_next(head);
	}
	return BRAINFUCK_OK;
}

/*                                                                              
 * Deallocate the given Brainfuck structure from the memory.                    
 *                                                                              
 * @param structure The structure to deallocate from the memory.                
 */                                                                             
void brainfuck_free(void *structure) 
{
	free(structure);
	structure = 0;
}
