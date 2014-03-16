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

#include <stdio.h>
#include <stdlib.h>

#include "../include/brainfuck.h"

/*                                                                              
 * Return a BrainfuckEnvironment with the input and output handlers connected
 * 	to the standard input and output.                                            
 *                                                                              
 * @return The default environment.                                             
 */                                                                             
struct BrainfuckEnvironment * brainfuck_environment_default() 
{
	BrainfuckEnvironment *env = malloc(sizeof(BrainfuckEnvironment));
	env->input_handler = &getchar;
	env->output_handler = &putchar;
	return env;
}

/*                                                                              
 * Compile the given string using the default Brainfuck compiler.                         
 *                                                                              
 * @param source The source string to compile.                                  
 * @param success A pointer to an integer that will be set to either a          
 *      success or an error code.                                               
 * @return A pointer to a BrainfuckScript instance or <code>null</code> if      
 *      the compiling failed.                                                   
 */                                                                             
struct BrainfuckScript * brainfuck_compile(char *source, int *success) 
{
	BrainfuckScript *script = malloc(sizeof(BrainfuckScript));
	BrainfuckScriptNode *node;
	BrainfuckScriptNode *head;
	BrainfuckInstruction *instruction;

	int id = 0;
	int difference = 0;
	
	while (*source) {
		node = malloc(sizeof(BrainfuckScriptNode));

		switch (*source++) {
		case '+':
		case '-':
			difference = 0;

			while (*source++ == '+' || *source == '-')
				if (*source == '+')
					difference++;
				else
					difference--;
			
			if (difference == 0)
				continue;	
			else
				id = difference > 0 ? BRAINFUCK_INSTRUCTION_PLUS : BRAINFUCK_INSTRUCTION_MINUS;
			instruction = (BrainfuckInstruction *) malloc(sizeof(BrainfuckMutateInstruction));
			instruction->id = id;
			((BrainfuckMutateInstruction *) instruction)->difference = difference;
			break;
		}
		
		case '>':
		case '<':
			difference = 0;

			while (*source++ == '+' || *source == '-')
				if (*source == '+')
					difference++;
				else
					difference--;
			
			if (difference == 0)
				continue;	
			else
				id = difference > 0 ? BRAINFUCK_INSTRUCTION_NEXT : BRAINFUCK_INSTRUCTION_PREVIOUS;
			instruction = (BrainfuckInstruction *) malloc(sizeof(BrainfuckMutateInstruction));
			instruction->id = id;
			((BrainfuckMutateInstruction *) instruction)->difference = difference;
			break;
		}
		
		node->instruction = instruction;
		if (script->root == NULL) 
			script->root = node;
		head->next = node;
		head = node;
	}
	*success = BRAINFUCK_OK; 
	return NULL;
}

/*                                                                              
 * Run the given compiled script with the given environment.                    
 *                                                                              
 * @param script The script to run.                                             
 * @param environment The environment to run this script in. If this argument   
 *      is <code>null</code>, it will use the default environment.              
 * @return a integer with a value of zero or higher if the script executed      
 *      successfully, a value lower than zero otherwise.                        
 */                                                                             
int brainfuck_run(struct BrainfuckScript *script, struct BrainfuckEnvironment *environment) 
{
	return BRAINFUCK_OK;
}

/*                                                                              
 * Deallocate the given Brainfuck structure from the memory.                    
 *                                                                              
 * @param structure The structure to deallocate from the memory.                
 */                                                                             
void brainfuck_free(void *structure) 
{
	free(structure);
	structure = 0;
}
