# **Minishell**

**Minishell** is a simple Unix shell implementation written in C. This project mimics basic shell functionalities such as command execution, piping, redirection, environment variable management, and signal handling. It provides a custom, minimalistic shell experience for interacting with the system.

---

## **Features**

- **Command Execution**: Executes user commands by forking new processes and using `execve` to execute the desired program.
- **Pipes**: Supports piping between commands using the `|` operator.
- **Redirection**: Handles input and output redirection with the `>` and `<` operators.
- **Background Execution**: Runs commands in the background using the `&` operator.
- **Environment Variables**: Supports reading and modifying environment variables, including commands like `echo $VAR`, `export VAR=VALUE`, and `unset VAR`.
- **Built-in Commands**:
  - `echo`: Prints arguments to the console.
  - `cd`: Changes the current working directory.
  - `pwd`: Prints the current working directory.
  - `export`: Exports environment variables.
  - `unset`: Unsets environment variables.
  - `exit`: Exits the shell.
- **Signal Handling**: Custom handling of signals such as `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\).
- **Custom Prompt**: Displays a custom prompt (`$ `) for user interaction.
- **Command History**: Implements basic command history using the `history` command.
- **Argument Parsing**: Parses and tokenizes user input for command execution, supporting pipes and redirection.
- **Error Handling**: Includes detailed error messages and handling for invalid commands or incorrect syntax.
