/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:41:54 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/22 09:55:22 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int		g_exit_status;

char	*get_line(bool *ctl_d)
{
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		line = readline("hel-bouk>$ ");
		if (!line)
		{
			*ctl_d = true;
			printf("exit\n");
		}
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (check_line(line))
			line[ft_strlen(line) - 1] = '\0';
	}
	add_history(line);
	if (!line || !*line)
	{
		free(line);
		line = NULL;
	}
	return (line);
}

void	initilze_struct(t_env *env, char **envp, t_fd *fd)
{
	env->envp = NULL;
	env->env = NULL;
	env->check = true;
	fd->save_in = dup(STDIN_FILENO);
	fd->save_out = dup(STDOUT_FILENO);
	parsing_env(&(env->env), envp);
}

void	read_line(t_fd fd, t_env *env)
{
	char		*line;
	bool		ctl_d;
	t_args_n	*cmd;

	cmd = NULL;
	while (1)
	{
		clear_list(&cmd);
		line = get_line(&ctl_d);
		if ((!isatty(STDIN_FILENO) && !line) || ctl_d)
			break ;
		else if (!line)
			continue ;
		built_array(env);
		cmd = initialization_list(line, env->envp);
		free(line);
		fd.fd_in = fd.save_in;
		fd.fd_out = fd.save_out;
		if (cmd && !run_allherdoc(cmd, env))
			continue ;
		if (cmd && count_cmds(cmd) == 1)
			execution(&cmd, env, fd);
		else if (cmd)
			execut_(&cmd, env, fd);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;
	t_fd	fd;

	(void)ac;
	(void)av;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	initilze_struct(&env, envp, &fd);
	read_line(fd, &env);
	free_arrays(env.envp);
	free_env(&(env.env));
	rl_clear_history();
	return (g_exit_status);
}
