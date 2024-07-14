/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:35:37 by zbakkas           #+#    #+#             */
/*   Updated: 2024/07/14 14:03:27 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "../execution/libft/libft.h"
#include <stdbool.h>


typedef struct s_inp
{
    char    *inp;
    bool    is_h;
}           t_inp;

typedef struct s_out
{
    char    *out;
    bool    is_a;
}           t_out;

typedef struct s_args_n
{
    char **arguments;
    t_inp *inp;
    t_out *out;
    struct s_args_n *next;
} t_args_n;


char * get_str_redline();
char *change_var(char * str);
char	**ft_split_pip(char  *s, char c);
char **split_part(char *s);
char *set_speece( char *str) ;


// char *get_argumants(char *str);
// char **get_flages(char *str);
// char *get_cmd(char *str);
char **get_args(char **str);
t_out *get_out(char **str);
t_inp *get_inp(char **str);

t_args_n *initialization_list(char *line);
void	ft_lstadd_backk(t_args_n **lst, t_args_n *new);
t_args_n	*ft_lstnew_one(char **str);
void	ft_lstiterr(t_args_n *lst);
void	clear_list(t_args_n **lst);