# Simple Shell Project

## Overview

This project implements a minimal Unix-like shell in C. The shell reads user input, parses it into commands and arguments, handles a few built-in commands, searches for executables in the system `PATH`, and executes programs using process creation.

---

## Features

* Custom command parsing with support for quoted strings
* Built-in commands:

  * `exit` – exits the shell
  * `env` – prints environment variables
* Execution of external programs
* PATH resolution for commands
* Basic memory management

---

## File Structure & Function Descriptions

### 1. Command Tokenization

#### `cmd_tok`

Splits a command string into tokens (arguments).

* Supports spaces, tabs, and newlines as delimiters
* Handles quoted strings (`" "` or `' '`) as single arguments
* Uses a save pointer to maintain state between calls

**Example:**

```
Input:  echo "hello world"
Output: ["echo", "hello world"]
```

---

### 2. Memory Management

#### `free_string_array`

Frees a dynamically allocated array of strings.

* Frees each string individually
* Frees the array itself

---

### 3. Environment Handling

#### `_getenv`

Custom implementation of `getenv`.

* Searches `environ` for a variable
* Returns pointer to its value if found

#### `print_env`

Prints all environment variables to standard output.

---

### 4. Utility Functions

#### `array_length`

Counts the number of elements in a NULL-terminated string array.

#### `prompt`

Displays the shell prompt.

* Only prints if input is from a terminal (`isatty`)

---

### 5. PATH Resolution

#### `search_path`

Searches for an executable in the system `PATH`.

* Splits `PATH` using `:`
* Builds full file paths and checks existence
* Optionally replaces the command with its absolute path

**Return values:**

* `0` → Found
* `1` → Not found

---

### 6. Shell Execution Flow

#### `main`

Entry point of the program.

* Runs a loop that repeatedly calls `shell()`
* Exits when `shell()` returns `1`

---

#### `shell`

Handles one iteration of the shell loop.

1. Prints prompt
2. Reads input using `getline`
3. Removes trailing newline
4. Converts input into argument array
5. Passes arguments to `run_command`

---

#### `run_command`

Executes user commands.

**Built-in commands:**

* `exit` → terminates shell
* `env` → prints environment variables

**External commands:**

1. Checks if command exists or searches `PATH`
2. If not found → prints error
3. If found:

   * Creates child process (`fork`)
   * Executes program (`execve`)
   * Parent waits for completion (`wait`)

---

### 7. String Parsing

#### `str_to_arr`

Converts a command string into an array of arguments.

**Process:**

1. First pass → count tokens
2. Allocate memory
3. Second pass → duplicate tokens into array

**Example:**

```
Input:  ls -l /home
Output: ["ls", "-l", "/home", NULL]
```

---

## Program Flow

```
main()
  ↓
shell()
  ↓
getline() → user input
  ↓
str_to_arr() → argument array
  ↓
run_command()
  ↓
  ├── built-in command
  └── external command
        ↓
    search_path()
        ↓
    fork()
        ↓
    execve()
```

---

## Notes & Considerations

* The tokenizer modifies the input string in-place
* Memory is dynamically allocated and freed appropriately
* The shell does not yet support advanced features like:

  * piping (`|`)
  * redirection (`>`, `<`)

---

## Future Improvements

* Add support for pipes and redirection
* Implement command history
* Improve error handling
* Support environment variable expansion
* Add signal handling (e.g., Ctrl+C)

---

## Compilation

```
gcc -Wall -Werror -Wextra -pedantic *.c -o shell
```

---

## Usage

```
./shell
```

Example:

```
shell$ ls -l
shell$ echo "Hello World"
shell$ env
shell$ exit
```

---

## Summary

This project demonstrates the core components of a simple shell:

* Input handling
* Tokenization
* Command execution
* Process control

