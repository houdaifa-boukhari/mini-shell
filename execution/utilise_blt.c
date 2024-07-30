/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise_blt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:46:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/30 16:41:25 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_exit(t_args_n **args, char **cmd)
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
			exit(2);
		}
		else if (count_arrays(cmd) > 2)
		{
			ft_putstr_fd("mini-shell: exit: too many arguments\n", 2);
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
		printf("%s\n", envp->env);
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
		if (ft_strchr(envp->env, '='))
			printf("\"");
		printf("\n");
		envp = envp->next;
	}
}
