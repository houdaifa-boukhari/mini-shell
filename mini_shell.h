/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:10:44 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/22 10:30:27 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

extern int			g_exit_status;

# define AMBIGUOUS_ERROR "minishell: ambiguous redirect\n"
# define TOKENS_ERROR "minishell: syntax error near unexpected token"
# define QUOTES_ERROR "minishell: unexpected EOF while looking for matching"
# define NEW_LINE_ERROR "minishell: syntax error near unexpected token \
`newline'\n"

typedef struct s_envp
{
	char			*env;
	struct s_envp	*prev;
	struct s_envp	*next;
}					t_envp;

typedef struct s_env
{
	char			**envp;
	t_envp			*env;
	bool			check;
}					t_env;

typedef struct s_quote
{
	int				in_double_quote;
	int				in_single_quote;

}					t_quote;

typedef struct s_inp
{
	char			*inp;
	bool			is_h;
}					t_inp;

typedef struct s_out
{
	char			*out;
	bool			is_a;
}					t_out;

typedef struct s_args_var
{
	int				x;
	int				l;
	char			*re;
	int				i;
	t_quote			q;
}					t_args_var;

typedef struct s_args_n
{
	char			**arguments;
	t_inp			*inp;
	t_out			*out;
	struct s_args_n	*next;
}					t_args_n;

typedef struct s_fd
{
	int				fd_in;
	int				fd_out;
	int				save_in;
	int				save_out;
	int				fd_p[2];
	int				pid;
}					t_fd;

int					check_line(char *str);
int					size_env(t_envp *lst);
void				free_env(t_envp **env);
int					get_current_path(void);
char				*get_next_line(int fd);
bool				valid_export(char *str);
int					print_env(t_envp *envp);
void				sorte_env(t_envp *head);
void				remove_file(t_inp *inp);
void				built_array(t_env *env);
int					count_cmds(t_args_n *lst);
void				print_export(t_envp *envp);
int					*allocation_array(int size);
bool				run_allherdoc(t_args_n *cmd, t_env *env);
bool				managing_herdoc(char **delim, t_env *env);
char				*get_path(char *cmd, char **envp);
void				change_fd_ouput(int fd, int cfd);
void				signal_handler(int signal);
void				wait_child(t_fd fd);
void				error_files(char *file);
char				*strjoin(char *str, char *str1);
void				change_fd_in(int fd, t_args_n **cmd);
t_envp				*search_env(t_envp *env, char *str);
bool				adding_env(t_envp **env, char *str);
void				ft_exit(t_args_n **args, char **cmd);
void				creat_list(t_envp **envp, char *line);
char				*search_in_env(char **envp, char *str);
void				parsing_env(t_envp **env, char **envp);
int					echo_handling(char **cmd);
int					unset_hadnling(t_envp **env, char **cmd);
char				*handle_var(char *re, char *line, int *x, t_env *env);
bool				managing_input(t_inp *input, t_fd *fd, int count,
						bool *flag);
bool				managing_output(t_out *output, t_fd *fd, int count,
						bool *flag);
int					change_directory(char **cmd, char **env);
bool				export_handling(char **cmd, t_envp **envp);
void				execut_(t_args_n **cmds, t_env *env, t_fd fd);
void				execution(t_args_n **cmd, t_env *env, t_fd fd);
void				ft_error(t_args_n **cmd, char *msg, int status);
void				handle_blt(t_args_n **args, char **cmd, t_env *env);
bool				is_builtin(t_args_n **args, char **cmd, t_env *env,
						t_fd fd);

/*parsing functions*/

int					is_sp(char c);
t_out				*get_out(char **str);
t_inp				*get_inp(char **str);
char				**split_part(char *s);
char				**get_args(char **str);
char				*whithout_q(char *str);
char				*set_speece(char *str);
t_args_n			*ft_lstnew_one(char **str);
void				clear_list(t_args_n **lst);
int					chacke_q(char c, t_quote *q);
char				**ft_split_pip(char *s, char c);
int					check_errors(char *str, int err);
char				*get_name_var(char *str, int *j);
char				*check_erroe_var(char *str, int x);
char				*search_in_env(char **envp, char *str);
int					change_var_count(char *str, char **envp);
char				*strjoin_parsing(char *start, char *buff);
t_args_n			*initialization_list(char *line, char **envp);
char				*change_var(char *str, char **envp, int *err);
void				ft_lstadd_backk(t_args_n **lst, t_args_n *new);
int					check_ambiguous(char *str, char **envp, int err);

#endif