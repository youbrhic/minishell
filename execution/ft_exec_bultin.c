/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bultin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:02:18 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/02 17:00:37 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	return (ft_strndup(cmd, i));
}

char	*get_args(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	return (ft_strndup(cmd + i, ft_strlen(cmd) - i));
}

int	check_bultin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	ft_exec_bultin(char **args, char ***env)
{
	int	exit_state;

	if (!ft_strcmp(args[0], "cd"))
		exit_state = ft_cd(args, env);
	else if (!ft_strcmp(args[0], "echo"))
		exit_state = ft_echo(args);
	else if (!ft_strcmp(args[0], "env"))
		exit_state = ft_env(args, env);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args);
	else if (!ft_strcmp(args[0], "pwd"))
		exit_state = ft_pwd(args);
	else if (!ft_strcmp(args[0], "unset"))
		exit_state = ft_unset(args, env);
	else if (!ft_strcmp(args[0], "export"))
		exit_state = ft_export(args, env);
	else
		exit_state = 0;
	return (exit_state);
}
