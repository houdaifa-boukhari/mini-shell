/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:42:44 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/15 18:24:42 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    execution(t_args_n **cmd, t_env *env, t_fd fd)
{
	int     pid;
	char    *path;

	if (is_builtin((*cmd)->arguments, env))
		;
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (managing_input((*cmd)->inp, &fd))
				dup2(fd.fd_in, STDIN_FILENO);
			if (managing_output((*cmd)->out, &fd))
				dup2(fd.fd_out, STDOUT_FILENO);
			path = get_path((*cmd)->arguments[0]);
			if (!path)
			{
				perror((*cmd)->arguments[0]);
				clear_list(cmd);
				exit(EXIT_FAILURE);
			}
			if (execve(path, (*cmd)->arguments, env->envp) == -1)
			{
				perror("failed execution");
				clear_list(cmd);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(NULL);
	}
}

void	change_fd_ouput(int fd, int cfd)
{
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("dup2 failed");
	close(cfd);
	close(fd);
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

void	execute_child(t_args_n *cmd, t_env *env, t_fd fd)
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
		change_fd_ouput(fd.fd_out, fd.fd_p[1]);
	else if (cmd->next)
		change_fd_ouput(fd.fd_p[1], fd.fd_p[0]);
	else
		change_fd_ouput(fd.save_out, fd.fd_p[1]);
	close(fd.fd_p[0]);
	close(fd.fd_out);
	if (is_builtin(cmd->arguments, env))
		exit(EXIT_SUCCESS);
	path = get_path(cmd->arguments[0]);
	if (!path)
	{
		write(2, cmd->arguments[0], ft_strlen(cmd->arguments[0]));
		write(2, " :command not found\n", 21);
		exit(127);
	}
	if (execve(path, cmd->arguments, env->envp) == -1)
	{
		perror("failed execution");
		exit(EXIT_FAILURE);
	}
}

void	execut_(t_args_n *cmds, t_env *env, t_fd fd)
{
	int		*pids;
	int		*pipe_r;
	int		i;

	i = count_cmds(cmds);
	pids = allocation_array(i);
	pipe_r = allocation_array(i);
	i = 0;
	while (cmds)
	{
		pipe(fd.fd_p);
		fd.pid = fork();
		if (fd.pid == 0)
			execute_child(cmds, env, fd);
		else 
		{
			pids[i++] = fd.pid;
			pipe_r[i - 1] = fd.fd_p[0];
			close(fd.fd_p[1]);
			if (!cmds->next)
				break ;
			fd.fd_in = fd.fd_p[0];
			cmds = cmds->next;
		}
	}
	close(fd.fd_in);
	close(fd.fd_p[0]);
	for (int j = 0; j < i; j++)
		close(pipe_r[j]);
	wait_children(pids, i);
}
