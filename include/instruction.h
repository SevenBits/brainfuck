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
#ifndef LIBBRAINFUCK_INSTRUCTION_H
#define LIBBRAINFUCK_INSTRUCTION_H

#define LIBBRAINFUCK_INSTRUCTION_CELL 1 /* Cell value mutation */
#define LIBBRAINFUCK_INSTRUCTION_INDEX 2 /* Index mutation */
#define LIBBRAINFUCK_INSTRUCTION_OUTPUT 3
#define LIBBRAINFUCK_INSTRUCTION_INPUT 4
#define LIBBRAINFUCK_INSTRUCTION_LOOP 5

/*
 * This structure represents a single instruction.
 */
struct libbrainfuck_Instruction {
	/* 
	 * The id of this instruction.
	 */
	int id;

	/*
	 * The code of this instruction.
	 */
	char *code;

	/*
	 * Contains the memory to execute.
	 */
	void *memory;
} libbrainfuck_Instruction;

/*                                                                              
 * This structure represents an instruction that mutates the index or the       
 *      value of a memory cell.                                                 
 */                                                                             
struct libbrainfuck_MutateInstruction {                                     
	/*                                                                   
	 * The base instruction.                                                
	 */                                                                     
	struct libbrainfuck_Instruction base;                                       
                                                                    
	/*                                                                      
	 * The difference between the current value and the new value.          
	 * To decrease the value, use a negative difference number.            
	 */                                                                     
	int difference;                                                         
} libbrainfuck_MutateInstruction;  

/*
 * Creates a memory cell mutation instruction.
 *
 * @param difference The value to add to the current memory cell value.
 * @return The created instruction as a MutateInstruction.
 */
struct libbrainfuck_Instruction * libbrainfuck_create_cell_mutate_instruction(int difference);

/*
 * Creates a memory index mutation instruction.
 *
 * @param difference The value to add to the current memory cell value.
 * @return The created instruction as a MutateInstruction.
 */
struct libbrainfuck_Instruction * libbrainfuck_create_index_mutate_instruction(int difference);

#endif
