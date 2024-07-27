/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:58:36 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/27 14:30:53 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	run_allherdoc(t_args_n *cmd)
{
	int	i;

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
