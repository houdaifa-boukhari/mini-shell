/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise_blt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:46:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/26 17:19:05 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    ft_exit(char **cmd)
{
	int flag;
	int status;

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

void    echo_handling(char **cmd, char **envp)
{
    if (count_arrays(cmd) == 2 && !ft_strcmp(cmd[1], "-n"))
        printf("\n");
    else
        execution(cmd, envp);
}

void    get_current_path(void)
{
    char    path[PATH_MAX];

    if (getcwd(path, sizeof(path)))
        printf("%s\n", path);
    else
        perror("getcwd");
}

void	change_directory(char **cmd)
{
	int		status;
	char	*path;

	status = 0;
	path = getenv("HOME");
	if (count_arrays(cmd) > 1)
		status = chdir(cmd[1]);
	else
		status = chdir(path);
	if (!path)
		ft_putendl_fd("mini-shell: cd: HOME not set", 2);
	if (status == -1 && count_arrays(cmd) > 1)
	{
		ft_putstr_fd("mini-shell: cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

void	export_handling(char **cmd, t_envp *env)
{
	int		size_envp;
	char	*new_env;

	if (count_arrays(cmd) == 1)
	{
		print_export(env);
		return ;
	}
}