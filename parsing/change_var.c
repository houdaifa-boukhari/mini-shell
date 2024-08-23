/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:45:21 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/23 18:07:10 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	is_her(char *str, int x)
{
	if (str[x] == '<' && str[x + 1] == '<')
		return (1);
	if (x - 1 >= 0 && str[x] == '<' && str[x - 1] == '<')
		return (1);
	return (0);
}

//$? g_exit_status
static void	change_var_one(int *x, char *re, int *i)
{
	char	*str;
	int		a;

	str = ft_itoa(g_exit_status);
	a = 0;
	while (str[a])
	{
		re[(*i)++] = str[a++];
	}
	free(str);
	(*x)++;
}

static void	change_var_tow(t_args_var *args, char *str, int *err, char **envp)
{
	int		j;
	char	*ss;
	char	*var;
	char	*tmp;

	(void)err;
	j = args->x;
	ss = get_name_var(str + args->x, &(*args).x);
	tmp = ft_strdup(search_in_env(envp, ss));
	var = ft_strtrim(tmp, "\t ", args->l);
	free(ss);
	j = 0;
	if (var && var[j] && args->l != 2)
		args->re[args->i++] = '"';
	while (var && var[j])
	{
		if (j - 1 >= 0 && args->l != 2 && is_sp(var[j - 1]) && !is_sp(var[j]))
			args->re[args->i++] = '"';
		args->re[args->i++] = var[j];
		if (args->l != 2 && !is_sp(var[j]) && (is_sp(var[j + 1])
				|| var[j + 1] == '\0'))
			args->re[args->i++] = '"';
		j++;
	}
	return (free(tmp), free(var));
}

// cat << $USER stoop in $USER not value of $USER
static int	check_and_her_var(char *str, int x, t_args_var args)
{
	int	l;

	l = 0;
	while (x >= 0)
	{
		while (x >= 0 && (is_sp(str[x])))
		{
			x--;
		}
		if (x >= 0 && str[x] == '<' && x - 1 >= 0 && str[x - 1] == '<')
			l = 1;
		x--;
	}
	if (!l && str[args.x] == '$' && args.l != 1 && str[args.x + 1]
		&& !is_sp(str[args.x + 1]) && str[args.x + 1] != '$')
		return (1);
	return (0);
}

char	*change_var(char *str, char **envp, int *err)
{
	t_args_var	args;

	args.q.in_double_quote = 0;
	args.q.in_single_quote = 0;
	args.re = malloc (change_var_count(str, envp) + 1);
	args.x = -1;
	args.i = 0;
	while (str[++args.x])
	{
		args.l = chacke_q(str[args.x], &args.q);
		if (!is_her(str, args.x) && !args.l 
			&& (str[args.x] == '<' || str[args.x] == '>'))
			*err = check_ambiguous(check_erroe_var(str, args.x), envp, *err);
		if (check_and_her_var(str, args.x, args))
		{
			if (str[args.x + 1] == '?')
				change_var_one(&args.x, args.re, &args.i);
			else if (!(is_sp(str[args.x + 1]) || str[args.x + 1] == '\''
					|| str[args.x + 1] == '"'))
				change_var_tow(&args, str, err, envp);
		}
		else
			args.re[args.i++] = str[args.x];
	}
	return (args.re[args.i] = '\0', args.re);
}
