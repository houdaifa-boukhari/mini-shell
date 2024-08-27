/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_tow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:05:06 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/27 09:12:13 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	last_wildcards(char *str, int x)
{
	t_quote	q;
	int		l;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if (!l && str[x] == '*')
			return (0);
		x++;
	}
	return (1);
}

int	ft_strlen_doubl(char **str)
{
	int	x;

	x = 0;
	if (!str)
		return (0);
	while (str[x])
	{
		x++;
	}
	return (x);
}
