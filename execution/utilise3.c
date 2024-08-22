/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:06:32 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/22 17:51:08 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	error_files(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!ft_strcmp(file, ""))
		ft_putstr_fd(": ", STDERR_FILENO);
	perror(file);
}

void	give_error(t_args_n *cmd)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", cmd->arguments[0]);
	if (cmd->arguments && cmd->arguments[0] && *cmd->arguments[0])
		str = ft_strjoin(tmp, " :command not found\n");
	else
		str = ft_strjoin(tmp, ":command not found\n");
	ft_putstr_fd(str, STDERR_FILENO);
	free(str);
	free(tmp);
}

void	ctl_error(char *msg, bool *check)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	*check = false;
}

bool	error_fork(t_fd fd)
{
	if (fd.pid < 0)
	{
		close(fd.fd_p[0]);
		close(fd.fd_p[1]);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror("fork");
		return (true);
	}
	return (false);
}
