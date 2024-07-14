/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:33:20 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/13 12:46:08 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    sorte_env(t_envp *head)
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

	len_str = ft_strlen(str);
	while (env)
	{
		if (!ft_strncmp(env->env, str, len_str) && *(env->env + len_str) == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	unset_hadnling(t_envp *env, char *str)
{
	t_envp	*pos;
	t_envp	*prev;
	t_envp	*next;

	pos = search_env(env, str);
	if (!pos)
		return ;
	prev = pos->prev;
	next = pos->next;
	free(pos->env);
	free(pos);
	prev->next = next;
	next->prev = prev;
	return ;
}

void	adding_env(t_envp **env, char *str)
{
	t_envp	*pos;

	pos = search_env(*env, str);
	if (!pos)
	{
		creat_list(env, str);
		return ;
	}
	free(pos->env);
	pos->env = ft_strdup(str);
	return ;
}