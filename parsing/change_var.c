
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-28 15:45:21 by zbakkas           #+#    #+#             */
/*   Updated: 2024-07-28 15:45:21 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"


static int	check_erroe_var(char *var, int j, int l, char *str)
{
	int	ll;
	int	k;

	ll = -1;
	k = 0;
	while (var && var[++ll] && !k)
		if (var[ll] == ' ')
			k = 1;
	ll = j;
	if (l != 2 && str[j])
	{
		while (ll >= 0)
		{
			ll--;
			if ((str[ll] == '>' || str[ll] == '<' ))
			{
				if ((!var || k))
					return (1);
			}
			if (str[ll] != ' ')
				break ;
		}
	}
	return (0);
}

//$? exit_status
static void	change_var_one(int *x, char *re, int *i)
{
	char	*str;
	int		a;

	str = ft_itoa(exit_status);
	a = 0;
	while (str[a])
	{
		re[(*i)++] = str[a++];
	}
	free(str);
	(*x)++;
}

static void change_var_tow(t_args_var *args,char *str,int *err,char **envp)
{
	int		j;
	char	*ss;
	char	*var;

	j = args->x;
	ss = get_name_var(str + args->x, &(*args).x);
	var = search_in_env(envp, ss);
	free(ss);
	*err = check_erroe_var(var, j, args->l, str);
	j = 0;
	if (var && var[j] && args->l != 2)
		args->re[args->i++] = '"';
	while (var && var[j])
	{
		if (j - 1 >= 0 && args->l != 2 && var[j - 1] == ' ' && var[j] != ' ')
			args->re[args->i++] = '"';
		args->re[args->i++] = var[j];
		if (args->l != 2 && var[j] != ' ' && (var[j + 1] == ' '
				|| var[j + 1] == '\0'))
			args->re[args->i++] = '"';
		j++;
	}
}

char *change_var(char *str, char **envp, int *err)
{
	t_args_var	args;
	t_quote		q;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	args.re = malloc (change_var_count(str, envp, err) + 1);
	args.x = -1;
	args.i = 0;
	while (str[++args.x])
	{
		args.l = chacke_q(str[args.x], &q);
		if (str[args.x] == '$' && args.l != 1 && str[args.x + 1]
			&& str[args.x + 1] != ' ' && str[args.x + 1] != '$')
		{
			if (str[args.x + 1] == '?')
				change_var_one(&args.x, args.re, &args.i);
			else if (!(str[args.x + 1] == ' ' || str[args.x + 1] == '\''
					|| str[args.x + 1] == '"'))
				change_var_tow(&args, str, err, envp);
		}
		else
			args.re[args.i++] = str[args.x];
	}
	args.re[args.i] = '\0';
	return (args.re);
}


