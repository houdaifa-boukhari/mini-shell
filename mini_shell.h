#ifndef MINI_SHELL
#define MINI_SHELL

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

#define BLT_CMDS (char *[]){"cd", "echo", "pwd", "export", "unset", "env", "exit"}

typedef struct s_cmd
{
    char            **cmd;
    struct  s_cmd   *next;
}                   t_cmd;

void	print_env(char **envp);
void    ft_exit(char **cmd);
char    *get_path(char *cmd);
bool	is_builtin(char *cmd);
void    get_current_path(void);
void	change_directory(char **cmd);
void	handle_blt(char **cmd, char **envp);
void    execution(char **cmd, char **envp);
void    echo_handling(char **cmd, char **envp);

#endif