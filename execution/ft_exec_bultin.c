/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bultin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:02:18 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/24 05:05:22 by youbrhic         ###   ########.fr       */
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
	if (!ft_strcmp(cmd, "echo1"))
		return (1);
	else if (!ft_strcmp(cmd, "cd1"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd1"))
		return (1);
	else if (!ft_strcmp(cmd, "export1"))
		return (1);
	else if (!ft_strcmp(cmd, "unset1"))
		return (1);
	else if (!ft_strcmp(cmd, "env1"))
		return (1);
	else if (!ft_strcmp(cmd, "exit1"))
		return (1);
	return (0);
}

void	ft_exec_bultin(char *cmd, char **env)
{


	// if (!ft_strcmp(command, "echo"))
	// 	ft_echo(args);

	ft_pwd();
	// else if (!ft_strcmp(command, "env"))
	// 	ft_env(env);
	// else if (!ft_strcmp(command, "cd"))
	//     ft_cd(args);
	// else if (!ft_strcmp(lst->cmd, "unset"))
	//     ft_unset(lst->cmd);
	// else if (!ft_strcmp(lst->cmd, "env"))
	//     ft_env(env);
	// else if (!ft_strcmp(lst->cmd, "exit"))
	//     ft_exit();

}