/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:06:15 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/24 11:14:29 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    creat_list(t_cmd **cmds, char *line)
{
	t_cmd   *ptr;
	t_cmd   *new_cmd;

	if (!cmds)
		return ;
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return ;
	new_cmd->cmd = ft_split(line, ' ');
	new_cmd->next = NULL;
	if (!*cmds)
	{
		*cmds = new_cmd;
		return ;
	}
	ptr = *cmds;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_cmd;
}

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
