/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:41:54 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/14 16:53:06 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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

int main(int argc, char **argv, char **envp)
{
	t_args_n	*cmd;
	t_env		env;
	t_fd		fd;
	char		*line;

	env.envp = envp;
	env.env = NULL;
	cmd = NULL;
	fd.fd_in = 0;
	fd.save_in = dup(STDIN_FILENO);
	fd.save_out = dup(STDOUT_FILENO);
	parsing_env(&(env.env), env.envp);
	while (1)
	{
		line = readline("hel-bouk>$ ");
		add_history(line);
		if (!line || !*line)
			continue ;
		cmd = initialization_list(line);
		free(line);
		fd.fd_in = fd.save_in;
		fd.fd_out = fd.save_out;
		run_allherdoc(cmd);
		if (count_cmds(cmd) == 1)
			execution(&cmd, &env, fd);
		else
			execut_(cmd ,&env, fd);
		clear_list(&cmd);
	}
	return (0);
}
