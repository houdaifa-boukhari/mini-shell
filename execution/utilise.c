/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:33:20 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/01 21:04:43 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

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
		if (ft_strncmp(env->env, s1, len_str) == 0)
			return (free(s1), env);
		env = env->next;
	}
	free(s1);
	return (NULL);
}

int	unset_hadnling(t_envp **env, char **cmd)
{
	int		i;
	bool	check;
	t_envp	*pos;

	i = 0;
	check = false;
	while (cmd[i])
	{
		if (!valid_export(cmd[i]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			check = true;
		}
		pos = search_env(*env, cmd[i]);
		unset(env, pos);
		i++;
	}
	return (check);
}

bool	adding_env(t_envp **env, char *str)
{
	t_envp	*pos;
	bool	status;

	status = true;
	if (!valid_export(str))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		status = false;
	}
	else
	{
		pos = search_env(*env, str);
		if (pos)
		{
			if (!valid_add(str))
				return (status);
			free(pos->env);
			pos->env = ft_strdup(str);
			return (status);
		}
		creat_list(env, str);
	}
	return (status);
}

void	free_env(t_envp **env)
{
	t_envp	*current;
	t_envp	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free(current->env);
		free(current);
		current = next;
	}
	*env = NULL;
	env = NULL;
}
