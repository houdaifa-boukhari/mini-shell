/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:49:05 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/23 17:57:44 by hel-bouk         ###   ########.fr       */
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
		if ((!ft_strncmp(str[x], "<", 2)
				|| !ft_strncmp(str[x], "<<", 3)) && str[x + 1])
			c++;
		x++;
	}
	return (c);
}

static void	get_inp_v(t_inp	*inp, int *c, bool bol, char *str)
{
	inp[*c].inp = str;
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
		if ((!ft_strncmp(str[x], "<", 2)
				|| !ft_strncmp(str[x], "<<", 3)) && str[x + 1])
		{
			if (!ft_strncmp(str[x], "<", 2))
				get_inp_v(inp, &c, false, whithout_q(str[x + 1], 0));
			else
				get_inp_v(inp, &c, true, whithout_q(str[x + 1], 0));
		}
		x++;
	}
	inp[c].inp = NULL;
	inp[c].is_h = false;
	return (inp);
}
