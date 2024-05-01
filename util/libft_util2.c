/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 07:24:24 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/01 07:51:02 by youbrhic         ###   ########.fr       */
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
	if (!s1)
		return (NULL);
	else if (!s2 && s1)
		return (free (s1), NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free(s1), NULL);
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

int	get_index_dollar(char *str, int flag)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && flag)
		{
			while (str[i] && str[++i] != '\'')
				;
		}
		else if (str[i] && str[i] == '\"')
		{
			while (str[i] && str[++i] != '\"')
			{
				if (str[i] == '$' && str[i + 1] != '\"'
					&& !is_space(str[i + 1]))
					return (i);
			}
		}
		else if (str[i] == '$'
			&& (i + 1 < ft_strlen(str) && (is_alphanum(str[i + 1])
					|| str[i + 1] == '?' || str[i + 1] == '_')))
			return (i);
	}
	return (-1);
}
