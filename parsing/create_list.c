/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:52:35 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/24 12:48:48 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_espace(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			c = str[i];
			while (str[++i] && str[i] != c)
				;
		}
		else
		{
			if (!is_space(str[i]))
				return (1);
		}
	}
	return (0);
}

static void print_error(char *str)
{
	char	*error;

	error = ft_strndup("minishell :", 11);
	error = ft_strjoin(error, str);
	error = ft_strjoin(error, ": ambiguous redirect");
	write(2, error, ft_strlen(error));
	free(error);
}

static int check_ambiguous(char **matr)
{
	int		i;

	if (!matr || !matr[0])
		return (0);
	expand(matr, 1);
	i = -1;
	while (matr[++i])
	{
		if (!ft_strcmp(matr[i], "<<"))
			i++;
		if (!is_oper(matr[i]))
		{
			if (check_espace(matr[i]))
				return (i);
		}
	}
	return (-1);
}

t_node	*create_list(char **matr)
{
	t_node *head;
	char	**token_cmd;
	int		index;

	head = get_nodes(matr);
	if (!head)
		return (NULL);
	token_cmd = ft_split_cmd(head->redirections);
	if ((index = check_ambiguous(token_cmd)) > 0)
		return (free(token_cmd), print_error(matr[index + 1]), NULL);
	free(head);
	expand(matr, 1);
	head = get_nodes(matr);
	return (head);
}
