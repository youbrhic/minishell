/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 06:35:56 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/23 05:50:02 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void set_file_redirection(t_node *node, char **matr, int i)
{
	node->list_files_redirections = ft_strndup(matr[i], ft_strlen(matr[i]));
	node->list_files_redirections = ft_strjoin(node->list_files_redirections, " ");
	node->list_files_redirections = ft_strjoin(node->list_files_redirections, matr[i + 1]);
}

static void set_node(t_node *node, char **matr, int *i, int end)
{
	if (!ft_strcmp(matr[*i], "<") || !ft_strcmp(matr[*i], "<<"))
	{
		node->input = open_file(matr[*i + 1], matr[*i]);
		set_file_redirection(node, matr, *i);
		*i += 2;
	}
	else if (!ft_strcmp(matr[*i], ">") || !ft_strcmp(matr[*i], ">>"))
	{
		node->output = open_file(matr[*i + 1], matr[*i]);
		set_file_redirection(node, matr, *i);
		*i += 2;
	}
	while (matr[*i] && *i < end && !is_redirection(matr[*i]))
	{
		node->cmd = ft_strjoin(node->cmd, " ");
		node->cmd = ft_strjoin(node->cmd, matr[*i]);
		(*i)++;
	}
	(*i)--;
}

static void	help_norm(int end, int start, t_node *node, char **matr)
{
	int		i;
	int		index;

	i = start - 1;
	index = check_cmd_line(matr, start, end);
	while (++i < end && matr[i])
	{
		if (is_redirection(matr[i]))
		{
			check_fd(node, matr[i]);
			if (i == index)
			{
				while (start < index)
				{
					node->cmd = ft_strjoin(node->cmd, matr[start++]);
					node->cmd = ft_strjoin(node->cmd, " ");
				}
			}
			set_node(node, matr, &i, end);
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
	help_norm(end, start, node, matr);
	node->next = NULL;
	return (node);
}
