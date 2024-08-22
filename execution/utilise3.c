/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:06:32 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/22 09:55:22 by hel-bouk         ###   ########.fr       */
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
