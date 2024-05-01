/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:47:47 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/01 06:16:24 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_cmd_line(char **matr, int start, int end)
{
	int		i;

	i = start;
	while (i < get_size_mat(matr) && matr[i] && i < end)
	{
		if (is_redirection(matr[i]))
			return (i);
		i++;
	}
	return (-1);
}

static char	*join_word(char *str1, char *str2, char *str3, int space)
{
	char	*new_str;

	if (space)
	{
		new_str = ft_strndup(str1, ft_strlen(str1));
		new_str = ft_strjoin(new_str, " ");
		new_str = ft_strjoin(new_str, str2);
	}
	else
		new_str = ft_strndup(str2, ft_strlen(str2));
	if (!new_str)
		return (NULL);
	new_str = ft_strjoin(new_str, " ");
	new_str = ft_strjoin(new_str, str3);
	return (free(str1), new_str);
}

static void	set_node(t_node *node, char **matr, int start, int end)
{
	int		i;

	i = start - 1;
	while (matr[++i] && i < end)
	{
		if (is_redirection(matr[i]))
		{
			if (!*node->redirections)
				node->redirections = join_word(node->redirections,
						matr[i], matr[i + 1], 0);
			else
				node->redirections = join_word(node->redirections,
						matr[i], matr[i + 1], 1);
			i++;
		}
		else
		{
			if (!*node->cmd)
				node->cmd = join_word(node->cmd, matr[i], "", 0);
			else
				node->cmd = join_word(node->cmd, matr[i], "", 1);
		}
		if (!node->cmd || !node->redirections)
			break ;
	}
}

static t_node	*get_val_node(t_node *node)
{
	if (!node->cmd || !node->redirections)
		return (ft_lstclear(&node), NULL);
	return (node);
}

t_node	*ft_create_node(char **matr, int start, int end)
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
			if (ft_strlen(node->cmd) != 0)
				node->cmd = ft_strjoin(node->cmd, " ");
			node->cmd = ft_strjoin(node->cmd, matr[i]);
		}
	}
	else
		set_node(node, matr, start, end);
	return (get_val_node(node));
}
