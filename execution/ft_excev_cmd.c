/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excev_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:05:24 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/28 14:19:18 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_first_cmd(char *str)
{
	int		size;
	char	*new_str;

	size = 0;
	while (str[size] && !is_space(str[size]))
		size++;
	new_str = ft_strndup(new_str, size);
	return (new_str);
}

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
		state = ft_open_file(node->redirections, &input, &output, 0);
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

int	ft_execv_cmd(t_node *node, char ***env)
{
	int		i;
	char   **token;
	
	token = ft_split_cmd(node->cmd);
	if (ft_lstsize(node) == 1 && check_bultin(token[0]))
		return (exec_b(node, env));
	else
		return (ft_exec_list(node, env));
}
