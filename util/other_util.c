/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:21:21 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/22 10:21:15 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(char	*str)
{
	return (!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")
		|| !ft_strcmp(str, "<") || !ft_strcmp(str, ">"));
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

char	**free2d(char ***arr, int index)
{
	int	i;

	i = 0;
	while (index - i > 0)
	{
		free((*arr)[index - i]);
		i++;
	}
	free(*arr);
	return (NULL);
}

int	is_oper(char *str)
{
	return (!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")
		|| !ft_strcmp(str, "|") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">"));
}
