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

/*
 * This structure represents a script that is compiled by a compiler.
 */ 
struct BrainfuckScript {

} BrainfuckScript;

/*
 * This structure represents an environment in which a script can be run.
 */
struct BrainfuckEnvironment {

} BrainfuckEnvironment;

/*
 * Return the default environment.
 * 
 * @return The default environment.
 */
struct BrainfuckEnvironment * brainfuck_environment_default();

/* 
 * Compile the given string using a Brainfuck compiler.
 *
 * @param source The source string to compile.
 * @return A pointer to a BrainfuckScript instance.
 */
struct BrainfuckScript * brainfuck_compile(char *source);

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
