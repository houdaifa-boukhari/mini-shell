/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise_blt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:46:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/21 15:31:35 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_exit(t_args_n **args, char **cmd)
{
	int	flag;
	int	status;

	flag = 0;
	status = 0;
	// ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (count_arrays(cmd) >= 2)
	{
		status = atoi_(cmd[1], &flag);
		if (flag == 1)
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			exit(255);
		}
		else if (count_arrays(cmd) > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_exit_status = EXIT_FAILURE;
			return ;
		}
	}
	clear_list(args);
	exit(status);
}

int	print_env(t_envp *envp)
{
	while (envp)
	{
		ft_putendl_fd(envp->env, STDOUT_FILENO);
		envp = envp->next;
	}
	return (0);
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
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (envp->env[j])
		{
			if (envp->env[j] == '=' && check == true)
			{
				write(STDOUT_FILENO, "=\"", 2);
				check = false;
			}
			else
				write(1, &envp->env[j], STDOUT_FILENO);
			j++;
		}
		if (ft_strchr(envp->env, '='))
			ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		envp = envp->next;
	}
}

int	size_env(t_envp *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (count);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
