/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_speace_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-26 21:40:50 by zbakkas           #+#    #+#             */
/*   Updated: 2024-07-26 21:40:50 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"

//re+=2 >> add after and befor
int	set_speece_count(char *str)
{
	int		x;
	t_quote	q;
	int		re;

	x = 0;
	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	re = ft_strlen(str);
	while (str[x])
	{
		if (!chacke_q(str[x], &q) && (str[x] == '>' || str[x] == '<'))
		{
			re += 2;
			while (str[x] == '>' || str[x] == '<')
				x++;
		}
		else
			x++;
	}
	return (re);
}

char	*set_speece(char *str)
{
	char	*re;
	int		x;
	int		i;
	t_quote	q;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	re = malloc(set_speece_count(str) + 1);
	x = 0;
	i = 0;
	while (str[x])
	{
		if (!chacke_q(str[x], &q) && (str[x] == '>' || str[x] == '<'))
		{
			re[i++] = ' ';
			while (str[x] == '>' || str[x] == '<')
				re[i++] = str[x++];
			re[i++] = ' ';
		}
		else
			re[i++] = str[x++];
	}
	re[i] = '\0';
	return (re);
}

