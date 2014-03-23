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
#include <string.h>

#ifndef NO_JIT
#	include <sys/types.h>
#	include <sys/mman.h>
#endif

#include "../include/brainfuck.h"

/*                                                                              
 * Return an Environment with the input and output handlers connected
 * 	to the standard input and output.                                            
 *                                                                              
 * @return The default environment.                                             
 */                                                                             
struct BrainfuckEnvironment * brainfuck_default_environment() 
{
	struct BrainfuckEnvironment *env = malloc(sizeof(struct BrainfuckEnvironment));
	env->input_handler = &getchar;
	env->output_handler = &putchar;
	return env;
}

#ifndef NO_JIT
/*
 * Creates a memory cell mutation instruction.
 *
 * @param difference The value to add to the current memory cell value.
 * @return The created instruction as a MutateInstruction.
 */
struct BrainfuckInstruction * brainfuck_create_cell_mutation(int difference) 
{
	unsigned char code[] = {
        
	};
    
	struct BrainfuckMutateInstruction *mutate_instruction = malloc(sizeof(struct BrainfuckMutateInstruction));
	mutate_instruction->difference = difference;
	
	struct BrainfuckInstruction *instruction = (struct BrainfuckInstruction *) mutate_instruction;
	instruction->id = BRAINFUCK_INSTRUCTION_CELL;
	instruction->memory = malloc(sizeof(code));
	memcpy(instruction->memory, code, sizeof(code));
	mprotect(instruction->memory, sizeof(code), PROT_EXEC);
   
	return instruction;
}

/*
 * Creates a memory index mutation instruction.
 *
 * @param difference The value to add to the current memory index.
 * @return The created instruction as a MutateInstruction.
 */
struct BrainfuckInstruction * brainfuck_create_index_mutation(int difference) 
{
	unsigned char code[] = {
        
	};
    
	struct BrainfuckMutateInstruction *mutate_instruction = malloc(sizeof(struct BrainfuckMutateInstruction));
	mutate_instruction->difference = difference;
	
	struct BrainfuckInstruction *instruction = (struct BrainfuckInstruction *) mutate_instruction;
	instruction->id = BRAINFUCK_INSTRUCTION_INDEX;
	instruction->memory = malloc(sizeof(code));
	memcpy(instruction->memory, code, sizeof(code));
	mprotect(instruction->memory, sizeof(code), PROT_EXEC);
   
	return instruction;
}
#else

/*
 * Handles cell mutation if JIT is disabled.
 *
 * @param instruction The instruction to handle.
 * @param ctx The execution context to use.
 * @return The result. If lower than zero, it failed.
 */
int brainfuck_handle_cell_mutation(struct BrainfuckInstruction *instruction, struct BrainfuckExecutionContext *ctx)
{
	ctx->memory[ctx->index] = ((struct BrainfuckMutateInstruction *) instruction)->difference;
	return 0;
}

/*
 * Handles index mutation if JIT is disabled.
 *
 * @param instruction The instruction to handle.
 * @param ctx The execution context to use.
 * @return The result. If lower than zero, it failed.
 */
int brainfuck_handle_index_mutation(struct BrainfuckInstruction *instruction, struct BrainfuckExecutionContext *ctx)
{
	ctx->index += ((struct BrainfuckMutateInstruction *) instruction)->difference;
	return 0;
}

/*
 * Handles output if JIT is disabled.
 *
 * @param instruction The instruction to handle.
 * @param ctx The execution context to use.
 * @return The result. If lower than zero, it failed.
 */
int brainfuck_handle_output(struct BrainfuckInstruction *instruction, struct BrainfuckExecutionContext *ctx)
{
	(void)(instruction); /* compiler will throw unused parameter error otherwise */
	ctx->env->output_handler(ctx->memory[ctx->index]);
	return 0;
}

#endif 

/*
 * Returns the default execution context.
 *
 * @param size Size of the memory.
 * @return The default execution context.
 */
