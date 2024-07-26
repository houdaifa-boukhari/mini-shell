/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:09:41 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/24 15:54:15 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_error(t_args_n **cmd, char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	clear_list(cmd);
	exit(status);
}

int	*allocation_array(int size)
{
	int	*tab;

	tab = ft_calloc(sizeof(int), size);
	if (!tab)
		return (NULL);
	return (tab);
}

void	built_array(t_env *envirement)
{
	int	i;
	int	size;
	t_env	*env;
	t_envp	*envp;

	i = 0;
	if (!envirement->check)
		return ;
	envirement->check = false;
	env = envirement;
	envp = env->env;
	free_arrays(env->envp);
	size = size_env(envp);
	env->envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env->envp)
		return ;
	while (i < size)
	{
		env->envp[i] = ft_strdup(envp->env);
		envp= envp->next; 
		i++;
	}
	env->envp[i] = NULL;
}
