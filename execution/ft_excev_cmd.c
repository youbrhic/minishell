/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excev_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:05:24 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/02 01:46:16 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_open_file_b(char *redirection, int *input, int *output, int exit_status)
{
	int	state;

	state = ft_create_file(redirection, input, output, exit_status);
	if (state)
		return (1);
	return (0);
}

static	int exec_b(t_node *node, char ***env, int exit_status)
{
	int		fdinput;
	int		fdoutput;
	int		state;
	int		input;
	int		output;
	char	**token;

	(1) && (fdinput = 0, fdoutput = 1, input = 0, output = 1);
	if (ft_strcmp(node->redirections, ""))
	{
		(1) && (fdinput = dup(0) ,fdoutput = dup(1));
		state = ft_open_file_b(node->redirections, &input, &output, exit_status);
		if (state)
			return (state);
		if (input && (dup2(input,0) < 0 || close(input) < 0))
			return (1);
		if (output != 1 && (dup2(output, 1) < 0 || close(output) < 0 ))
			return (1);
	}
	token = ft_split_cmd(node->cmd);
	ft_expand(token, 1, exit_status);
	ft_remove_quotes(token);
	state = ft_exec_bultin(token, env);
	if ( dup2(fdinput, 0) < 0 || dup2(fdoutput, 1) < 0 
		|| (fdinput != 0 && close(fdinput) < 0) 
		|| (fdoutput != 1 && close(fdoutput) < 0))
		return (1);
	return ( state);
}

int	ft_execv_cmd(t_node *node, char ***env, int exit_status)
{
	char	**tokens;
	int		i;

	tokens = ft_split_cmd(node->cmd);
	ft_expand(tokens, 1, exit_status);
	ft_remove_quotes(tokens);
	if (ft_lstsize(node) == 1 && check_bultin(tokens[0]))
		return (free_mat(tokens), exec_b(node, env, exit_status));
	else
		return (free_mat(tokens), ft_exec_list(node, env, exit_status));
}
