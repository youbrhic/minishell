/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 06:35:56 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/24 08:06:19 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void set_node(t_node *node, char **matr, int start, int end)
{
	int		i;

	i = start - 1;
	while (matr[++i] && i < end)
	{
		if (is_redirection(matr[i]))
		{
			if (!node->redirections)
			{
				node->redirections = ft_strndup(matr[i], ft_strlen(matr[i]));
				node->redirections = ft_strjoin(node->redirections, " ");
				node->redirections = ft_strjoin(node->redirections, matr[i + 1]);
			}
			else
			{
				node->redirections = ft_strjoin(node->redirections, " ");
				node->redirections = ft_strjoin(node->redirections, matr[i]);
				node->redirections = ft_strjoin(node->redirections, " ");
				node->redirections = ft_strjoin(node->redirections, matr[i + 1]);
			}
			i++;
		}
		else 
		{
			if (!node->cmd)
				node->cmd = ft_strndup(matr[i], ft_strlen(matr[i]));
			else
			{
				node->cmd = ft_strjoin(node->cmd, " ");
				node->cmd = ft_strjoin(node->cmd, matr[i]);
			}
		}
	}
}

t_node	*create_node(char **matr, int start, int end)
{
	t_node	*node;
	int		i;
	int		index;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	i = start - 1;
	init_node(&node);
	index = check_cmd_line(matr, start, end);
	if (index < 0)
	{
		while (++i < end && matr[i])
		{
			node->cmd = ft_strjoin(node->cmd, matr[i]);
			node->cmd = ft_strjoin(node->cmd, " ");
		}
		return (node);
	}
	else
		set_node(node, matr, start, end);
	return (node);
}
