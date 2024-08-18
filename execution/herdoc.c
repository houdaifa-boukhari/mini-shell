/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:58:36 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/18 16:13:44 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

bool	run_allherdoc(t_args_n *cmd, t_env *env)
{
	int		i;
	bool	check;

	check = true;
	while (cmd)
	{
		i = 0;
		while (cmd->inp[i].inp)
		{
			if (cmd->inp[i].is_h)
				check = managing_herdoc(&(cmd->inp[i].inp), env);
			if (!check)
			{
				g_exit_status = EXIT_FAILURE;
				break ;
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (check);
}

char	*catch_env(char *line, t_env *env)
{
	char	*ss;
	char	*var;
	char	*re;
	char	c[2];
	int		x;

	x = -1;
	c[1] = '\0';
	re = NULL;
	while (line[++x])
	{
		c[0] = line[x];
		if (line[x] == '$' && line[x + 1] && line[x + 1] != '$'
			&& line[x + 1] != ' ')
		{
			ss = get_name_var(line + x, &x);
			var = search_in_env(env->envp, ss);
			if (var)
				re = strjoin(re, var);
			free(ss);
		}
		else
			re = strjoin(re, c);
	}
	return (free(line), line = NULL, re);
}

void	signal_herdoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		exit(1);
	}
}

void	read_herdoc(char *delim, int tmp_fd, t_env *env)
{
	char	*line;
	char	*line_tmp;

	signal(SIGINT, signal_herdoc);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, delim) == 0)
			break ;
		if (line)
		{
			line_tmp = catch_env(line, env);
			write(tmp_fd, line_tmp, ft_strlen(line_tmp));
			free(line_tmp);
		}
		else
			break ;
	}
	free(line);
	close(tmp_fd);
	free(delim);
	exit(0);
}

bool	managing_herdoc(char **delim, t_env *env)
{
	char	*file;
	int		tmp_fd;
	int		pid;
	int		status;

	*delim = strjoin(*delim, "\n");
	file = ft_strjoin("/tmp/", *delim);
	tmp_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		perror("open failed");
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		read_herdoc(*delim, tmp_fd, env);
	else
	{
		waitpid(0, &status, 0);
		status = WEXITSTATUS(status);
		signal(SIGINT, signal_handler);
		free(*delim);
		*delim = file;
	}
	if (status == 1)
		return (false);
	return (true);
}
