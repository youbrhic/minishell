/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excev_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:05:24 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/01 07:38:08 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int ft_open_file_b(char *redirection, int *input, int *output, int exit_status)
// {
// 	int	state;

// 	state = ft_create_files(redirection, input, output, exit_status);
// 	if (state)
// 		return (1);
// 	return (0);
// }

static int exec_b(t_node *node, char ***env)
{
	int		fdinput;
	int		fdoutput;
	int		state;
	int		input;
	int		output;

	(1) && (fdinput = 0, fdoutput = 1, input = 0, output = 1);
	if (ft_strcmp(node->redirections, ""))
	{
		(1) && (fdinput = dup(0) ,fdoutput = dup(1));
		state = ft_open_file(node->redirections, &input, &output, 1);
		if (state)
			return (state);
		if (input && (dup2(input,0) < 0 || close(input) < 0))
			return (1);
		if (output != 1 && (dup2(output, 1) < 0 || close(output) < 0 ))
			return (1);
	}

	state = ft_exec_bultin(ft_split_cmd(node->cmd), env);
	if ( dup2(fdinput, 0) < 0 || dup2(fdoutput, 1) < 0 
		|| (fdinput != 0 && close(fdinput) < 0) 
		|| (fdoutput != 1 && close(fdoutput) < 0))
		return (1);
	return (state);
}

int	ft_execv_cmd(t_node *node, char ***env, int exit_status)
{
	char	**token;
	int		i;

	token = ft_split_cmd(node->cmd);
	// if (ft_lstsize(node) == 1 && check_bultin(token[0]))
	// 	return (free_mat(&token), exec_b(node, env));
	// else
		return (free_mat(token), ft_exec_list(node, env, exit_status));
}