struct BrainfuckExecutionContext * brainfuck_default_execution_context(int size)
{
	struct BrainfuckExecutionContext *ctx = malloc(sizeof(struct BrainfuckExecutionContext));
	ctx->index = 0;
	ctx->memory = malloc(sizeof(int) * size);
	ctx->env = brainfuck_default_environment();
	return ctx;
}

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
int brainfuck_run(struct BrainfuckScript *script, struct BrainfuckExecutionContext *ctx)
{
	if (ctx == NULL)
		ctx = brainfuck_default_execution_context(BRAINFUCK_DEFAULT_MEMORY_SIZE);
	
	struct BrainfuckScriptNode *node = script->root;
	while (node) {
		if (node->instruction->memory == NULL)
			continue;
#ifndef NO_JIT
		int (*func)(struct BrainfuckExecutionContext *ctx)  = node->instruction->memory;
		int result = func(ctx);
#else
		int (*func)(struct BrainfuckInstruction *, struct BrainfuckExecutionContext *ctx)  = node->instruction->memory;
		int result = func(node->instruction, ctx);
#endif
		if (result < BRAINFUCK_OK)
			return result;
		node = node->next;
	}
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
struct BrainfuckScript * brainfuck_compile(struct BrainfuckCompilerContext *ctx, char *source, int *error)
{
	struct BrainfuckScript *script = malloc(sizeof(struct BrainfuckScript));
	struct BrainfuckScriptNode *node;
	struct BrainfuckScriptNode *head;
	struct BrainfuckInstruction *instruction;

	struct BrainfuckPassManagerNode *pass_node;
	
	if (ctx != NULL)
		pass_node = ctx->pass_manager->root;

	int difference = 0;
	
	while (*source) {
		node = malloc(sizeof(struct BrainfuckScriptNode));
		
		switch (*source++) {
			case '+':
			case '-':
				difference = 0;

				while (*source++ == '+' || *source == '-')
					if (*source == '+')
						difference++;
				else
					difference--;
				source--;
				if (difference == 0)
					continue;	
#ifndef NO_JIT
				instruction = brainfuck_create_cell_mutation(difference);
#else
				instruction = (struct BrainfuckInstruction *) malloc(sizeof(struct BrainfuckMutateInstruction));
				instruction->id = BRAINFUCK_INSTRUCTION_CELL;
				instruction->memory = &brainfuck_handle_cell_mutation;
		
				((struct BrainfuckMutateInstruction *) instruction)->difference = difference;
#endif
				break;
			case '>':
			case '<':
				difference = 0;

				while (*source++ == '+' || *source == '-')
					if (*source == '+')
						difference++;
				else
					difference--;
				source--;
			
				if (difference == 0)
					continue;	
#ifndef NO_JIT
				instruction = brainfuck_create_index_mutation(difference);
#else
				instruction = (struct BrainfuckInstruction *) malloc(sizeof(struct BrainfuckMutateInstruction));
				instruction->id = BRAINFUCK_INSTRUCTION_INDEX;
				instruction->memory = &brainfuck_handle_index_mutation;
		
				((struct BrainfuckMutateInstruction *) instruction)->difference = difference;
#endif
				break;

			case '.':
#ifndef NO_JIT
			
#else
				instruction = malloc(sizeof(struct BrainfuckInstruction));
				instruction->id = BRAINFUCK_INSTRUCTION_OUTPUT;
				instruction->memory = &brainfuck_handle_output;
#endif
				break;
			case ',':
#ifndef NO_JIT
			
#else
				instruction = malloc(sizeof(struct BrainfuckInstruction));
				instruction->id = BRAINFUCK_INSTRUCTION_INPUT;
				instruction->memory = &brainfuck_handle_input;
#endif
				break;
		}
		
		while (pass_node) {
			if (pass_node->pass == NULL)
				continue;
			if (pass_node->pass->analyse != NULL)
				pass_node->pass->analyse(instruction);
			if (pass_node->pass->transform != NULL)
				instruction = pass_node->pass->transform(instruction);
			pass_node = pass_node->next;
		}
		if (ctx != NULL)
			pass_node = ctx->pass_manager->root;
		if (instruction == NULL)
			continue;
		node->instruction = instruction;
		if (script->root == NULL) 
			script->root = node;
		if (head != NULL)
			head->next = node;
		head = node;
	}
	if (error != NULL)
		*error = BRAINFUCK_OK; 
	return script;
}
