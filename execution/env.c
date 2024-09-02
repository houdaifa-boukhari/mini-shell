/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:47:23 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/02 11:38:55 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

bool	error_path(char *msg, char *cmd, bool check)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	return (check);
}

bool	check_is_dir(char *cmd, char *path)
{
	DIR		*dir;

	dir = opendir(cmd);
	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		return (closedir(dir), exit(2), true);
	}
	else if (dir && (ft_strchr(cmd, '/') || !path))
		return (closedir(dir), error_path(": is a directory\n", cmd, true));
	else if (dir)
		closedir(dir);
	else if ((ft_strchr(cmd, '/') || !path )  && access(cmd, F_OK) == -1)
	{
		error_path(": No such file or directory\n", cmd, true);
		return (exit(127), true);
	}
	else if ((ft_strchr(cmd, '/') || !path ) && access(cmd, X_OK) == -1)
		return (error_path(": Permission denied\n", cmd, true));
	return (false);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**full_path;

	i = 0;
	if (!cmd)
		return (NULL);
	if (check_is_dir(cmd, search_in_env(env, "PATH")))
		exit(126);
	full_path = ft_split(search_in_env(env, "PATH"), ':');
	if (access(cmd, X_OK) == 0 && ((!full_path) || (ft_strchr(cmd, '/'))))
		return (free_arrays(full_path), cmd);
	path = ft_strjoin("/", cmd);
	if (!full_path || ft_strcmp(path, "/") == 0 || ft_strchr(path, '.'))
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
	return (free(path), free_arrays(full_path), tmp);
}

bool	controle_fd_blt(t_args_n *cmds, t_fd *fd)
{
	int		count;
	bool	flag;
	bool	check;

	flag = true;
	count = count_cmds(cmds);
	check = managing_input(cmds->inp, fd, count, &flag);
	if (flag == false)
		return (false);
	check = managing_output(cmds->out, fd, count, &flag);
	if (check && flag)
		dup2(fd->fd_out, STDOUT_FILENO);
	if (!flag)
		return (false);
	return (true);
}

bool	is_builtin(t_args_n **args, char **cmd, t_env *env, t_fd fd)
{
	int	count;

	count = count_cmds((*args));
	if (!cmd || !*cmd)
		return (false);
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "echo")
		|| !ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "env")
		|| !ft_strcmp(cmd[0], "exit"))
	{
		if (count == 1)
		{
			if (controle_fd_blt(*args, &fd))
			{
				handle_blt(args, cmd, env);
				dup2(fd.save_out, STDOUT_FILENO);
			}
		}
		else
			handle_blt(args, cmd, env);
		return (true);
	}
	return (false);
}

void	handle_blt(t_args_n **args, char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		g_exit_status = change_directory(cmd, env->envp);
	else if (!ft_strcmp(cmd[0], "echo"))
		g_exit_status = echo_handling(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		g_exit_status = get_current_path();
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
		g_exit_status = print_env(env->env);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(args, cmd);
}
