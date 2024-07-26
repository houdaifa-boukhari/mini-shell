/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:41:54 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/26 14:04:56 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	exit_status = 0;

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

char	*get_line(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline("hel-bouk>$ ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (check_line(line))
			line[ft_strlen(line) - 1] = '\0';
		if (!line)
			return (NULL);
	}
	add_history(line);
	if (!line || !*line)
		return (NULL);
	return (line);
}

int main(int argc, char **argv, char **envp)
{
	t_args_n	*cmd;
	t_env		env;
	t_fd		fd;
	char		*line;
	int			status;

	status = 0;
	env.envp = NULL;
	env.env = NULL;
	env.check = true;
	cmd = NULL;
	fd.save_in = dup(STDIN_FILENO);
	fd.save_out = dup(STDOUT_FILENO);
	parsing_env(&(env.env), envp);
	while (1)
	{
		line = get_line();
		if (!isatty(STDIN_FILENO) && !line)
			break ;
		else if (!line)
			continue ;
		cmd = initialization_list(line, env.env);
		free(line);
		fd.fd_in = fd.save_in;
		fd.fd_out = fd.save_out;
		run_allherdoc(cmd);
		built_array(&env);
		if (count_cmds(cmd) == 1)
			execution(&cmd, &env, fd);
		else
			execut_(&cmd ,&env, fd);
			dprintf(2, "status is %d\n", exit_status);
		clear_list(&cmd);
	}
	rl_clear_history();
	return (0);
}
