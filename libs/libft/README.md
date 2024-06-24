# Libft Project

## Overview

The Libft project is part of the 42 network curriculum, aimed at implementing a custom standard library in C. The goal is to recreate essential standard library functions to gain a deeper understanding of their implementation and improve C programming skills.

## Concepts Learned

### Standard Library Functions

* **String Manipulation**: Implementing functions for string operations such as copying, concatenation, comparison, and searching.
* **Memory Management**: Writing functions to manage memory allocation, deallocation, and manipulation.

### Data Structures

* **Linked Lists**: Creating and managing linked list data structures, including adding, removing, and iterating through elements.

### Function Implementation

* **Function Prototypes**: Writing functions with proper prototypes to ensure compatibility and usability.
* **Error Handling**: Implementing robust error handling within the functions.

## Project Description

**Libft**: The project involves implementing various functions from the standard C library, categorized into different sections.

### Part 1 - Libc Functions

- Implement standard C library functions such as `memset`, `bzero`, `memcpy`, `strdup`, `atoi`, and more.

### Part 2 - Additional Functions

- Implement additional useful functions that are not part of the standard library but are frequently used, such as `ft_substr`, `ft_strjoin`, `ft_strtrim`, and more.

### Part 3 - Bonus

- Implement functions to manipulate linked lists, such as `ft_lstnew`, `ft_lstadd_front`, `ft_lstsize`, `ft_lstlast`, and more.

## Implementation

* **String Functions**: Functions for handling and manipulating strings.
* **Memory Functions**: Functions for memory allocation and manipulation.
* **Linked List Functions**: Functions to create and manage linked lists.
    
## Compilation and Usage

```bash
git clone https://github.com/khalidlakbuichy/libft.git
```
```bash
cd libft
```
```bash
make
```
To use the library in your projects, include the header file and link the library:

```c
#include "libft.h"
```
```bash
gcc -L. -lft your_program.c
```
Lessons Learned

* **Standard Library Internals**: Gaining a deep understanding of how standard library  functions are implemented.
* **Memory and String Management**: Writing efficient and robust functions for memory and string operations.
* **Data Structures**: Implementing and managing linked list data structures.

## Conclusion

The Libft project provided a comprehensive understanding of standard library functions, memory management, and data structures in C, essential for writing efficient and robust code.
