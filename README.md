# Simple C Language Compiler

## Overview

The Simple language is a high-level abstraction inspired by C but with a more concise and Pythonic syntax. This project provides a compiler for Simple, making it easier to write C-like code with modern syntactic conveniences, aiming at educational purposes and simplified programming.

## Features

- **Python-inspired syntax:** Simple adopts the clean and readable style of Python, reducing the complexity often associated with C.
- **C-like functionality:** While the syntax is simplified, the language retains core concepts of C such as variables, loops, and conditionals, allowing users to experience C-like programming without its full complexity.
- **High-level abstraction:** The language is designed to help users focus on logic and structure, abstracting away some of the lower-level details that make C more difficult for beginners.

## Syntax

The Simple language blends the intuitive nature of Python with key elements from C. For example:

- **Variable declaration:** Similar to C but without type specification.
- **Function declaration:** Python-like indentation but follows C's logical structure.
- **Control flow:** Includes familiar constructs such as `if`, `while`, and `for`, with simplified syntax.

### Example Code:

```python
def main():
    # Simple print statement
    print("Hello, World!")

    # Loop example
    for i in range(10):
        print(i)
