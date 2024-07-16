/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:10:44 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/16 13:16:29 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../parsing/min.h"

#define BLT_CMDS (char *[]){"cd", "echo", "pwd", "export", "unset", "env", "exit"}

typedef struct s_envp
{
	char			*env;
	struct s_envp	*prev;
	struct s_envp	*next;
}					t_envp;

typedef struct s_env
{
	char	**envp;
	t_envp	*env;
}			t_env;

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
	int	save_in;
	int	save_out;clea
	int	fd_p[2];
	int	pid;
}		t_fd;

void	ft_exit(char **cmd);
char	*get_path(char *cmd);
void	get_current_path(void);
char	*get_next_line(int fd);
void	print_env(t_envp *envp);
void	sorte_env(t_envp *head);
int		count_cmds(t_args_n *lst);
void	print_export(t_envp *envp);
int		*allocation_array(int size);
void	run_allherdoc(t_args_n *cmd);
void	change_directory(char **cmd);
void	managing_herdoc(char **delim);
void	handle_blt(char **cmd, t_env *env);
bool	is_builtin(char **cmd, t_env *env);
t_envp	*search_env(t_envp *env, char *str);
void	adding_env(t_envp **env, char *str);
void	creat_list(t_envp **envp, char *line);
void	parsing_env(t_envp **env, char **envp);
void	echo_handling(char **cmd, char **envp);
void	unset_hadnling(t_envp **env, char **cmd);
bool	managing_input(t_inp *input, t_fd *fd);
bool	managing_output(t_out *output, t_fd *fd);
void	export_handling(char **cmd, t_envp **envp);
void	execut_(t_args_n **cmds, t_env *env, t_fd fd);
void	execution(t_args_n **cmd, t_env *env, t_fd fd);
void	ft_error(t_args_n **cmd, char *msg, int status);

#endif