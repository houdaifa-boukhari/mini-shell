/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:47:23 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/30 17:53:21 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**full_path;

	i = 0;
	env = NULL;
	if (access(cmd, X_OK) == 0 && (ft_strncmp(cmd, "/", 1) == 0
			|| ft_strncmp(cmd, "./", 2) == 0))
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

bool	is_builtin(t_args_n **args, char **cmd, t_env *env)
{
	if (!cmd || !*cmd)
		return (false);
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "echo")
		|| !ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "env")
		|| !ft_strcmp(cmd[0], "exit"))
	{
		handle_blt(args, cmd, env);
		return (true);
	}
	return (false);
}

void	handle_blt(t_args_n **args, char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		exit_status = change_directory(cmd, env->envp);
	else if (!ft_strcmp(cmd[0], "echo"))
		exit_status = echo_handling(cmd, env->envp);
	else if (!ft_strcmp(cmd[0], "pwd"))
		exit_status = get_current_path();
	else if (!ft_strcmp(cmd[0], "export"))
	{
		env->check = true;
		exit_status = export_handling(cmd, &(env->env));
	}
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		env->check = true;
		exit_status = unset_hadnling(&(env->env), cmd);
	}
	else if (!ft_strcmp(cmd[0], "env"))
		exit_status = print_env(env->env);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(args, cmd);
}
