/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:29:46 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/05 13:51:33 by hel-bouk         ###   ########.fr       */
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

bool	valid_add(char	*str)
{
	char	*tmp;

	if (!str || !*str)
		return (false);
	tmp = ft_strchr(str, '=');
	if (!tmp)
		return (false);
	return (true);
}

bool	error_path(char *msg, char *cmd, bool check)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	return (check);
}

bool	check_is_dir(char *cmd, char *path)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n",
			STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		return (closedir(dir), exit(2), true);
	}
	else if (dir && (ft_strchr(cmd, '/') || !path))
		return (closedir(dir), error_path(": is a directory\n", cmd, true));
	else if (dir)
		closedir(dir);
	else if ((ft_strchr(cmd, '/') || !path) && access(cmd, F_OK) == -1)
	{
		error_path(": No such file or directory\n", cmd, true);
		return (exit(127), true);
	}
	else if ((ft_strchr(cmd, '/') || !path) && access(cmd, X_OK) == -1)
		return (error_path(": Permission denied\n", cmd, true));
	return (false);
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

//> 1
//>> 2
//< 3
//<< 4
 
bool	opens_files(t_files *file)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (file[i].last)
	{
		if (file[i].is_am)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(file[i].file, STDERR_FILENO);
			ft_putendl_fd(ERR_AMBG, STDERR_FILENO);
			return (false);
		}
		if (file[i].typ == 1 && !file[i].is_am)
			fd = open(file[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (file[i].typ == 2)
			fd = open(file[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file[i].typ == 3)
			fd = open(file[i].file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			if (!ft_strcmp(file[i].file, ""))
				ft_putstr_fd(": ", STDERR_FILENO);
			perror(file[i].file);
			return (false);
		}
		close(fd);
		i++;
	}
	return (true);
}
