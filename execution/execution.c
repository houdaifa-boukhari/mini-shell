/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:42:44 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/13 12:59:24 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    execution(t_args_n *cmd, t_env *env, t_fd fd)
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
		if (is_builtin(cmd->arguments, env))
			return ;
        path = get_path(cmd->arguments[0]);
        if (!path)
        {
            perror(cmd->arguments[0]);
            exit(EXIT_FAILURE);
        }
        if (execve(path, cmd->arguments, env->envp) == -1)
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
}

void	execute_child(t_args_n *cmd, char **envp, t_fd fd)
{
	char	*path;

	path = NULL;
	if (managing_input(cmd->inp, &fd))
		dup2(fd.fd_in, STDIN_FILENO);
    else if (fd.fd_in != 0)
	{
		if (dup2(fd.fd_in, STDIN_FILENO) == -1)
			perror("dup2 failed");
	}
	close(fd.fd_in);
	if (managing_output(cmd->out, &fd))
		dup2(fd.fd_out, STDOUT_FILENO);
	else if (cmd->next)
		change_fd_ouput(fd.fd_p[1], fd.fd_p[0]);
	else
		change_fd_ouput(fd.save_out, fd.fd_p[1]);
	close(fd.fd_out);
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

void	execut_(t_args_n *cmds, t_env *env, t_fd fd)
{
	int		*pids;
	int		i;

	i = 0;
	pids = (int *)malloc(sizeof(int) * count_cmds(cmds));
	if (!pids)
		return ;
	while (cmds)
	{
		pipe(fd.fd_p);
		fd.pid = fork();
		if (fd.pid == 0)
			execute_child(cmds, env->envp, fd);
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
