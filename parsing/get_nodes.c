/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:13:12 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/24 13:00:00 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_pipes(char **matr)
{
	int		i;
	int		count;

	if (!matr || !*matr)
		return (0);
	i = -1;
	count = 1;
	while (matr[++i])
	{
		if (!ft_strcmp(matr[i], "|"))
			count++;
	}
	return (count);
}

static void	help_norm(char **matr, t_node **head, int end, int start)
{
	int		nb_pipes;

	nb_pipes = count_pipes(matr);
	while (nb_pipes-- > 0 && matr[++end])
	{
		while (matr[end] && ft_strcmp(matr[end], "|"))
			end++;
		if (!*head)
		{
			*head = create_node(matr, start, end);
			if (!*head)
				return ;
		}
		else
		{
			ft_lstadd_back(head, create_node(matr, start, end));
			if (!*head)
				return ;
		}
		start = end + 1;
	}
}

t_node	*get_nodes(char **matr)
{
	int		start;
	int		end;
	int		nb_pipes;
	t_node	*head;

	if (!matr && !*matr)
		return (NULL);
	start = 0;
	end = -1;
	head = NULL;
	nb_pipes = count_pipes(matr);
	if (nb_pipes == 1)
		return (create_node(matr, 0, get_size_mat(matr)));
	help_norm(matr, &head, end, start);
	return (head);
}
