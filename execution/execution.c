/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:42:44 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/31 14:45:25 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	execution(t_args_n **cmd, t_env *env, t_fd fd)
{
	char	*path;
	int		status;

	if (is_builtin(cmd, (*cmd)->arguments, env))
		return ;
	fd.pid = fork();
	if (fd.pid == 0)
	{
		if (managing_input((*cmd)->inp, &fd))
			dup2(fd.fd_in, STDIN_FILENO);
		if (managing_output((*cmd)->out, &fd))
			dup2(fd.fd_out, STDOUT_FILENO);
		path = get_path((*cmd)->arguments[0], env->envp);
		if (!path)
		{
			free_env(&(env->env));
			ft_putstr_fd((*cmd)->arguments[0], STDERR_FILENO);
			ft_error(cmd, ": command not found\n", 127);
		}
		if (execve(path, (*cmd)->arguments, env->envp) == -1)
			ft_error(cmd, "failed execution", EXIT_FAILURE);
	}
	waitpid(fd.pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
}

void	wait_children(int *fd, int *pids, int size)
{
	int	status;
	int	i;

	i = 0;
	while (i < size)
		close(fd[i++]);
	i = 0;
	while (i < size)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			free(pids);
			free(fd);
			exit(EXIT_FAILURE);
		}
		g_exit_status = WEXITSTATUS(status);
		i++;
	}
	free(pids);
	free(fd);
}

void	controle_fd(t_args_n *cmd, t_args_n **cmds, t_fd fd)
{
	if (managing_input(cmd->inp, &fd))
		change_fd_in(fd.fd_in, cmds);
	else if (fd.fd_in != 0)
		change_fd_in(fd.fd_in, cmds);
	close(fd.fd_in);
	if (managing_output(cmd->out, &fd))
		change_fd_ouput(fd.fd_out, fd.fd_p[1]);
	else if (cmd->next)
		change_fd_ouput(fd.fd_p[1], fd.fd_p[0]);
	else
		change_fd_ouput(fd.save_out, fd.fd_p[1]);
	close(fd.fd_p[0]);
	close(fd.fd_out);
}

void	execute_child(t_args_n *cmd, t_args_n **cmds, t_env *env, t_fd fd)
{
	char		*path;

	path = NULL;
	controle_fd(cmd, cmds, fd);
	if (is_builtin(cmds, cmd->arguments, env))
		exit(g_exit_status);
	path = get_path(cmd->arguments[0], env->envp);
	if (!path)
	{
		path = ft_strjoin(cmd->arguments[0], " :command not found\n");
		ft_putstr_fd(path, 2);
		free(path);
		clear_history();
		clear_list(cmds);
		free_env(&(env->env));
		exit(127);
	}
	if (execve(path, cmd->arguments, env->envp) == -1)
		ft_error(cmds, "failed execution", EXIT_FAILURE);
}

void	execut_(t_args_n **cmds, t_env *env, t_fd fd)
{
	int			*pids;
	int			*pipe_r;
	int			i;
	t_args_n	*cmd;

	i = count_cmds(*cmds);
	pids = allocation_array(i);
	pipe_r = allocation_array(i);
	cmd = *cmds;
	i = 0;
	while (cmd)
	{
		pipe(fd.fd_p);
		fd.pid = fork();
		if (fd.pid == 0)
			execute_child(cmd, cmds, env, fd);
		pids[i++] = fd.pid;
		pipe_r[i - 1] = fd.fd_p[0];
		close(fd.fd_p[1]);
		if (!(cmd)->next)
			break ;
		fd.fd_in = fd.fd_p[0];
		cmd = (cmd)->next;
	}
	wait_children(pipe_r, pids, i);
}
