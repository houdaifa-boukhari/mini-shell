/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:58:36 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/15 21:28:03 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	run_allherdoc(t_args_n *cmd, t_env *env)
{
	int	i;

	if (!cmd)
		return ;
	while (cmd)
	{
		i = 0;
		while (cmd->inp[i].inp)
		{
			if (cmd->inp[i].is_h)
				managing_herdoc(&(cmd->inp[i].inp), env);
			i++;
		}
		cmd = cmd->next;
	}
}

char	*catch_env(char *line, t_env *env)
{
	char	*ss;
	char	*var;
	char	*re;
	char 	c[2];
	int		x;

	x = -1;
	c[1] = '\0';
	re = NULL;
	while (line[++x])
	{
		c[0] = line[x];
		if(line[x] == '$' && line[x + 1] && line[x + 1] != '$' && line[x + 1] != ' ')
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

void	managing_herdoc(char **delim, t_env *env)
{
	char	*line;
	char	*file;
	int		tmp_fd;
	char	*line_tmp;

	*delim = ft_strjoin(*delim, "\n");
	file = ft_strjoin("/tmp/", *delim);
	tmp_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		perror("open failed");
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, *delim) == 0)
			break ;
		line_tmp = catch_env(line, env);
		write(tmp_fd, line_tmp, ft_strlen(line_tmp));
		free(line_tmp);
	}
	free(line);
	close(tmp_fd);
	free(*delim);
	*delim = file;
}

void	change_fd_ouput(int fd, int cfd)
{
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("dup2 failed");
	close(cfd);
	close(fd);
}

void	change_fd_in(int fd, t_args_n **cmd)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		ft_error(cmd, "dup2 failed", EXIT_FAILURE);
	}
	close(fd);
}
