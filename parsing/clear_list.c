/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-26 21:37:16 by zbakkas           #+#    #+#             */
/*   Updated: 2024-07-26 21:37:16 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min.h"

void	remove_file(t_inp *inp);

void	clear_list(t_args_n **lst)
{
	t_args_n	*nexttte;
	int			i;

	if (!lst)
		return ;
	while (*lst)
	{
		i = 0;
		// remove_file((*lst)->inp);
		nexttte = (*lst)->next;
		while ((*lst)->arguments[i])
			free((*lst)->arguments[i++]);
		free((*lst)->arguments);
		i = 0;
		while ((*lst)->inp[i].inp)
			free((*lst)->inp[i++].inp);
		free((*lst)->inp);
		i = 0;
		while ((*lst)->out[i].out)
			free((*lst)->out[i++].out);
		free((*lst)->out);
		free(*lst);
		*lst = nexttte;
	}
	*lst = NULL;
}
