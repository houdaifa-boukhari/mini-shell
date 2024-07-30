/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:58:36 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/30 17:04:34 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	run_allherdoc(t_args_n *cmd)
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
				managing_herdoc(&(cmd->inp[i].inp));
			i++;
		}
		cmd = cmd->next;
	}
}

void	managing_herdoc(char **delim)
{
	char	*line;
	char	*file;
	int		tmp_fd;

	*delim = ft_strjoin(*delim, "\n");
	file = ft_strjoin("/tmp/", *delim);
	tmp_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		perror("open failed");
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, *delim, ft_strlen(line)) == 0)
			break ;
		write(tmp_fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(tmp_fd);
	free(*delim);
	*delim = file;
}
