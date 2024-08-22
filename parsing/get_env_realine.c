/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_realine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:32:57 by zbakkas           #+#    #+#             */
/*   Updated: 2024/08/22 09:53:34 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*get_str_redline(void)
{
	char	*re;
	char	*user;

	user = getenv("USER");
	re = ft_strjoin("\033[0;32m", user);
	re = ft_strjoin(re, "\033[0m\033[1;37m@1337 ");
	re = ft_strjoin(re, "\033[0;36mminishell\033[0m$ ");
	return (re);
}
