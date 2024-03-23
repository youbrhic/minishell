/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:01:51 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/23 12:11:04 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	dup_redirection (t_node *node)
{
	if (node->input == -1)
		return (-1);	
    if (node->input != 0)
		dup2(node->input, 0);
	if (node->output != 1)
		dup2(node->output, 1);
	return (1);
}

void	exec_node(t_node *node, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(-1);
	else if (pid == 0)
	{
		if (dup_redirection(node) > 0)
			exec_cmd(node->cmd, env);
	}
	else
		wait(&pid);
}
