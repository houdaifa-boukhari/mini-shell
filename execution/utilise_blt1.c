/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise_blt1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:38:35 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/22 09:55:22 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

bool	skip_flag_echo(char **cmd, int *idx)
{
	int		i;
	int		j;
	bool	check;

	i = 1;
	check = false;
	while (cmd[i])
	{
		j = 1;
		if (cmd[i][0] == '-')
		{
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] == '\0')
				check = true;
			else
				break ;
		}
		else
			break ;
		i++;
	}
	*idx = i;
	return (check);
}

int	echo_handling(char **cmd)
{
	int		i;
	int		count;
	bool	flag;

	i = 1;
	count = count_arrays(cmd);
	if (count == 1)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	flag = skip_flag_echo(cmd, &i);
	while (i < count - 1)
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd(cmd[i], STDOUT_FILENO);
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	get_current_path(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		return (0);
	}
	else
		perror("getcwd");
	return (1);
}

int	change_directory(char **cmd, char **env)
{
	int		status;
	int		n_args;
	char	*path;

	status = 0;
	n_args = count_arrays(cmd);
	path = search_in_env(env, "HOME");
	if (n_args == 1 || (n_args == 2 && !ft_strcmp("~", cmd[1])))
	{
		status = chdir(path);
		if (!path)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
	}
	else if (n_args == 2)
		status = chdir(cmd[1]);
	else
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	if (status == -1 && n_args != 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	return (status == -1);
}

bool	export_handling(char **cmd, t_envp **env)
{
	int		i;
	bool	status;

	i = 1;
	status = true;
	if (count_arrays(cmd) == 1)
	{
		print_export(*env);
		return (0);
	}
	while (cmd[i])
	{
		if (status)
			status = adding_env(env, cmd[i]);
		else
			adding_env(env, cmd[i]);
		i++;
	}
	return (status);
}
