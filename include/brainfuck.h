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
#ifndef LIBBRAINFUCK_BRAINFUCK_H
#define LIBBRAINFUCK_BRAINFUCK_H

#include "base.h"

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
struct libbrainfuck_Script * libbrainfuck_brainfuck_compile(struct libbrainfuck_CompilerContext *ctx, char *source, int *error);

#endif
