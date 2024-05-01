/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:13:12 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/01 06:12:54 by youbrhic         ###   ########.fr       */
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

static void	add_node(t_node **head, t_node *new_node)
{
	if (!new_node)
	{
		ft_lstclear(head);
		*head = NULL;
	}
	ft_lstadd_back(head, new_node);
}

static void	set_list(char **matr, t_node **head, int end, int start)
{
	int		nb_pipes;
	t_node	*tmp;

	nb_pipes = count_pipes(matr);
	while (nb_pipes-- > 0 && matr[++end])
	{
		while (matr[end] && ft_strcmp(matr[end], "|"))
			end++;
		if (!*head)
			*head = ft_create_node(matr, start, end);
		else
			add_node(head, ft_create_node(matr, start, end));
		if (!*head)
			return ;
		start = end + 1;
	}
}

t_node	*ft_get_nodes(char **matr)
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
		return (ft_create_node(matr, 0, get_size_mat(matr)));
	set_list(matr, &head, end, start);
	return (head);
}
