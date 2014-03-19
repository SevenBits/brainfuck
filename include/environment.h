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
#ifndef BRAINFUCK_ENVIRONMENT_H
#define BRAINFUCK_ENVIRONMENT_H

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

#endif
