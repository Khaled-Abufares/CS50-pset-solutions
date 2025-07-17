# CS50 Lecture 2: Arrays — Summary

This lecture introduces **arrays** and dives deeper into how data is stored and manipulated in memory. It also touches on strings, ASCII, command-line arguments, and basic debugging tools.

---

## Arrays

- An **array** is a fixed-size, ordered collection of elements of the same data type.
- In C:
    
    ```c
    int scores[3];
    scores[0] = 72;
    scores[1] = 73;
    scores[2] = 33;
    ```
    

Indexing starts at 0.

Arrays are stored in contiguous memory.

---

### Memory & Addresses

Every variable is stored at a memory address.

Use & to get the address of a variable:

printf("%p\n", &x);

Arrays are stored sequentially in memory:
scores[0] is directly before scores[1], and so on.

---

### Strings in C

A string is an array of characters ending with a special character: '\0' (null terminator).

Example:

string name = "CS50";

Equivalent to:

char name[] = {'C', 'S', '5', '0', '\0'};

---

### ASCII

ASCII is a standard for representing characters as numbers.

Example: 'A' = 65, 'B' = 66, 'a' = 97

---

### Loops & Strings

Looping through a string:

for (int i = 0; i < strlen(s); i++)
{
printf("%c\n", s[i]);
}

---

### Command-line Arguments

main() can accept arguments:

int main(int argc, string argv[])

argc: argument count

argv: argument values (array of strings)

Example:

./hello Khaled

argc = 2

argv[0] = "./hello"

argv[1] = "Khaled"

---

### Debugging with debug50 and printf

Use debug50 ./program to step through code line by line.

Insert printf() statements to inspect variable values and flow.

---

### Key Takeaways

Arrays group related data in memory.

Strings in C are arrays of char ending with '\0'.

Memory addresses help understand what's happening under the hood.

Command-line arguments allow dynamic input.

Debugging is essential — learn to use tools!

---

### Recommended Practice

Solve CS50's Pset2 problems (e.g., Caesar, Substitution).

Try printing memory addresses of array elements.

Build a command-line tool that accepts and prints user input.
