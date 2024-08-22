/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:09:41 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/22 09:55:22 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_error(t_args_n **cmd, char *msg, int status)
{
	if ((*cmd)->arguments && (*cmd)->arguments && *((*cmd)->arguments))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((*cmd)->arguments[0], STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	else
		status = g_exit_status;
	clear_list(cmd);
	clear_history();
	exit(status);
}

void	remove_file(t_inp *inp)
{
	int	i;

	i = 0;
	while (inp[i].inp)
	{
		if (inp[i].is_h)
			unlink(inp[i].inp);
		i++;
	}
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
	int		i;
	int		size;
	t_env	*env;
	t_envp	*envp;

	i = 0;
	if (!envirement && !envirement->check)
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
		envp = envp->next;
		i++;
	}
	env->envp[i] = NULL;
}

bool	valid_export(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if ((!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'))
			return (false);
		i++;
	}
	return (true);
}
