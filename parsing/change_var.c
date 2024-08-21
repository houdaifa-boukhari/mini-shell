/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:45:21 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/21 17:22:34 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"
int is_her(char *str,int x)
{
	if((x - 1 >= 0) && str[x]=='<'&& str[x+1]=='<')
		return 1;
	if((x - 1 >= 0) && str[x]=='<'&& str[x-1]=='<')
		return 1;
	
	return 0;
}

int check_speace_in_var(char *var)
{
	int ll =0;
	int s =0;
	while (var && is_sp(var[ll]))
		ll++;
	while (var && var[ll])
	{

		if(var[ll] && s)
			return (1);
		
		ll++;
		while (var[ll] && is_sp(var[ll]))
		{
			ll++;
			s=1;
		}
	}
	return 0;
}

//$hhbhb@fh$USER
int check_ambiguous(char *str,  char **envp, int err)
{
	if(!str )
		return (0);
	if(err )
		return (free(str),1);
	int x =0;
	int l;
	char *re =NULL;
	char add[2];
	char *var;
	char *ss;
	
	while (str[x])
	{	
		if(str[x]=='$')
		{
			ss = get_name_var(str + x, &x);
			var = search_in_env(envp, ss);

				if(check_speace_in_var(var))
					return(free(ss),free(str),free(re),1);
			
			// printf("var=%s|\n",var);
			if(var)
				re = strjoin_parsing(re,var);
			free(ss);
		}
		else
		{
			add[0]=str[x];
			// printf("%c|\n",str[x]);
			add[1]='\0';
			re = strjoin_parsing(re,add);
		}
		x++;
	}
	
	// printf("last=%s|\n",re);
	if(!re)
		return (free(str),free(re),1);
	return (free(str),free(re),0);
}

static char *check_erroe_var(char *str, int x )
{
	
	// while (var && var[++ll] && !k)
	// 	if (is_sp(var[ll]))
	// 		k = 1;
	int i =0; 
	char *re =NULL;
	char add[2];
	int l;
	t_quote		q;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	
	// printf("d=%d|\n",x);
	x++;
	while (is_sp(str[x]))
		x++;
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if(!l&&(is_sp(str[x]) || str[x]=='<'||str[x]=='>'))
			break ;
		add[0]=str[x];
		add[1]='\0';
		re =strjoin_parsing(re,add);
		x++;
	}
	return (re);
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

static void change_var_tow(t_args_var *args,char *str,int *err,char **envp)
{
	int		j;
	char	*ss;
	char	*var;

	j = args->x;
	ss = get_name_var(str + args->x, &(*args).x);
	// printf("j=%d,x=%d,j+len=%d\n",j,(*args).x,j+ (ft_strlen(ss)));
	var = search_in_env(envp, ss);
	// if (!(*err))
	

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
}

// cat << $USER stoop in $USER not value of $USER
static int	  check_and_her_var(char *str, int x, t_args_var args)
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
	t_quote		q;

	q.inDoubleQuote = 0;
	q.inSingleQuote = 0;
	args.re = malloc (change_var_count(str, envp) + 1);
	args.x = -1;
	args.i = 0;
	args.c_var = 0;
	while (str[++args.x])
	{
		args.l = chacke_q(str[args.x], &q);
		
		// printf("err=%d\n",*err);
		if (!is_her(str,args.x)&&!args.l && (str[args.x] == '<'  || str[args.x]== '>'))
			*err = check_ambiguous(check_erroe_var(str, args.x ),envp, *err);
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
	args.re[args.i] = '\0';
	return (args.re);
}
