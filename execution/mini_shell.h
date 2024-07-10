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
# include "../parsing/min.h"

#define BLT_CMDS (char *[]){"cd", "echo", "pwd", "export", "unset", "env", "exit"}

typedef struct s_envp
{
	char			*env;
	struct  s_envp	*prev;
	struct  s_envp	*next;
}                   t_envp;

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
	int	save_in;
	int	save_out;
	int	fd_p[2];
	int	pid;
}		t_fd;

void    ft_exit(char **cmd);
char    *get_path(char *cmd);
bool	is_builtin(char *cmd);
void    get_current_path(void);
char	*get_next_line(int fd);
void	print_env(t_envp *envp);
void    sorte_env(t_envp *head);
int		count_cmds(t_args_n *lst);
void	print_export(t_envp *envp);
void	change_directory(char **cmd);
t_envp	*search_env(t_envp *env, char *str);
void	adding_env(t_envp **env, char *str);
void    creat_list(t_envp **envp, char *line);
void	parsing_env(t_envp **env, char **envp);
void    echo_handling(char **cmd, char **envp);
void	unset_hadnling(t_envp **env, char *str);
void	managing_herdoc(char *delim, t_fd *fd);
bool	managing_input(t_inp *input, t_fd *fd);
bool	managing_output(t_out *output, t_fd *fd);
void	export_handling(char **cmd, t_envp *envp);
void	execut_(t_args_n *cmds, char **envp, t_fd fd);
void    execution(t_args_n *cmd, char **envp, t_fd fd);
void	handle_blt(char **cmd, t_envp **env, char **envp);

#endif