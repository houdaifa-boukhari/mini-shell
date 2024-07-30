/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:47:23 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/30 13:59:08 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*get_path(char *cmd, t_env *envp)
{
	int		i;
	t_envp	*env;	
	char	*tmp;
	char	*path;
	char	**full_path;

	i = 0;
	env = NULL;
	if (access(cmd, X_OK) == 0 && (ft_strncmp(cmd, "/", 1) == 0
			|| ft_strncmp(cmd, "./", 2) == 0))
		return (cmd);
	path = ft_strjoin("/", cmd);
	env = search_env(envp->env, "PATH");
	if (env)
		full_path = ft_split(env->env, ':');
	if (!full_path)
		return (NULL);
	while (full_path[i])
	{
		tmp = ft_strjoin(full_path[i], path);
		if (access(tmp, X_OK) == 0)
			break ;
		free(tmp);
		tmp = NULL;
		i++;
	}
	free(path);
	free_arrays(full_path);
	return (tmp);
}

bool	is_builtin(t_args_n **args, char **cmd, t_env *env)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (false);
	while (i < 7)
	{
		if (!ft_strncmp(cmd[0], BLT_CMDS[i], ft_strlen(cmd[0])))
		{
			handle_blt(args, cmd, env);
			return (true);
		}
		i++;
	}
	return (false);
}

void	handle_blt(t_args_n **args, char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[0], BLT_CMDS[0]))
		exit_status = change_directory(cmd, env->env);
	else if (!ft_strcmp(cmd[0], BLT_CMDS[1]))
		exit_status = echo_handling(cmd, env->envp);
	else if (!ft_strcmp(cmd[0], BLT_CMDS[2]))
		exit_status = get_current_path();
	else if (!ft_strcmp(cmd[0], BLT_CMDS[3]))
	{
		env->check = true;
		exit_status = export_handling(cmd, &(env->env));
	}
	else if (!ft_strcmp(cmd[0], BLT_CMDS[4]))
	{
		env->check = true;
		exit_status = unset_hadnling(&(env->env), cmd);
	}
	else if (!ft_strcmp(cmd[0], BLT_CMDS[5]))
		exit_status = print_env(env->env);
	else if (!ft_strcmp(cmd[0], BLT_CMDS[6]))
		ft_exit(args, cmd);
}
