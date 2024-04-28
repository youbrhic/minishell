/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:23:29 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/27 03:56:18 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_close_fd(int	*p_1, int *p_2, int i)
{
	if (i % 2 == 0)
	{
		if (close(p_1[0]) < 0)
			return (perror("Error"), -1);
	}
	if ((1 < i) && (i % 2 != 0))
	{
		if (close(p_2[0]) < 0)
			return (perror("Error gg"), -1);
	}
	return (0);
}

static int	ft_pipe(int	*p_1, int *p_2, t_node *node, int i)
{
	if ((i == 1) && node->next && ((pipe(p_1) < 0)))
		return (perror("Error"), -1);
	else if (1 < i)
	{
		if (!node->next)
		{
			if ((i % 2 == 0) && ((close(p_1[1]) < 0)))
				return (perror("Error"), -1);
			else if (i % 2 != 0 && ((close(p_2[1]) < 0)))
				return (perror("Error"), -1);
		}
		else if ((i % 2 == 0) && \
			((close(p_1[1]) < 0) || (pipe(p_2) < 0)))
			return (perror("Error"), -1);
		else if ((i % 2 != 0) && \
			((close(p_2[1]) < 0) || (pipe(p_1) < 0)))
			return (perror("Error"), -1);
	}
	return (0);
}

static int	ft_dup(int	*p_1, int *p_2, t_node *node, int i)
{
	if ((i == 1) && node->next && (((dup2(p_1[1], 1) < 0)
				|| (close(p_1[0]) < 0))))
		return (perror("Error"), -1);
	else if (1 < i)
	{
		if (!node->next)
		{
			if ((i % 2 == 0) && ((dup2(p_1[0], 0) < 0)))
				return (perror("Error"), -1);
			else if (i % 2 != 0 && ((dup2(p_2[0], 0) < 0)))
				return (perror("Error"), -1);
		}
		else if ((i % 2 == 0) && ((dup2(p_1[0], 0) < 0)
				|| (close(p_1[0]) < 0) || (dup2(p_2[1], 1) < 0)
				|| close(p_2[0]) < 0))
			return (perror("Error"), -1);
		else if ((i % 2 != 0) && ((dup2(p_2[0], 0) < 0) || (close(p_2[0]) < 0)
				|| (dup2(p_1[1], 1) < 0) || (close(p_1[0]) < 0)))
			return (perror("Error"), -1);
	}
	return (0);
}

static void	exec_node(t_node *lst, int *input, int *output, char ***env)
{
	int	state;

	if (lst->redirections)
	{
		state = ft_open_file(lst->redirections, input, output, 1);
		if (state)
			exit(state);
	}
	state = ft_exec_cmd(lst->cmd, env);
	if (state)
		exit(state);
}

int	ft_exec_list(t_node *lst, char ***env)
{
	int			i;
	int			pid;
	t_argument	args;
	int			status;

	(1) && (i = 0, args.input = 0, args.output = 1);
	while (lst && ++i)
	{
		if ((ft_pipe(args.p_1, args.p_2, lst, i) < 0))
			return (-1);
		pid = fork();
		if (pid == 0)
		{
			if (0 <= ft_dup(args.p_1, args.p_2, lst, i))
				exec_node(lst, &args.input, &args.output, env);
		}
		else if (pid == -1)
			return (-1);
		(1) && (ft_close_fd(args.p_1, args.p_2, i), lst = lst->next);
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	return (WEXITSTATUS(status));
}

// printf ("%d \n", WEXITSTATUS(status));