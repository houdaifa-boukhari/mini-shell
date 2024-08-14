/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:47:23 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/14 21:51:56 by hel-bouk         ###   ########.fr       */
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
	if (access(cmd, X_OK) == 0 && (ft_strchr(cmd, '/')))
		return (cmd);
	path = ft_strjoin("/", cmd);
	full_path = ft_split(search_in_env(env, "PATH"), ':');
	if (!full_path || ft_strcmp(path, "/") == 0)
		return (free(path), free_arrays(full_path), NULL);
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

bool	is_builtin(t_args_n **args, char **cmd, t_env *env, t_fd fd)
{
	if (!cmd || !*cmd)
		return (false);
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "echo")
		|| !ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "env")
		|| !ft_strcmp(cmd[0], "exit"))
	{
		managing_output((*args)->out, &fd);
		handle_blt(args, cmd, env, fd);
		return (true);
	}
	return (false);
}

void	update_oldPWD(t_env *env)
{
	char	path[PATH_MAX];
	char	*line;

	if (getcwd(path, PATH_MAX))
	{
		line = ft_strjoin("OLDPWD=", path);
		env->check = true;
		adding_env(&(env->env), line);
		free(line);
	}
}

void	handle_blt(t_args_n **args, char **cmd, t_env *env, t_fd fd)
{
	if (!ft_strcmp(cmd[0], "cd"))
	{
		if (count_arrays(cmd) != 1)
			update_oldPWD(env);
		g_exit_status = change_directory(cmd, env->envp);
	}
	else if (!ft_strcmp(cmd[0], "echo"))
		g_exit_status = echo_handling(cmd, env->envp, fd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		g_exit_status = get_current_path(fd);
	else if (!ft_strcmp(cmd[0], "export"))
	{
		env->check = true;
		g_exit_status = export_handling(cmd, &(env->env));
	}
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		env->check = true;
		g_exit_status = unset_hadnling(&(env->env), cmd);
	}
	else if (!ft_strcmp(cmd[0], "env"))
		g_exit_status = print_env(env->env, fd);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(args, cmd);
}
