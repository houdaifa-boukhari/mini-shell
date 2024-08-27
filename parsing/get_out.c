/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:50:44 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/27 09:12:13 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	get_out_count(char **str)
{
	int		x;
	int		c;

	x = 0;
	c = 0;
	while (str[x])
	{
		if ((!ft_strncmp(str[x], ">", 2)
				|| !ft_strncmp(str[x], ">>", 3)) && str[x + 1])
			c++;
		x++;
	}
	return (c);
}

static void	get_out_v(t_out	*out, int *c, bool bol, char *str)
{
	out[*c].out = str;
	out[*c].is_a = bol;
	(*c)++;
}

t_out	*get_out(char **str)
{
	t_out	*out;
	int		x;
	int		c;

	x = 0;
	c = 0;
	out = malloc((get_out_count(str) + 1) * sizeof(t_out));
	while (str[x])
	{
		if ((!ft_strncmp(str[x], ">", 2)
				|| !ft_strncmp(str[x], ">>", 3)) && str[x + 1])
		{
			if (!ft_strncmp(str[x], ">", 2))
				get_out_v(out, &c, false, whithout_q(str[x + 1], 0));
			else
				get_out_v(out, &c, true, whithout_q(str[x + 1], 0));
		}
		x++;
	}
	out[c].out = NULL;
	out[c].is_a = false;
	return (out);
}
