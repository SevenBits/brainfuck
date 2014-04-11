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
#ifndef BRAINFUCK_BASE_H
#define BRAINFUCK_BASE_H

#define BRAINFUCK_DEFAULT_VALUE(variable, value) variable = variable == NULL ? value : variable
#define BRAINFUCK_SET_ERROR(variable, value) if (variable != NULL) { \
	*variable = value;  \
} \

#define BRAINFUCK_OK 1 /* Everything is OK */
#define BRAINFUCK_EOF EOF /* End of file */
#define BRAINFUCK_ENOMEM -5 /* Out of memory */
#define BRAINFUCK_ESYNTAX -6 /* Syntax error */

#define BRAINFUCK_INSTRUCTION_SET_BRAINFUCK 1
#define BRAINFUCK_MEMORY_SIZE_DEFAULT 30000

#include "list.h"
#include "instruction.h"

/*
 * A BrainfuckCompilerContext structure is passed to the compiler and provides
 * 	the analystic and transform passes.
 */
struct BrainfuckCompilerContext {
} BrainfuckCompilerContext;

/*
 * A BrainfuckExecutionContext structure is passed to the execution engine and
 * 	provides the stdin, stdout and the memory management.
 */
struct BrainfuckExecutionContext {
	/*
 	 * Pointer to a function which can read from the environment's input.
	 *
	 * @return The character that was read from the environment's input.
	 */
	int (*input_handler)(void);

	/*
	 * Pointer to a function which can write to the environment's output.
	 * 
	 * @param character The character to write to the environment's output.
	 * @return On success, the written character is returned. If a writing 
	 * 	error occurs, BRAINFUCK_EOF is returned.
	 */
	int (*output_handler)(int character);
	
	/*
	 * The current index in the memory.
	 */
	int index;

	/*
	 * Location of the memory.
	 */
	int *memory;
} BrainfuckExecutionContext;

/*
 * Return the default execution context.
 * 
 * @param size Size of the memory block to allocate.
 * @return The default execution context.
 */
struct BrainfuckExecutionContext * brainfuck_execution_context_default(int size);

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
int brainfuck_run(struct BrainfuckLoopInstruction *script, struct BrainfuckExecutionContext *ctx);

/*
 * Deallocate the given Brainfuck structure from the memory.
 *
 * @param structure The structure to deallocate from the memory.
 */
void brainfuck_free(void *structure);

#endif
