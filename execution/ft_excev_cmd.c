/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excev_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:05:24 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/02 22:54:24 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_open_file_b(char *redirection, int *input, int *output, int exit_status, char **env)
{
	int	state;

	state = ft_create_file(redirection, input, output, exit_status, env);
	if (state)
		return (1);
	return (0);
}

int exec_b(t_node *node, char **token, char ***env, int exit_status)
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
		state = ft_open_file_b(node->redirections, &input, &output, exit_status, *env);
		if (state)
			return (state);
		if (input && (dup2(input,0) < 0 || close(input) < 0))
			return (1);
		if (output != 1 && (dup2(output, 1) < 0 || close(output) < 0 ))
			return (1);
	}
	state = ft_exec_bultin(token, env);
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
	int		state;

	token = ft_split_cmd(node->cmd);
	ft_expand(token, 1, exit_status, *env);
	ft_remove_quotes(token);
	if (ft_lstsize(node) == 1 && check_bultin(token[0]))
		state = exec_b(node, token, env, exit_status);
	else
		ft_exec_list(node, env, exit_status);
	free_mat(token);
	return (state);
}
