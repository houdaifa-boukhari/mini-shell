/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:42:44 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/10 11:33:11 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    execution(t_args_n *cmd, char **envp, t_fd fd)
{
    int     pid;
    char    *path;

    pid = fork();
    if (pid == 0)
    {
		if (managing_input(cmd->inp, &fd))
			dup2(fd.fd_in, STDIN_FILENO);
		if (managing_output(cmd->out, &fd))
			dup2(fd.fd_out, STDOUT_FILENO);
        path = get_path(cmd->arguments[0]);
        if (!path)
        {
            perror(cmd->arguments[0]);
            exit(EXIT_FAILURE);
        }
        if (execve(path, cmd->arguments, envp) == -1)
        {
            perror("failed execution");
            exit(EXIT_FAILURE);
        }
    }
    else
        wait(NULL);
}

void	change_fd_ouput(int fd, int cfd)
{
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("dup2 failed");
	close(cfd);
}

void	wait_children(int *pids, int size)
{
	int	status;
	int	i;

	i = 0;
	while (i < size)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		status = WEXITSTATUS(status);
		if (status == 127 && i == size - 1)
			exit(status);
		i++;
	}
	free(pids);
	unlink("/tmp/herdoc");
}

void	execute_child(t_args_n *cmd, char **envp, t_fd fd)
{
	char	*path;

	path = NULL;
    if (fd.fd_in != 0)
	{
		if (dup2(fd.fd_in, 0) == -1)
			perror("dup2 failed");
	}
	if (cmd->next)
		change_fd_ouput(fd.fd_p[1], fd.fd_p[0]);
	else
		change_fd_ouput(fd.save_out, fd.fd_p[1]);
	path = get_path(cmd->arguments[0]);
	if (!path)
	{
		write(2, cmd->arguments[0], ft_strlen(cmd->arguments[0]));
		write(2, " :command not found\n", 21);
		exit(127);
	}
	if (execve(path, cmd->arguments, envp) == -1)
	{
		perror("failed execution");
		exit(EXIT_FAILURE);
	}
}

void	execut_(t_args_n *cmds, char **envp, t_fd fd)
{
	int		*pids;
	int		i;

	i = 0;
	pids = (int *)malloc(sizeof(int) * count_cmds(cmds));
	if (!pids)
		return ;
	while (cmds)
	{
		managing_input(cmds->inp, &fd);
		managing_output(cmds->out, &fd);
		pipe(fd.fd_p);
		fd.pid = fork();
		if (fd.pid == 0)
			execute_child(cmds, envp, fd);
		else 
		{
			pids[i++] = fd.pid; 
			close(fd.fd_p[1]);
			if (!cmds->next)
				break ;
			fd.fd_in = fd.fd_p[0];
			cmds = cmds->next;
		}
	}
	close(fd.fd_in);
	wait_children(pids, i);
}
