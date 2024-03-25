/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 07:24:24 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/24 09:23:17 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (free(s1), str);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*temp;

	if (!new)
	{
		*lst = NULL;
		return ;
	}
	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static void	del(void *p)
{
	t_node	*node;

	node = p;
	if (node->cmd)
		free(node->cmd);
	if (node->redirections)
		free(node->redirections);
}

void	ft_lstclear(t_node **lst)
{
	t_node	*l;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		l = (*lst)->next;
		del(*lst);
		free(*lst);
		*lst = l;
	}
	*lst = NULL;
}

int	ft_lstsize(t_node *lst)
{
	t_node	*temp;
	int		size;

	if (!lst)
		return (0);
	temp = lst;
	size = 0;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}