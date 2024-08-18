/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:10:44 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/16 16:47:43 by hel-bouk         ###   ########.fr       */
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

extern int	g_exit_status;

typedef struct s_env
{
	char	**envp;
	t_envp	*env;
	bool	check;
}			t_env;

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
	int	save_in;
	int	save_out;
	int	fd_p[2];
	int	pid;
}		t_fd;

int		check_line(char *str);
int		size_env(t_envp *lst);
void	free_env(t_envp **env);
int		get_current_path(void);
char	*get_next_line(int fd);
bool	valid_export(char *str);
int		print_env(t_envp *envp);
void	sorte_env(t_envp *head);
void	remove_file(t_inp *inp);
void	built_array(t_env *env);
int		count_cmds(t_args_n *lst);
void	print_export(t_envp *envp);
int		*allocation_array(int size);
bool	run_allherdoc(t_args_n *cmd, t_env *env);
bool	managing_herdoc(char **delim, t_env *env);
char	*get_path(char *cmd, char **envp);
void	change_fd_ouput(int fd, int cfd);
void	signal_handler(int signal);
char	*strjoin(char *str, char *str1);;
void	change_fd_in(int fd, t_args_n **cmd);
t_envp	*search_env(t_envp *env, char *str);
bool	adding_env(t_envp **env, char *str);
void	ft_exit(t_args_n **args, char **cmd);
void	creat_list(t_envp **envp, char *line);
char	*search_in_env(char **envp, char *str);
void	parsing_env(t_envp **env, char **envp);
int		echo_handling(char **cmd, char **envp);
bool	managing_input(t_inp *input, t_fd *fd);
int		unset_hadnling(t_envp **env, char **cmd);
bool	managing_output(t_out *output, t_fd *fd);
int		change_directory(char **cmd, char **env);
bool	export_handling(char **cmd, t_envp **envp);
void	execut_(t_args_n **cmds, t_env *env, t_fd fd);
void	execution(t_args_n **cmd, t_env *env, t_fd fd);
void	ft_error(t_args_n **cmd, char *msg, int status);
void	handle_blt(t_args_n **args, char **cmd, t_env *env);
bool	is_builtin(t_args_n **args, char **cmd, t_env *env, t_fd fd);

#endif