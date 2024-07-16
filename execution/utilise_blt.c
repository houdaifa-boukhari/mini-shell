/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise_blt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:46:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/16 13:02:15 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_exit(char **cmd)
{
	int	flag;
	int	status;

	flag = 0;
	status = 0;
	ft_putstr_fd("exit\n", 2);
	if (count_arrays(cmd) >= 2)
	{
		status = atoi_(cmd[1], &flag);
		if (flag == 1)
		{
			printf("mini-shell: exit: %s: numeric argument required\n", cmd[1]);
			exit(255);
		}
		else if (count_arrays(cmd) > 2)
		{
			ft_putstr_fd("mini-shell: exit: too many arguments\n", 2);
			return ;
		}
		exit(status);
	}
	else
		exit(status);
}

void	print_env(t_envp *envp)
{
	while (envp)
	{
		printf("%s\n", envp->env);
		envp = envp->next;
	}
}

void	print_export(t_envp *envp)
{
	int		j;
	bool	check;

	sorte_env(envp);
	while (envp)
	{
		j = 0;
		check = true;
		ft_putstr_fd("declare -x ", 1);
		while (envp->env[j])
		{
			if (envp->env[j] == '=' && check == true)
			{
				write(1, "=\"", 2);
				check = false;
			}
			else
				write(1, &envp->env[j], 1);
			j++;
		}
		printf("\"\n");
		envp = envp->next;
	}
}

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

void	echo_handling(char **cmd, char **envp)
{
	int		i;
	bool	flag;

	i = 1;
	if (count_arrays(cmd) == 1)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	flag = skip_flag_echo(cmd, &i);
	while (cmd[i + 1])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd(cmd[i], STDOUT_FILENO);
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	get_current_path(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
		printf("%s\n", path);
	else
		perror("getcwd");
}

void	change_directory(char **cmd)
{
	int		status;
	int		n_args;
	char	*path;

	status = 0;
	n_args = count_arrays(cmd);
	path = getenv("HOME");
	if (n_args == 1 || (n_args == 2 && !ft_strcmp("~", cmd[1])))
	{
		status = chdir(path);
		if (!path)
			ft_putendl_fd("mini-shell: cd: HOME not set", 2);
	}
	else if (n_args == 2)
		status = chdir(cmd[1]);
	else
		ft_putendl_fd("mini-shell: cd: too many arguments", 2);
	if (status == -1)
	{
		ft_putstr_fd("mini-shell: cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

void	export_handling(char **cmd, t_envp **env)
{
	int		i;
	char	*new_env;

	i = 1;
	if (count_arrays(cmd) == 1)
	{
		print_export(*env);
		return ;
	}
	while (cmd[i])
	{
		adding_env(env, cmd[i]);
		i++;
	}
}
