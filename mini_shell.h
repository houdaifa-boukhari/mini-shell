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

#define BLT_CMDS (char *[]){"cd", "export", "unset", "exit"}

typedef struct s_cmd
{
    char            **cmd;
    struct  s_cmd   *next;
}                   t_cmd;

void    ft_exit(char **cmd);
char    *get_path(char *cmd);
void	handle_blt(char **cmd);
bool	is_builtin(char *cmd);
void    execution(char **cmd, char **envp);

#endif