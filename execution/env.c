/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:47:23 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/27 16:27:46 by hel-bouk         ###   ########.fr       */
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
		tmp = NULL;
		i++;
	}
	free(path);
	free_arrays(full_path);
	return (tmp);
}

bool	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (false);
	while (i < 7)
	{
		if (!ft_strncmp(cmd, BLT_CMDS[i], ft_strlen(cmd)))
			return (true);
		i++;
	}
	return (false);
}

void	handle_blt(char **cmd, t_envp **env, char **envp)
{
	if (!ft_strcmp(cmd[0], BLT_CMDS[0]))
		change_directory(cmd);
	else if (!ft_strcmp(cmd[0], BLT_CMDS[1]))
		echo_handling(cmd, envp);
	else if (!ft_strcmp(cmd[0], BLT_CMDS[2]))
		get_current_path();
	else if (!ft_strcmp(cmd[0], BLT_CMDS[3]))
		export_handling(cmd, *env);
	else if (!ft_strcmp(cmd[0], BLT_CMDS[4]))
		unset_hadnling(env, cmd[1]);
	else if (!ft_strcmp(cmd[0], BLT_CMDS[5]))
		print_env(*env);
	else if (!ft_strcmp(cmd[0], BLT_CMDS[6]))
		ft_exit(cmd);
	
}