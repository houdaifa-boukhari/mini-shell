/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:33:20 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/16 12:55:51 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	sorte_env(t_envp *head)
{
	t_envp	*next;
	char	*tmp;

	while (head)
	{
		next = head->next;
		while (next)
		{
			if (ft_strcmp(head->env, next->env) > 0)
			{
				tmp = head->env;
				head->env = next->env;
				next->env = tmp;
			}
			next = next->next;
		}
		head = head->next;
	}
}

t_envp	*search_env(t_envp *env, char *str)
{
	char	*s1;
	int		len_str;

	s1 = ft_strdup(str);
	s1[find_char(str, '=')] = '\0';
	len_str = ft_strlen(s1);
	while (env)
	{
		if (!ft_strncmp(env->env, s1, len_str))
		{
			free(s1);
			return (env);
		}
		env = env->next;
	}
	free(s1);
	return (NULL);
}

void	unset_hadnling(t_envp **env, char **cmd)
{
	int		i;
	t_envp	*pos;
	t_envp	*prev;
	t_envp	*next;

	i = 1;
	while (cmd[i])
	{
		pos = search_env(*env, cmd[i]);
		if (pos)
		{
			prev = pos->prev;
			next = pos->next;
			free(pos->env);
			free(pos);
			if (prev)
				prev->next = next;
			if (next)
				next->prev = prev;
		}
		i++;
	}
	return ;
}

void	adding_env(t_envp **env, char *str)
{
	t_envp	*pos;

	pos = search_env(*env, str);
	if (pos)
	{
		free(pos->env);
		pos->env = ft_strdup(str);
		return ;
	}
	creat_list(env, str);
	return ;
}
