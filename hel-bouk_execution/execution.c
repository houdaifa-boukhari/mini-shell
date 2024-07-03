/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:42:44 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/23 12:28:27 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    execution(char **cmd, char **envp)
{
    int     pid;
    char    *path;

    pid = fork();
    if (pid == 0)
    {
        path = get_path(cmd[0]);
        if (!path)
        {
            perror(cmd[0]);
            exit(EXIT_FAILURE);
        }
        if (execve(path, cmd, envp) == -1)
        {
            perror("failed execution");
            exit(EXIT_FAILURE);
        }
    }
    else
        wait(NULL);
}
