/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excev_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:05:24 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/13 23:00:08 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_open_file_b(char *redirection, t_argument *arg,
	int exit_status, char **env)
{
	int	state;

	state = ft_create_file(redirection, arg, exit_status, env);
	if (state)
		return (1);
	return (0);
}

static int	exec_b(t_node *node, char **token, char ***env, int exit_status)
{
	int			fdinput;
	int			fdoutput;
	int			state;
	t_argument	arg;

	(1) && (fdinput = 0, fdoutput = 1, arg.input = 0, arg.output = 1);
	if (ft_strcmp(node->redirections, ""))
	{
		(1) && (fdinput = dup(0), fdoutput = dup(1));
		state = ft_open_file_b(node->redirections, &arg, exit_status, *env);
		if (state)
			return (state);
		if (arg.input && (dup2(arg.input, 0) < 0 || close(arg.input) < 0))
			return (1);
		if (arg.output != 1 && (dup2(arg.output, 1) < 0
				|| close(arg.output) < 0))
			return (1);
	}
	state = ft_exec_bultin(token, env);
	if (dup2(fdinput, 0) < 0 || dup2(fdoutput, 1) < 0
		|| (fdinput != 0 && close(fdinput) < 0)
		|| (fdoutput != 1 && close(fdoutput) < 0))
		return (perror("close or dup2"), 1);
	return (state);
}

int	ft_execv_cmd(t_node *node, char ***env, int exit_status)
{
	char	**token;
	int		i;
	int		state;

	token = ft_token_cmds(node->cmd, *env, exit_status);
	if (!token)
		return (perror("memory problem"), 0);
	if (ft_lstsize(node) == 1 && check_bultin(token[0]))
		state = exec_b(node, token, env, exit_status);
		return (free_mat(token), state);
	}
	else
		return (free_mat(token), ft_exec_list(node, env, exit_status));
	return (0);
}
