/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:06:15 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/10 12:02:58 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    creat_list(t_envp **envp, char *line)
{
	t_envp   *ptr;
	t_envp   *new_env;

	if (!envp)
		return ;
	new_env = (t_envp *)malloc(sizeof(t_envp));
	if (!new_env)
		return ;
	new_env->env = ft_strdup(line);
	new_env->next = NULL;
	if (!*envp)
	{
		*envp = new_env;
		(*envp)->prev = NULL;
		return ;
	}
	ptr = *envp;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_env;
	new_env->prev = ptr; 
}

void	parsing_env(t_envp **env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		creat_list(env, envp[i]);
		i++;
	}
}

bool	managing_input(t_inp *input, t_fd *fd)
{
	int	i;

	i = 0;
	if (!input)
		return (false);
	while (input[i].inp)
	{
		if (input[i].is_h)
			managing_herdoc(input[i].inp, fd);
		else
		{
			fd->fd_in = open(input[i].inp, O_RDONLY);
			if (fd->fd_in < 0)
				perror(input[i].inp);
		}
		i++;
	}
	return (true);
}

bool	managing_output(t_out *output, t_fd *fd)
{
	int	i;

	i = 0;
	if (!output)
		return (false);
	while (output[i].out)
	{
		if (output[i].is_a)
			fd->fd_out = open(output[i].out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd->fd_out = open(output[i].out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd->fd_out < 0)
			perror(output[i].out);
		i++;
	}
	return (true);
}


void	managing_herdoc(char *delim, t_fd *fd)
{
	char	*line;
	int		tmp_fd;

	delim = ft_strjoin(delim, "\n");
	tmp_fd = open("/tmp/herdoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		perror("open failed");
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, delim, ft_strlen(line)) == 0)
			break ;
		write(tmp_fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(tmp_fd);
	tmp_fd = open("/tmp/herdoc", O_RDONLY);
	fd->fd_in = tmp_fd;
	free(delim);
}