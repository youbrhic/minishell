/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:01:51 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/30 13:22:00 by youbrhic         ###   ########.fr       */
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
			return (perror("Error"), -1);
	}
	return (0);
}

static int	ft_pipe(int	*p_1, int *p_2, t_node*node, int i)
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
	if ((i == 1) && node->next && ((dup2(p_1[1], 1) < 0)))
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
		else if ((i % 2 == 0) && ((dup2(p_1[0], 0) < 0) || \
			(dup2(p_2[1], 1) < 0)))
			return (perror("Error"), -1);
		else if ((i % 2 != 0) && ((dup2(p_2[0], 0) < 0) ||
			(dup2(p_1[1], 1) < 0)))
			return (perror("Error"), -1);
	}
	return (0); 
}

int	exec_list(t_node *lst, int *p_1, int *p_2, char **env)
{
	int			i;
	int			pid;
	int			input;
	int			output;

	i = 0;
	input = 0;
	output = 1;
	while (lst && ++i)
	{
		if ((ft_pipe(p_1, p_2, lst, i) < 0))
			return (-1);
		pid = fork();
		if (pid == 0)
		{
			if (0 <= ft_dup(p_1, p_2, lst, i))
			{
				if (lst->redirections && open_file(lst->redirections, &input, &output) < 0)
					exit(1);
				exec_cmd(lst->cmd, env);
			}
			exit(1);
		}
		ft_close_fd(p_1, p_2, i);
		lst = lst->next;
	}
	while (0 < wait(NULL))
		;
	return (0);
}
