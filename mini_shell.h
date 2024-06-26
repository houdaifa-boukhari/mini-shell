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

typedef struct s_envp
{
	char			*env;
	struct  s_envp	*next;
}                   t_envp;

void    ft_exit(char **cmd);
char    *get_path(char *cmd);
bool	is_builtin(char *cmd);
void    get_current_path(void);
void	print_env(t_envp *envp);
void	print_export(t_envp *envp);
void	change_directory(char **cmd);
void    execution(char **cmd, char **envp);
void	parsing_env(t_envp **env, char **envp);
void    echo_handling(char **cmd, char **envp);
void	export_handling(char **cmd, t_envp *envp);
void	handle_blt(char **cmd, t_envp *env, char **envp);

#endif