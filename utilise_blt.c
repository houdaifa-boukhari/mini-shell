/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise_blt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:46:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/24 16:20:30 by hel-bouk         ###   ########.fr       */
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

void	print_env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
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