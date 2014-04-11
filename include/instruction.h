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
#ifndef BRAINFUCK_INSTRUCTION_H
#define BRAINFUCK_INSTRUCTION_H

#define BRAINFUCK_INSTRUCTION_CELL 1 /* Cell value mutation */
#define BRAINFUCK_INSTRUCTION_INDEX 2 /* Index mutation */
#define BRAINFUCK_INSTRUCTION_OUTPUT 3 /* Write cell value to stdout */
#define BRAINFUCK_INSTRUCTION_INPUT 4 /* Set cell value to stdin */
#define BRAINFUCK_INSTRUCTION_LOOP 5 /* Loop */

/*
 * This structure represents a single instruction.
 */
struct BrainfuckInstruction {
	/* 
	 * The id of this instruction.
	 */
	int id;

	/*                                                                
	 * Either the difference between the current value and the new value, or
	 * the amount of times to execute this instruction.
	 */
	int difference;

	/*
	 * Contains the memory to execute.
	 */
	void *memory;
} BrainfuckInstruction;

/*                                                                              
 * A loop instruction that contains a list of instructions to execute.                                   
 */                                                                             
struct BrainfuckLoopInstruction {                                     
	/*                                                                   
	 * The base instruction.                                                
	 */                                                                     
	struct BrainfuckInstruction base;                                       
                                                                    
	/*                                                                      
	 * The node that contains the first instruction to execute.   
	 */                                                                     
	struct BrainfuckListNode *root;                                               
} BrainfuckLoopInstruction; 

#endif
