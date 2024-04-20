/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:21:21 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/20 03:34:34 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(char	*str)
{
	return (!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")
		|| !ft_strcmp(str, "<") || !ft_strcmp(str, ">"));
}

void	init_node(t_node **node)
{
	(*node)->cmd = ft_strndup("", 1);
	(*node)->redirections = NULL;
	(*node)->next = NULL;
}

void	ft_perror(char *str, int ex)
{
	perror(str);
	exit(ex);
}

int	get_size_mat(char **str)
{
	int		i;
	int		count;

	if (!str || !*str)
		return (0);
	i = -1;
	count = 0;
	while (str[++i])
		count++;
	return (count);
}
