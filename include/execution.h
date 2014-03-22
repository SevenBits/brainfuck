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
#ifndef LIBBRAINFUCK_EXECUTION_H
#define LIBBRAINFUCK_EXECUTION_H

#include "environment.h"
#include "compiler.h"

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

#endif