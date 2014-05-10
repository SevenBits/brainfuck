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

#ifndef BRAINFUCK_HELPER_H
#define BRAINFUCK_HELPER_H

#include "base.h"

/*
 * Creates a cell value mutation instruction and returns it.
 *
 * @param difference The difference between the current cell value and the value
 * 	that is going to be set.
 * @return The cell value mutation instruction.
 */
struct BrainfuckInstruction * brainfuck_helper_create_cell_mutation(int difference);

/*
 * Handles the cell value mutation on platforms where JIT isn't available.
 *
 * @param ctx The execution context that will provide the memory management and
 *	the environment for the execution.
 * @param instruction The instruction that is executed.
 * @return <code>BRAINFUCK_OK</code> if no errors occured.
 */
int brainfuck_helper_handle_cell_mutation(struct BrainfuckExecutionContext *ctx, struct BrainfuckInstruction *instruction);

/*
 * Creates an index mutation instruction and returns it.
 *
 * @param difference The difference between the current index and the index
 * 	that is going to be set.
 * @return The index mutation instruction.
 */
struct BrainfuckInstruction * brainfuck_helper_create_index_mutation(int difference);

/*
 * Handles the index mutation on platforms where JIT isn't available.
 *
 * @param ctx The execution context that will provide the memory management and
 *	the environment for the execution.
 * @param instruction The instruction that is executed.
 * @return <code>BRAINFUCK_OK</code> if no errors occured.
 */
int brainfuck_helper_handle_index_mutation(struct BrainfuckExecutionContext *ctx, struct BrainfuckInstruction *instruction);

/*
 * Creates an output instruction and returns it.
 *
 * @param times The amount of times this instruction will be executed.
 * @return The output instruction.
 */
struct BrainfuckInstruction * brainfuck_helper_create_output(int times);

/*
 * Handles the output on platforms where JIT isn't available.
 *
 * @param ctx The execution context that will provide the memory management and
 *	the environment for the execution.
 * @param instruction The instruction that is executed.
 * @return <code>BRAINFUCK_OK</code> if no errors occured.
 */
int brainfuck_helper_handle_output(struct BrainfuckExecutionContext *ctx, struct BrainfuckInstruction *instruction);

/*
 * Creates an input instruction and returns it.
 *
 * @param times The amount of times this instruction will be executed.
 * @return The input instruction.
 */
struct BrainfuckInstruction * brainfuck_helper_create_input(int times);

/*
 * Handles the input on platforms where JIT isn't available.
 *
 * @param ctx The execution context that will provide the memory management and
 *	the environment for the execution.
 * @param instruction The instruction that is executed.
 * @return <code>BRAINFUCK_OK</code> if no errors occured.
 */
int brainfuck_helper_handle_input(struct BrainfuckExecutionContext *ctx, struct BrainfuckInstruction *instruction);

#endif
