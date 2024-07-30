/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-29 20:27:17 by zbakkas           #+#    #+#             */
/*   Updated: 2024-07-29 20:27:17 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"

// $? exit_status
static int	change_var_count_one(int *x)
{
	char	*str;
	int		i;

	str = ft_itoa(exit_status);
	i = ft_strlen(str);
	(*x)++;
	free(str);
	return (i);
}

static int	change_var_count_tow(char **envp, int l, int *x, char *str)
{
	int		j;
	char	*var;
	int		i;
	char	*ss;

	ss = get_name_var(str + *x, x);
	var = search_in_env(envp, ss);
	i = 0;
	free(ss);
	i += ft_strlen(var);
	j = 0;
	if (l != 2)
		i++;
	while (l != 2 && var && var[j])
	{
		if (j - 1 >= 0 && l != 2 && var[j - 1] == ' ' && var[j] != ' ')
			i++;
		if (l != 2 && var[j] != ' ' && (var[j + 1] == ' '
				|| var[j + 1] == '\0'))
			i++;
		j++;
	}
	return (i);
}

int	change_var_count(char *str, char **envp, int *err)
{
	int		x;
	int		i;
	int		l;
	t_quote	q;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	x = -1;
	i = 0;
	while (str[++x])
	{
		l = chacke_q(str[x], &q);
		if (str[x] == '$' && l != 1 && str[x + 1]
			&& str[x + 1] != ' ' && str[x + 1] != '$')
		{
			if (str[x + 1] == '?')
				i = i + change_var_count_one(&x);
			else if (!(str[x + 1] == ' ' || str[x + 1] == '\''
					|| str[x + 1] == '"'))
				i = i + change_var_count_tow(envp, l, &x, str);
		}
		else
			i++;
	}
	return (i);
}
