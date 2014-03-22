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

#include <stdio.h>
#include <stdlib.h>

#include "../include/brainfuck.h"

/*                                                                              
 * Return an Environment with the input and output handlers connected
 * 	to the standard input and output.                                            
 *                                                                              
 * @return The default environment.                                             
 */                                                                             
struct libbrainfuck_Environment * libbrainfuck_default_environment() 
{
	struct libbrainfuck_Environment *env = malloc(sizeof(struct libbrainfuck_Environment));
	env->input_handler = &getchar;
	env->output_handler = &putchar;
	return env;
}

/* 
 * Compile the given string using the default Brainfuck compiler.
 *
 * @param ctx The compiler context.
 * @param error A pointer to an integer that will be set to either a 
 * 	success or error code.
 * @param source The source string to compile.
 * @return A pointer to a BrainfuckScript instance or <code>null</code> if
 * 	the compiling failed.
 */
struct libbrainfuck_Script * libbrainfuck_brainfuck_compile(struct libbrainfuck_CompilerContext *ctx, char *source, int *error)
{
	struct libbrainfuck_Script *script = malloc(sizeof(libbrainfuck_Script));
	struct libbrainfuck_ScriptNode *node;
	struct libbrainfuck_ScriptNode *head;
	struct libbrainfuck_Instruction *instruction;

	int difference = 0;
	
	while (*source) {
		node = malloc(sizeof(struct libbrainfuck_ScriptNode));

		switch (*source++) {
		case '+':
		case '-':
			difference = 0;

			while (*source++ == '+' || *source == '-')
				if (*source == '+')
					difference++;
				else
					difference--;
			
			if (difference == 0)
				continue;	
			instruction = (struct libbrainfuck_Instruction *) malloc(sizeof(libbrainfuck_MutateInstruction));
			instruction->id = LIBBRAINFUCK_INSTRUCTION_CELL;
			((struct libbrainfuck_MutateInstruction *) instruction)->difference = difference;
			break;
		case '>':
		case '<':
			difference = 0;

			while (*source++ == '+' || *source == '-')
				if (*source == '+')
					difference++;
				else
					difference--;
			
			if (difference == 0)
				continue;	
			instruction = (struct libbrainfuck_Instruction *) malloc(sizeof(libbrainfuck_MutateInstruction));
			instruction->id = LIBBRAINFUCK_INSTRUCTION_INDEX;
			((struct libbrainfuck_MutateInstruction *) instruction)->difference = difference;
			break;

		case '.':
			instruction = malloc(sizeof(libbrainfuck_Instruction));
			instruction->id = LIBBRAINFUCK_INSTRUCTION_OUTPUT;
			break;
		}
		
		node->instruction = instruction;
		if (script->root == NULL) 
			script->root = node;
		head->next = node;
		head = node;
	}
	*error = LIBBRAINFUCK_OK; 
	return script;
}

/*
 * Returns the default execution context.
 *
 * @param size Size of the memory.
 * @return The default execution context.
 */
struct libbrainfuck_ExecutionContext * libbrainfuck_default_execution_context(int size)
{
	struct libbrainfuck_ExecutionContext *ctx = malloc(sizeof(libbrainfuck_ExecutionContext));
    ctx->index = 0;
    ctx->memory = malloc(sizeof(int) * size);
    ctx->env = libbrainfuck_default_environment();
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
int libbrainfuck_run(struct libbrainfuck_Script *script, struct libbrainfuck_ExecutionContext *ctx)
{
	struct libbrainfuck_ScriptNode *node = script->root;
	while (node) {
		node->instruction->memory(node->instruction, ctx);
		node = node->next;
	}
	return LIBBRAINFUCK_OK;
}

/*                                                                              
 * Deallocate the given Brainfuck structure from the memory.                    
 *                                                                              
 * @param structure The structure to deallocate from the memory.                
 */                                                                             
void libbrainfuck_free(void *structure) 
{
	free(structure);
	structure = 0;
}
