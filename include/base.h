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
#ifndef LIBBRAINFUCK_BASE_H
#define LIBBRAINFUCK_BASE_H

#define LIBBRAINFUCK_OK 0 /* Everything is OK */
#define LIBBRAINFUCK_EOF EOF /* End of file */
#define LIBBRAINFUCK_ENOMEM -5 /* Out of memory */
#define LIBBRAINFUCK_ESYNTAX -6 /* Syntax error */

#include "instruction.h"
#include "environment.h"
#include "pass.h" 

/*
 * This structure represents a node of the linked list that contains all
 *	instructions of a script.
 */
struct libbrainfuck_ScriptNode {
	/*
	 * Pointer to the instruction of this node.
	 */
	struct libbrainfuck_Instruction *instruction;
	/*
 	 * The next node in the linked list.
	 */
	struct libbrainfuck_ScriptNode *next;
} libbrainfuck_ScriptNode;

/*
 * This structure represents a script that is compiled by a compiler.
 */ 
struct libbrainfuck_Script {
	/*
	 * Pointer to the first instruction of this script.
	 */ 
	struct libbrainfuck_ScriptNode *root;
} libbrainfuck_Script;

/*
 * This structure is passed to the compiler and contains the pass manager.
 * 	that the compiler must use when compiling.
 */
struct libbrainfuck_CompilerContext {
	/* 
	 * The PassManager that the compiler should use.
	 */
	struct libbrainfuck_PassManager *pass_manager;
} libbrainfuck_CompilerContext;

/*
 * This structure is contains the current index and the location of the memory cells.
 */
struct libbrainfuck_ExecutionContext {
	/*
	 * The current index in the memory.
	 */
	int index;

	/*
	 * Location of the memory.
	 */
	int *memory;

	/*
	 * Environment to execute the script in.
	 */
	struct libbrainfuck_Environment *env;
} libbrainfuck_ExecutionContext;

/*
 * Returns the default execution context.
 *
 * @param size Size of the memory.
 * @return The default execution context.
 */
struct libbrainfuck_ExecutionContext * libbrainfuck_default_execution_context(int size);

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
int libbrainfuck_run(struct libbrainfuck_Script *script, struct libbrainfuck_ExecutionContext *ctx);

/*
 * Deallocate the given Brainfuck structure from the memory.
 *
 * @param structure The structure to deallocate from the memory.
 */
void libbrainfuck_free(void *structure);

#endif
