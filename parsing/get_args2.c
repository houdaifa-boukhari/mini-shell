/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:50:38 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/21 20:36:56 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"

static int	whithout_q_count(char *str, int x)
{
	int		c;
	int		l;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	c = 0;
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if ((str[x] == '"' || str[x] == '\''))
		{
			if ((l == 1 && str[x] == '"') || (l == 2 && str[x] == '\''))
				c++;
		}
		else
			c++;
		x++;
	}
	return (c);
}

char	*whithout_q(char *str)
{
	char	*re;
	int		x;
	int		c;
	int		l;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	x = 0;
	c = 0;
	if (!str)
		return (NULL);
	re = malloc(whithout_q_count(str, x) + 1);
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if ((l == 1 && str[x] == '"') || (l == 2 && str[x] == '\''))
			re[c++] = str[x];
		else if (str[x] != '"' && str[x] != '\'')
			re[c++] = str[x];
		x++;
	}
	re[c] = '\0';
	return (re);
}

static int	get_args_count(char **str)
{
	int	x;
	int	c;

	x = 0;
	c = 0;
	while (str[x])
	{
		if (str[x + 1] && (ft_strncmp(str[x], "<", 2) == 0
				|| ft_strncmp(str[x], ">", 2) == 0
				|| ft_strncmp(str[x], "<<", 3) == 0
				|| ft_strncmp(str[x], ">>", 3) == 0))
			x++;
		else
			c++;
		x++;
	}
	return (c);
}

char	**get_args(char **str)
{
	char	**re;
	int		x;
	int		c;

	x = 0;
	c = 0;
	re = (char **)malloc((get_args_count(str) + 1) * sizeof(char *));
	while (str[x])
	{
		if (str[x + 1] && (ft_strncmp(str[x], "<", 2) == 0
				|| ft_strncmp(str[x], ">", 2) == 0
				|| ft_strncmp(str[x], "<<", 3) == 0
				|| ft_strncmp(str[x], ">>", 3) == 0))
			x++;
		else
			re[c++] = whithout_q(str[x]);
		x++;
	}
	re[c] = NULL;
	return (re);
}

// int main()
// {
//     char *str0 ="ls \"\" -a \"\" -l";
//     char *str1 ="l\"s\"> \"hello  <'worde\"  \"-l -a\" \"\">\"\" 'out'";
//     char *str2 ="l\"s\"< 'hello  \">> worde'  \"-l -a\">> out >f";
//     char *str3 ="<'cat'\"<\" \" min '2\" \"-e\"";
//     char *str4 = "'ca't file >out >>out1<< stop out2 > out3 \"-e\" -l";
//     char *str5 ="ls";
//     printf("%s\n",str5);
// //    printf("%s\n", set_speece(str3));
// char ** str =split_part(set_speece(str5));
// int x =0;
// // while (str[x])
// // {
// //     printf("%s\n",str[x]);
// //     x++;
// // }
// // // printf("x==%d\n",x);
// // // printf("--------------------\n");
// // // printf("cmd=%s\n",get_cmd2(str) ? get_cmd2(str):"(null)");
// // // char **flags=get_flags2(str);
// // // x =0;
// // // while (flags && flags[x])
// // // {
// // //     printf("flag%d =%s\n",x,flags[x]);
// // //     x++;
// // // }
// // x =0;
// // char **args =get_args(str); 
// // while (args[x])
// // {
// //     printf("arg[%d]=%s\n",x,args[x]);
// //    x++;
// // }
// // // get_args(str);
// // // printf("%s\n" , whithout_q("    cat ffr"));
// // x =0;
// t_out *out =get_out(str);
// while (out[x].out)
// {
//     printf("out file [%d]:%s\n",x,out[x].out);
//     printf("is append [%d]:%d\n",x,out[x].is_a);
//     x++;
// }
// x =0;
// t_inp *inp =get_inp(str);
// while (inp[x].inp)
// {
//     printf("inp file [%d]:%s\n",x,inp[x].inp);
//     printf("is Heredoc [%d]:%d\n",x,inp[x].is_h);
//     x++;
// }
// }