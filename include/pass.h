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
#ifndef LIBBRAINFUCK_PASS_H
#define LIBBRAINFUCK_PASS_H

/*
 * This structure represents a pass which can transform or analyse code.
 */
struct libbrainfuck_Pass {
	/*
	 * Analyse the given instruction.
	 *
	 * @param instruction The instruction to analyse.
	 */
	void (*analyse)(struct libbrainfuck_Instruction *instruction);

	/*
	 * Transforms the given instruction.
	 *
	 * @param instruction The instruction to transform.
	 * @return The transformed instruction.
	 */
	struct libbrainfuck_Instruction * (*transform)(struct libbrainfuck_Instruction *instruction);
} libbrainfuck_Pass;

/*
 * This structure represents a node in a linked list of a pass manager.
 */
struct libbrainfuck_PassManagerNode {
	/* 
	 * The Pass that is associated with this node.
	 */
	struct libbrainfuck_Pass *pass;

	/*
 	 * The next node.
	 */
	struct libbrainfuck_PassManagerNode *next;
} libbrainfuck_PassManagerNode;

/*
 * This structure manages passes.
 */
struct libbrainfuck_PassManager {
	/*
	 * The first node.
	 */
	struct libbrainfuck_PassManagerNode *root;
} libbrainfuck_PassManager;

#endif
