/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:08:16 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/20 11:19:01 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"

static void	print_err(char *str, char c)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd(' ', 2);
	ft_putchar_fd('`', 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd('\n', 2);
}

int	check_errors_p(char *str, int l, int *x, int first_p)
{
	if ((!l && !str[(*x) + 1] && str[(*x)] == '|' ) 
		|| (!l && str[(*x)] == '|' && (first_p) == *x))
		return (g_exit_status = 258, print_err(TOKENS_ERROR, str[(*x)++]), 1);
	else if (!l && (str[(*x)] == '<' || str[(*x)] == '>' || str[(*x)] == '|'))
	{
		(*x)++;
		if (str[(*x)] == str[(*x) - 1])
			(*x)++;
		while (str[(*x)] && is_sp(str[(*x)]))
			(*x)++;
		if (!str[(*x)])
			return (g_exit_status = 258, ft_putstr_fd(NEW_LINE_ERROR, 2), 1);
		else if (str[(*x)] == '|' || str[(*x)] == '<' || str[(*x)] == '>')
		{
			g_exit_status = 258;
			print_err(TOKENS_ERROR, str[(*x)++]);
			return (1);
		}
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
	int		first_p;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	first_p = 0;
	x = 0;
	while (str[x] && is_sp(str[x]))
		x++;
	first_p = x;
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if (check_errors_p(str, l, &x, first_p))
			return (1);
	}
	if (l == 2)
		return (g_exit_status = 258, print_err(QUOTES_ERROR, '"'), 1);
	else if (l == 1)
		return (g_exit_status = 258, print_err(QUOTES_ERROR, '\''), 1);
	if (err)
		return (g_exit_status = 1, ft_putstr_fd(AMBIGUOUS_ERROR, 2), 1);
	return (0);
}
