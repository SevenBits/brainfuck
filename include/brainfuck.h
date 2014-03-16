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
#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#define BRAINFUCK_OK 0 /* Everything is OK */
#define BRAINFUCK_EOF EOF /* End of file */
#define BRAINFUCK_ENOMEM -5 /* Out of memory */
#define BRAINFUCK_ESYNTAX -6 /* Syntax error */

#define BRAINFUCK_INSTRUCTION_PLUS 1
#define BRAINFUCK_INSTRUCTION_MINUS 2
#define BRAINFUCK_INSTRUCTION_NEXT 3
#define BRAINFUCK_INSTRUCTION_PREVIOUS 4
#define BRAINFUCK_INSTRUCTION_OUTPUT 5
#define BRAINFUCK_INSTRUCTION_INPUT 6
#define BRAINFUCK_INSTRUCTION_LOOP 7

/*
 * This structure represents a single instruction.
 */
typedef struct BrainfuckInstruction {
	/* 
	 * The id of this instruction.
	 */
	int id;

	/*
	 * Contains the memory to execute.
	 */
	void *code;
} BrainfuckInstruction;

/*                                                                              
 * This structure represents an instruction that mutates the index or the       
 *      value of a memory cell.                                                 
 */                                                                             
typedef struct BrainfuckMutateInstruction {                                     
	/*                                                                   
	 * The base instruction.                                                
	 */                                                                     
	struct BrainfuckInstruction base;                                       
                                                                    
	/*                                                                      
	 * The difference between the current value and the new value.          
	 * To decrease the value, use a negative difference number.            
	 */                                                                     
        int difference;                                                         
} BrainfuckMutateInstruction;   

/*
 * This structure represents a node of the linked list that contains all
 *	instructions of a script.
 */
typedef struct BrainfuckScriptNode {
	/*
	 * Pointer to the instruction of this node.
	 */
	struct BrainfuckInstruction *instruction;
	/*
 	 * The next node in the linked list.
	 */
	struct BrainfuckScriptNode *next;
} BrainfuckScriptNode;

/*
 * This structure represents a script that is compiled by a compiler.
 */ 
typedef struct BrainfuckScript {
	/*
	 * Pointer to the first instruction of this script.
	 */ 
	struct BrainfuckScriptNode *root;
} BrainfuckScript;

/*
 * This structure represents an environment in which a script can be run.
 */
typedef struct BrainfuckEnvironment {
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
} BrainfuckEnvironment;

/*
 * Return the default environment.
 * 
 * @return The default environment.
 */
struct BrainfuckEnvironment * brainfuck_environment_default();

/* 
 * Compile the given string using the default Brainfuck compiler.
 *
 * @param source The source string to compile.
 * @param success A pointer to an integer that will be set to either a 
 * 	success or an error code.
 * @return A pointer to a BrainfuckScript instance or <code>null</code> if
 * 	the compiling failed.
 */
struct BrainfuckScript * brainfuck_compile(char *source, int *success);

/*
 * Run the given compiled script with the given environment.
 *
 * @param script The script to run.
 * @param environment The environment to run this script in. If this argument
 *	is <code>null</code>, it will use the default environment.
 * @return a integer with a value of zero or higher if the script executed 
 *	successfully, a value lower than zero otherwise.
 */
int brainfuck_run(struct BrainfuckScript *script, struct BrainfuckEnvironment *environment);

/*
 * Deallocate the given Brainfuck structure from the memory.
 *
 * @param structure The structure to deallocate from the memory.
 */
void brainfuck_free(void *structure);

#endif
