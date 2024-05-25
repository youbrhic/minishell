/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:02:29 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/22 21:55:51 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_node(t_node **node)
{
	(*node)->cmd = ft_strndup("", 1);
	(*node)->redirections = ft_strndup("", 1);
	(*node)->next = NULL;
}

t_node	*ft_create_list(char *input, char **env, int *exit_status)
{
	t_node	*head;
	char	**token_cmd;
	char	*new_input;
	int		old_status;

	if (g_cld_proc)
		(1) && (*exit_status = g_cld_proc, g_cld_proc = 0);
	(1) && (old_status = *exit_status, new_input = ft_add_space(input));
	if (!new_input)
		return (*exit_status = 258, NULL);
	token_cmd = ft_split_cmd(new_input);
	if (!token_cmd)
		return ((*exit_status = 1), free(new_input), NULL);
	*exit_status = ft_parse_line(token_cmd, env, *exit_status);
	if (*exit_status == 258 || *exit_status == 1)
		return (free(new_input), free_mat(token_cmd), NULL);
	head = ft_get_nodes(token_cmd);
	if (!head)
		return ((*exit_status = old_status), free(new_input),
			free_mat(token_cmd), NULL);
	*exit_status = old_status;
	return (free(new_input), free_mat(token_cmd), head);
}
