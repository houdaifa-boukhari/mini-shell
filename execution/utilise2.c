/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:11:28 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/18 16:14:44 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	wait_child(t_fd fd)
{
	int	status;

	waitpid(fd.pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status) + 128;
}

void	change_fd_ouput(int fd, int cfd)
{
	dup2(fd, STDOUT_FILENO);
	close(cfd);
	close(fd);
}

void	change_fd_in(int fd, t_args_n **cmd)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		ft_error(cmd, "", EXIT_FAILURE);
	}
	close(fd);
}

int	count_cmds(t_args_n *lst)
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

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = EXIT_FAILURE;
	}
}
