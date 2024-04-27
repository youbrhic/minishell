/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:02:29 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/27 12:07:23 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_espace(char *str)
{
	int		i;
	char	c;

	i = -1;
	if (!str)
		return (1);
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
			if (is_space(str[i]))
				return (1);
		}
	}
	return (0);
}

static void	print_error(char *str)
{
	char	*error;

	error = ft_strndup("minishell :", 11);
	error = ft_strjoin(error, str);
	error = ft_strjoin(error, ": ambiguous redirect");
	if (!error)
		return ;
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	free(error);
}

static int	check_ambiguous(char *redirections, int *exit_status)
{
	char	**token;
	char	**copy;
	int		i;

	token = ft_split_cmd(redirections);
	if (!token)
		return (1);
	copy = get_matr_copy(token);
	if (!copy)
		return (free_mat(&token), 1);
	ft_expand(token, 1, *exit_status);
	ft_remove_quotes(token);
	i = -1;
	while (token[++i])
	{
		if (is_redirection(token[i]))
		{
			if (!ft_strlen(token[i + 1]) || ft_strlen(token[i + 1]) == 1|| is_oper(token[i + 1]) || check_espace(token[i + 1]))
				return (print_error(copy[i + 1]), free_mat(&token), free_mat(&copy), 1);
		}
	}
	return (free_mat(&token), free_mat(&copy), 0);
}

static t_node *ft_get_list(char **token, t_node *head, int *exit_status)
{
	t_node *new_head;

	ft_expand(token, 1, *exit_status);
	new_head = ft_get_nodes(token);
	if (!new_head)
		return (ft_lstclear(&head), NULL);
	return (ft_lstclear(&head), new_head);	
}

t_node	*ft_create_list(char *input, int *exit_status)
{
	t_node	*head;
	char	**token_cmd;
	char	*new_input;

	new_input = ft_add_space(input);
	if (!new_input)
		return (NULL);
	token_cmd = ft_split_cmd(new_input);
	if (!token_cmd)
		return (free(new_input), NULL);
	if (ft_parse_line(token_cmd) == 258)
		return (*exit_status = 258, free(new_input), free_mat(&token_cmd), NULL);
	head = ft_get_nodes(token_cmd);
	if (!head)
		return (free(new_input), free_mat(&token_cmd), NULL);
	if (check_ambiguous(head->redirections, exit_status) == 1)
		return ((*exit_status = 1), free(new_input), ft_lstclear(&head), free_mat(&token_cmd), NULL);
	else
		head = ft_get_list(token_cmd, head, exit_status);
	return (free(new_input), free_mat(&token_cmd), head);
}
