# 🔄 Pipex

A command pipeline implementation in C that mimics the shell pipe operator (`|`). Part of the School 1337 cursus.

## 📋 Project Structure

```
📦 Pipex
├── 📂 bonus/           # Bonus implementation files
├── 📂 get_next_line/   # GNL implementation for here_doc
├── 📂 utils/           # Utility functions
├── 📄 Makefile        # Compilation rules
├── 📄 parsing_arg.c   # Argument parsing implementation
├── 📄 pipex.c         # Main program logic
└── 📄 pipex.h         # Header file with prototypes
```

## 🎯 Description

Pipex recreates the Unix pipe mechanism, allowing command output redirection between processes. The program implements the functionality of the shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

## ⚡ Features

- ✨ Basic Pipeline: `./pipex infile cmd1 cmd2 outfile`
- 📚 Multiple Commands Support (Bonus)
- 📝 Here Document Support (Bonus)
- 🔍 Command Path Resolution
- ⚠️ Error Handling

## 🛠️ Installation

```bash
# Clone the repository
git clone https://github.com/Serghini04/Pipex.git

# Navigate to the project directory
cd Pipex

# Compile the program
make          # For mandatory part
make bonus    # For bonus features
```

## 💻 Usage

### Basic Usage
```bash
./pipex infile "cmd1" "cmd2" outfile
```

### Examples

1. Count number of lines:
```bash
./pipex infile "ls -l" "wc -l" outfile
```

2. Search and replace:
```bash
./pipex infile "grep text" "sed s/text/replaced/" outfile
```

## 🔧 Implementation Details

### Core Files
- `pipex.c`: Main program implementation
- `pipex.h`: Header file containing:
  - Function prototypes
  - Structure definitions
  - Required includes
- `parsing_arg.c`: Command-line argument parsing
- `Makefile`: Compilation rules and targets

### Utils Directory
Contains helper functions for:
- String manipulation
- Memory management
- Error handling

### Bonus Implementation
- Multiple pipe handling
- Here document (`<<`) support
- Append mode (`>>`) support

## ⚙️ Technical Requirements

- C Language
- Norm Compliant (42 School Code Standards)
- No Memory Leaks
- Error Handling
- Limited Set of Allowed Functions:
  - `fork`, `pipe`, `execve`, `dup2`
  - `open`, `close`, `read`, `write`
  - `malloc`, `free`
  - `perror`, `strerror`
  - `access`, `unlink`
  - `exit`, `wait`, `waitpid`

## 🐛 Error Handling

The program handles various error cases:
- File access permissions
- Invalid commands
- Memory allocation failures
- Fork/pipe failures
- Invalid number of arguments

## 🚀 Bonus Features

1. Multiple Pipes:
```bash
./pipex infile "cmd1" "cmd2" "cmd3" outfile
```

2. Here Document:
```bash
./pipex here_doc DELIMITER "cmd1" "cmd2" outfile
```

## 📝 Notes

- All memory allocations are properly freed
- File descriptors are properly managed
- Commands are executed with their full path
- Error messages are clear and informative

## 🔑 Testing

```bash
# Basic test
./pipex infile "ls -l" "wc -l" outfile

# Multiple commands (bonus)
./pipex infile "ls" "grep .c" "wc -l" outfile

# Here_doc (bonus)
./pipex here_doc END "cat" "grep hello" outfile
```

## 📚 Resources

- Unix Processes
- File Descriptors
- Pipe Communication
- Fork and Execve
- Shell Command Execution

## 🌟 Tips for Development

1. Always check system call return values
2. Free resources in the correct order
3. Handle edge cases carefully
4. Test with various command combinations
5. Ensure proper file descriptor management
6. Use valgrind to check for memory leaks

---
This project is part of the School 1337 curriculum.
