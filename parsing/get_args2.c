/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:50:38 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/27 09:23:22 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	get_args_count_if(char **str, int x)
{
	if (str[x + 1] && (ft_strncmp(str[x], "<", 2) == 0 || ft_strncmp(str[x],
				">", 2) == 0 || ft_strncmp(str[x], "<<", 3) == 0
			|| ft_strncmp(str[x], ">>", 3) == 0))
		return (1);
	return (0);
}

static int	get_args_count(char **str)
{
	int		x;
	int		c;
	char	**ss;

	x = -1;
	c = 0;
	while (str[++x])
	{
		if (get_args_count_if(str, x))
			x++;
		else if (check_wildcards(str[x]))
		{
			ss = get_name_of_files(str[x]);
			if (ft_strlen_doubl(ss) > 0)
				c += ft_strlen_doubl(ss);
			else
				c++;
			free_double_str(ss);
		}
		else
			c++;
	}
	return (c);
}

static void	grt_arg_one(char **str, int x, char **re, int *c)
{
	char	**ss;
	int		j;

	j = 0;
	ss = get_name_of_files((str[x]));
	if (ft_strlen_doubl(ss) > 0)
	{
		j = 0;
		while (ss[j])
			re[(*c)++] = ss[j++];
	}
	else
		re[(*c)++] = whithout_q(str[x], 0);
	free(ss);
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
		if (str[x + 1] && (ft_strncmp(str[x], "<", 2) == 0 || ft_strncmp(str[x],
					">", 2) == 0 || ft_strncmp(str[x], "<<", 3) == 0
				|| ft_strncmp(str[x], ">>", 3) == 0))
			x++;
		else if (check_wildcards(str[x]))
		{
			grt_arg_one(str, x, re, &c);
		}
		else
			re[c++] = whithout_q(str[x], 0);
		x++;
	}
	re[c] = NULL;
	return (re);
}
