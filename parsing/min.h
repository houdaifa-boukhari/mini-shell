/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../mini_shell.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:35:37 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/05 10:58:05 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIN_H
#define MIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <string.h>
#include <readline/readline.h>
#include "libft/libft.h"
#include <stdbool.h>

#include <dirent.h>

// #ifndef g_exit_status
// #define g_exit_status

extern int	g_exit_status;

// #endif

# define TOKENS_ERROR "minishell: syntax error near unexpected token"
# define NEW_LINE_ERROR "minishell: syntax error near unexpected token `newline'\n"
// # define HEREDOC_ERROR "minishell: syntax error near unexpected token `<<'"
// # define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"
// # define IN_ERROR "minishell: syntax error near unexpected token `<'"
// # define OUT_ERROR "minishell: syntax error near unexpected token `>'"

# define QUOTES_ERROR "minishell: unexpected EOF while looking for matching"
# define AMBIGUOUS_ERROR "minishell: ambiguous redirect\n"
// # define SPACE_REDIRECTION_ERROR ": No such file or directory"

/////////////////////////////////////////////////
typedef struct s_envp
{
	char			*env;
	struct  s_envp	*prev;
	struct  s_envp	*next;
}	t_envp;

/////////////////////////////////////////////

typedef struct s_quote
{
	int	in_double_quote;
	int	in_single_quote;

}	t_quote;

typedef struct s_files
{
	char	*file;
	int		typ;
	char	*last;
	bool	is_q;
	bool	is_am;
}	t_files;


typedef struct s_out
{
	char	*out;
	bool	is_a;
	bool	is_am;
}	t_out;

typedef struct s_in
{
	char	*in;
	bool	is_h;
	bool	is_q;
	bool	is_am;
}	t_inp;
///////change_var////
typedef struct s_args_var
{
	int		x;
	int		l;
	char	*re;
	int		i;
	t_quote	q;
}	t_args_var;
/////////////////////

typedef struct s_args_n
{
	char			**arguments;
	t_files			*inp;
	t_inp			*in;
	t_out			*out;
	struct s_args_n	*next;
}	t_args_n;

char		**ft_split_pip(char *s, char c);
char		**split_part(char *s);
char		*set_speece( char *str);

char		*change_var(char *str, char **envp);
int			change_var_count(char *str, char **envp);
char		*get_name_var(char *str, int *j);
char		*search_in_env(char **envp, char *str);

char		**get_args(char **str);
t_files		*get_files(char **str,char **envp);

t_args_n	*initialization_list(char *line, char **envp);
void		ft_lstadd_backk(t_args_n **lst, t_args_n *new);
t_args_n	*ft_lstnew_one(char **str,char **envp);
void		ft_lstiterr(t_args_n *lst);
void		clear_list(t_args_n **lst);

char		*whithout_q(char *str,int is_wildcardss);

int			check_errors(char *str, int err);
int			chacke_q(char c, t_quote *q);
int			is_sp(char c);

int			check_ambiguous(char *str, char **envp);
char		*check_erroe_var(char *str, int x );
char		*strjoin_parsing(char *start, char *buff);
void		free_double_str(char **str);

int check_wildcards(char *str);
char **get_name_of_files(char *str );
int	last_wildcards(char *str, int x);
char	*chech_be(char *str, int x);
char	*check_aft(char *str, int x, int xx);
int	ch_f(char *str, char *name, int *i);
int	ch_m(char *str, char *name, int *i);
int	ch_l(char *str, char *name);
int	ft_strlen_doubl(char **str);


int check_doub(char *str);
void	change_var_tow_one(t_args_var *args, char *var, int j);
t_out *get_out(t_files *files);
t_inp *get_inp(t_files *files);
#endif