/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bultin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:02:18 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/21 06:19:16 by youbrhic         ###   ########.fr       */
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

int	ft_exec_bultin(char **args, char ***env, int flag)
{
	int	exit_state;

	exit_state = 0;
	if (!ft_strcmp(args[0], "cd"))
		exit_state = ft_cd(args, env);
	else if (!ft_strcmp(args[0], "echo"))
		exit_state = ft_echo(args);
	else if (!ft_strcmp(args[0], "env"))
		exit_state = ft_env(args, env);
	else if (!ft_strcmp(args[0], "exit"))
		exit_state = ft_exit(args, *env, flag);
	else if (!ft_strcmp(args[0], "pwd"))
		exit_state = ft_pwd(args);
	else if (!ft_strcmp(args[0], "unset"))
		exit_state = ft_unset(args, env);
	else if (!ft_strcmp(args[0], "export"))
		exit_state = ft_export(args, env);
	return (exit_state);
}
