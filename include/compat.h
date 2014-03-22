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
#if !defined(LIBBRAINFUCK_COMPAT_H) && defined(NO_JIT)
#define LIBBRAINFUCK_COMPAT_H

#include "instruction.h"
#include "execution.h"

/*
 * Handles cell mutation if JIT is disabled.
 *
 * @param instruction The instruction to handle.
 * @param ctx The execution context to use.
 * @return The result. If lower than zero, it failed.
 */
int libbrainfuck_handle_cell_mutate_instruction(struct libbrainfuck_Instruction *instruction, struct libbrainfuck_ExecutionContext *ctx);

/*
 * Handles index mutation if JIT is disabled.
 *
 * @param instruction The instruction to handle.
 * @param ctx The execution context to use.
 * @return The result. If lower than zero, it failed.
 */
int libbrainfuck_handle_index_mutate_instruction(struct libbrainfuck_Instruction *instruction, struct libbrainfuck_ExecutionContext *ctx);

/*
 * Handles output if JIT is disabled.
 *
 * @param instruction The instruction to handle.
 * @param ctx The execution context to use.
 * @return The result. If lower than zero, it failed.
 */
int libbrainfuck_handle_output_instruction(struct libbrainfuck_Instruction *instruction, struct libbrainfuck_ExecutionContext *ctx);

#endif