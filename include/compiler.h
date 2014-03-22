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
#ifndef LIBBRAINFUCK_COMPILER_H
#define LIBBRAINFUCK_COMPILER_H

#include "instruction.h"
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


#endif