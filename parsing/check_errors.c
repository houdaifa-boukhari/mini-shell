/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-26 21:08:16 by zbakkas           #+#    #+#             */
/*   Updated: 2024-07-26 21:08:16 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"

int	check_errors_p(char *str, int l, int *x)
{

	if (!l && !str[(*x) + 1] && str[(*x)] == '|')
		return (printf("%s `%c'\n", TOKENS_ERROR, str[(*x)++]), 1);
	else if (!l && (str[(*x)] == '<' || str[(*x)] == '>'))
	{
		(*x)++;
		if (str[(*x)] == str[(*x) - 1])
			(*x)++;
		while (str[(*x)] && str[(*x)] == ' ')
			(*x)++;
		if (!str[(*x)])
			return (printf("%s\n", NEW_LINE_ERROR), 1);
		else if (str[(*x)] == '|' || str[(*x)] == '<' || str[(*x)] == '>')
			return (printf("%s `%c'\n", TOKENS_ERROR, str[(*x)++]), 1);
	}
	else
		(*x)++;
	return (0);
}

int	check_errors(char *str, int err)
{
	int		x;
	int		l;
	t_quote	q;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	x = 0;
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if (check_errors_p(str, l, &x))
			return (1);
	}
	if (l == 2)
		return (printf("%s `%c'\n", QUOTES_ERROR, '"'), 1);
	else if (l == 1)
		return (printf("%s `%c'\n", QUOTES_ERROR, '\''), 1);
	if (err)
		return (printf("%s\n", AMBIGUOUS_ERROR), 1);
	return (0);
}
