/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:21:21 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/24 09:23:08 by youbrhic         ###   ########.fr       */
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