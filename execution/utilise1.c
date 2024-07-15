/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:09:41 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/15 18:16:58 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    ft_error(t_args_n **cmd, char *msg, int status)
{
    ft_putstr_fd(msg, STDERR_FILENO);
    clear_list(cmd);
    exit(status);
}

int *allocation_array(int size)
{
    int *tab;

    tab = ft_calloc(sizeof(int), size);
    if (!tab)
        return (NULL);
    return (tab);
}
