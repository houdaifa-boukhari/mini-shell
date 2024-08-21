/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:27:17 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/21 16:20:00 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"

// $? g_exit_status
static int	change_var_count_one(int *x)
{
	char	*str;
	int		i;

	str = ft_itoa(g_exit_status);
	i = ft_strlen(str);
	(*x)++;
	free(str);
	return (i);
}

static int	change_var_count_tow(char **envp,int l, int *x, char *str)
{
	int		j;
	char	*var;
	int		i;
	char	*ss;

	ss = get_name_var(str + *x, x);
	var = search_in_env(envp, ss);
	i = 0;
	
	// i += ft_strlen(var);
	free(ss);
	j = 0;
	if (var && var[j] && l != 2)
		i++;
	while (var && var[j])
	{
		if (j - 1 >= 0 && l != 2 && is_sp(var[j - 1]) && !is_sp(var[j]))
			i++;
		i++;
		if (l != 2 && !is_sp(var[j]) && (is_sp(var[j + 1])
				|| var[j + 1] == '\0'))
			i++;
		j++;
	}
	return (i);
}

// cat << $USER stoop in $USER not value of $USER
static int	  count_check_and_her_var(char *str, int x, int j,int l )
{
	int	ll;

	ll = 0;
	while (x >= 0)
	{
		while (x >= 0 && (is_sp(str[x])))
		{
			x--;
		}
		if (x >= 0 && str[x] == '<' && x - 1 >= 0 && str[x - 1] == '<')
			ll = 1;
		x--;
	}
	if (!ll && str[j] == '$' && l != 1 && str[j + 1]
		&& !is_sp(str[j + 1]) && str[j + 1] != '$')
		return (1);
	return (0);
}
int	change_var_count(char *str, char **envp)
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
		if (count_check_and_her_var(str,x,x,l))
		{
			if (str[x + 1] == '?')
				i = i + change_var_count_one(&x);
			else if (!(is_sp(str[x + 1]) || str[x + 1] == '\''
					|| str[x + 1] == '"'))
				i = i + (change_var_count_tow(envp, l, &x, str) );
		}
		else
			i++;
	}
	return (i);
}
