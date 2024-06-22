/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:47:23 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/22 18:05:15 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char *get_path(char *cmd)
{
	int     i;
	char	*tmp;
	char    *path;
	char    **full_path;

	i = 0;
	if (access(cmd, X_OK) == 0 && (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0))
		return (cmd);
	path = ft_strjoin("/", cmd);
	full_path = ft_split(getenv("PATH"), ':');
	if (!full_path)
		return (NULL);
	while (full_path[i])
	{
		tmp = ft_strjoin(full_path[i], path);
		if (access(tmp, X_OK) == 0)
			break ;
		free(tmp);
		i++;
	}
	free(path);
	free_arrays(full_path);
	return (tmp);
}
