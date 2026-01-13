# 🐚 Minishell

A simple shell implementation written in C, developed as part of the [42 School](https://42.fr/) curriculum.  This project recreates the core functionalities of bash, providing hands-on experience with process management, file descriptors, and Unix system calls.

## 📋 Table of Contents

- [About](#-about)
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Built-in Commands](#-built-in-commands)
- [Technical Implementation](#-technical-implementation)
- [Skills Demonstrated](#-skills-demonstrated)
- [Author](#-author)

## 📖 About

Minishell is a simplified version of a Unix shell that interprets and executes user commands. This project was an opportunity to dive deep into how shells work under the hood, from parsing user input to managing child processes and handling signals.

The shell mimics the behavior of **bash**, handling complex command structures while maintaining clean and efficient code following the [42 Norm](https://github.com/42School/norminette).

## ✨ Features

- **Interactive prompt** with command history (using readline)
- **Command execution** with absolute, relative, or PATH-resolved binaries
- **Pipes** (`|`) to chain multiple commands
- **Redirections**:
  - `<` Input redirection
  - `>` Output redirection
  - `<<` Heredoc (with delimiter)
  - `>>` Append output
- **Environment variable expansion** (`$VAR`, `$? ` for exit status)
- **Quote handling** (single `'` and double `"` quotes)
- **Signal handling** (Ctrl+C, Ctrl+D, Ctrl+\\)
- **Exit status** management

## 🛠️ Installation

### Prerequisites

- GCC or Clang compiler
- Make
- readline library

### Building

```bash
# Clone the repository
git clone https://github.com/PyrrhaSchnee/42_minishell.git

# Navigate to the project directory
cd 42_minishell

# Compile the project
make

# The executable 'minishell' will be created
```

### Cleaning

```bash
# Remove object files
make clean

# Remove object files and executable
make fclean

# Rebuild the project
make re
```

## 🚀 Usage

```bash
# Launch the shell
./minishell

# You will see a prompt where you can enter commands
minishell$ echo "Hello, World!"
Hello, World!

minishell$ ls -la | grep minishell
-rwxr-xr-x  1 user  staff  52432 Jan 13 12:00 minishell

minishell$ cat < input.txt | grep "pattern" > output.txt

minishell$ exit
```

## 📜 Built-in Commands

| Command | Description |
|---------|-------------|
| `echo` | Display text with optional `-n` flag (no newline) |
| `cd` | Change current directory |
| `pwd` | Print working directory |
| `export` | Set environment variables |
| `unset` | Remove environment variables |
| `env` | Display environment variables |
| `exit` | Exit the shell with optional status code |

## 🔧 Technical Implementation

### Architecture

```
minishell
├── Lexer/Tokenizer  → Breaks input into tokens
├── Parser           → Builds command structure
├── Expander         → Handles $VAR and quote removal
├── Executor         → Forks and executes commands
└── Built-ins        → Internal command implementations
```

### Key Components

- **Tokenization** (`token*. c`): Lexical analysis of user input, handling quotes and special characters
- **Heredoc** (`heredoc*.c`): Implementation of `<<` with temporary file handling
- **Execution** (`exec*.c`): Process forking, piping, and command execution
- **Redirections** (`redir_sanitizer*. c`): File descriptor management for I/O redirections
- **Environment** (`envp_expansion*.c`, `env. c`, `export*. c`): Environment variable handling and expansion
- **Signals** (`signal*.c`): Custom signal handlers for interactive and non-interactive modes
- **libft**:  Custom C library with utility functions

### Memory Management

The project implements careful memory management with dedicated cleanup functions (`clean_all.c`) to prevent memory leaks, verified using Valgrind with a custom suppression file for readline library leaks.
The memory safety can also be verified by runtime ASAN+UBSAN+LSAN.

## 💼 Skills Demonstrated

This project showcases proficiency in: 

| Category | Skills |
|----------|--------|
| **Systems Programming** | Process management, fork/exec, file descriptors, signals |
| **C Programming** | Pointers, memory allocation, data structures, parsing |
| **Unix/Linux** | Shell behavior, environment variables, file I/O |
| **Problem Solving** | Handling edge cases, complex parsing logic |
| **Code Quality** | Clean code, modular design, norm compliance |
| **Debugging** | Memory leak detection, edge case testing |

## 📚 Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
  
## 👤 Author

**Yang**

- GitHub: [@PyrrhaSchnee](https://github.com/PyrrhaSchnee)
  
---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. 

---

*This project was completed as part of the 42 School curriculum.  It represents approximately 210 hours of work and demonstrates strong systems programming fundamentals.*
