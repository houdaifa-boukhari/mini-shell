/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:41:54 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/23 14:30:02 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	**cmds;

	while (1)
	{
		cmd = readline("$ ");
		cmds = ft_split(cmd, ' ');
		free(cmd);
		if (is_builtin(cmds[0]))
			handle_blt(cmds);
		execution(cmds, envp);
	}	 
	return (0);
}

