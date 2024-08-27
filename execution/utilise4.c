/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:29:46 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/24 18:02:14 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	**assign_envp(t_envp *envp)
{
	int		i;
	int		size;
	char	**env;

	i = 0;
	size = size_env(envp);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env || size == 0)
		return (free(env), NULL);
	while (i < size)
	{
		env[i] = ft_strdup(envp->env);
		envp = envp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
