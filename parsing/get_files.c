/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:49:05 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/04 14:44:59 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	get_files_count(char **str)
{
	int	x;
	int	c;

	x = 0;
	c = 0;
	while (str[x])
	{
		if (!ft_strncmp(str[x], "<", 2) || !ft_strncmp(str[x], "<<", 3) || !ft_strncmp(str[x], ">", 2)|| !ft_strncmp(str[x], ">>", 3))
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

static void	get_files_v(t_files	*file, int *c, int typ, char *str,char **envp)
{
	// printf("in=%s\n",str);
	if (typ == 4 && is_quote(str))
		file[*c].is_q = true;
	else
		file[*c].is_q = false;
	if (str && (!ft_strncmp(str, "<", 2) || !ft_strncmp(str, "<<", 3)||!ft_strncmp(str, ">", 2) || !ft_strncmp(str, ">>", 3)))
	{
		free(str);
		str = NULL;
	}
	if(typ != 4 && check_ambiguous(str,envp))
		file[*c].is_am = true;
	else
		file[*c].is_am = false;
	if(typ!=4 && !check_ambiguous(str,envp))
		file[*c].file = whithout_q(change_var(str,envp),1);
	else
		file[*c].file = whithout_q(str,0);

	file[*c].typ = typ;
	file[*c].last = ft_strdup("1");
	(*c)++;
}
//> 1
//>> 2
//< 3
//<< 4

t_files	*get_files(char **str,char **envp)
{
	t_files	*inp;
	int		x;
	int		c;

	inp = malloc((get_files_count(str) + 1) * sizeof(t_files));
	c = 0;
	x = 0;
	while (str[x])
	{
		if (!ft_strncmp(str[x], "<", 2) || !ft_strncmp(str[x], "<<", 3) || !ft_strncmp(str[x], ">", 2)|| !ft_strncmp(str[x], ">>", 3))
		{
			// printf("str+x=%s\n",str[x+1]);
			if (!ft_strncmp(str[x], ">", 2))
				get_files_v(inp, &c, 1, str[x + 1],envp);
			else if (!ft_strncmp(str[x], ">>", 3))
				get_files_v(inp, &c, 2, str[x + 1],envp);
			else if (!ft_strncmp(str[x], "<", 2))
				get_files_v(inp, &c, 3, str[x + 1],envp);
			else if (!ft_strncmp(str[x], "<<", 3))
				get_files_v(inp, &c, 4, str[x + 1],envp);
		}
		x++;
	}
	inp[c].last = NULL;
	inp[c].is_am = false;
	inp[c].file = NULL;
	inp[c].typ = 0;
	return (inp);
}
