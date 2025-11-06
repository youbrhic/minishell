# 🐚 minishell

> A simple shell written in C as part of the [42 School] curriculum.  
> The goal of this project is to create a miniature version of **bash**, learning how a real shell works behind the scenes.

---

## 📘 Project Overview

`minishell` is a small shell implementation that mimics the basic behavior of the **bash** terminal.  
It handles command parsing, environment variables, pipes, redirections, and built-in commands —  
all while managing processes and signals like a real Unix shell.

This project is a deep dive into:
- Process control (`fork`, `execve`, `waitpid`)
- File descriptors & redirections (`dup2`, `pipe`)
- Signal handling (`SIGINT`, `SIGQUIT`, `SIGTERM`)
- Lexical parsing and tokenization
- Environment management and variable expansion

---

## ✨ Features

✅ Display a working **prompt**  
✅ Execute commands from **PATH** or by absolute/relative path  
✅ Handle **quotes** (`'`, `"`) correctly  
✅ Expand **environment variables** (`$VAR`)  
✅ Support **redirections**:
  - Output: `>`
  - Append: `>>`
  - Input: `<`
  - Heredoc: `<<`
✅ Support **pipes** (`|`)  
✅ Manage **exit statuses** and **error messages**  
✅ Implement **built-in commands**:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
  
✅ Handle **signals** like Bash:
  - `Ctrl+C` → interrupts current command
  - `Ctrl+D` → exits the shell
  - `Ctrl+\` → ignored

---

## 🧱 Project Structure

```
minishell/
├── Makefile
├── README
├── main.c
├── minishell.h
│
├── butlin/
│   ├── ft_cd.c
│   ├── ft_echo.c
│   ├── ft_env.c
│   ├── ft_exit.c
│   ├── ft_export.c
│   ├── ft_pwd.c
│   └── ft_unset.c
│
├── execution/
│   ├── exec_fun.c
│   ├── ft_create_file.c
│   ├── ft_excev_cmd.c
│   ├── ft_exec_bultin.c
│   ├── ft_exec_cmd.c
│   ├── ft_exec_list.c
│   ├── ft_hardoc.c
│   └── ft_open_file.c
│
├── parsing/
│   ├── ft_add_space.c
│   ├── ft_create_list.c
│   ├── ft_create_node.c
│   ├── ft_expand.c
│   ├── ft_get_nodes.c
│   ├── ft_parse_line.c
│   ├── ft_remove_quotes.c
│   ├── ft_token_cmds.c
│   └── parse_export.c
│
├── signals/
│   └── signals.c
│
└── util/
    ├── env_util.c
    ├── export_tools.c
    ├── ft_split.c
    ├── ft_split_cmd.c
    ├── ft_split_cmd_util.c
    ├── libft_util.c
    ├── libft_util2.c
    ├── libft_util3.c
    ├── libtf_util4.c
    ├── other_util.c
    └── other_util2.c
```