/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:49:05 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/03 11:01:36 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	get_inp_count(char **str)
{
	int	x;
	int	c;

	x = 0;
	c = 0;
	while (str[x])
	{
		if ((!ft_strncmp(str[x], "<", 2) || !ft_strncmp(str[x], "<<", 3))
			&& str[x + 1])
			c++;
		x++;
	}
	return (c);
}

static int	is_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

static void	get_inp_v(t_inp *inp, int *c, bool bol, char *str)
{
	if (is_quote(str))
		inp[*c].is_q = true;
	else
		inp[*c].is_q = false;
	inp[*c].inp = whithout_q(str, 0);
	inp[*c].is_h = bol;
	(*c)++;
}

t_inp	*get_inp(char **str)
{
	t_inp	*inp;
	int		x;
	int		c;

	inp = malloc((get_inp_count(str) + 1) * sizeof(t_inp));
	c = 0;
	x = 0;
	while (str[x])
	{
		if ((!ft_strncmp(str[x], "<", 2) || !ft_strncmp(str[x], "<<", 3))
			&& str[x + 1])
		{
			if (!ft_strncmp(str[x], "<", 2))
				get_inp_v(inp, &c, false, str[x + 1]);
			else
				get_inp_v(inp, &c, true, str[x + 1]);
		}
		x++;
	}
	inp[c].inp = NULL;
	inp[c].is_h = false;
	return (inp);
}
