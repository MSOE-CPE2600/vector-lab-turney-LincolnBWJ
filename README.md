# Vector Calculator Project

### CPE-2600 Systems Programming

---

## Description

This is a simple command-line program that works as a 3D vector calculator. It lets a user load, save, and manage a list of vectors interactively.

## How to Build

To build the program, run the `make` command from the project directory.

```
make
```

## How to Run

After building, run the program from your terminal like this: 

```
./vector_calc
```

The program does not take any command line options.

## Program Commands

The program supports the following commands:

* `list`: Shows all vectors currently in memory.
* `load <filename>`: Loads vectors from a CSV file.
* `save <filename>`: Saves vectors to a CSV file.
* `add <n> <x> <y> <z>`: Adds a new vector.
* `clear`: Removes all vectors.
* `exit`: Quits the program.

## Dynamic Memory Usage

This program uses dynamic memory to store vectors. It starts with a small array and uses `realloc` to automatically grow the array's size whenever it runs out of space. Memory is released when the program exits to prevent leaks.
