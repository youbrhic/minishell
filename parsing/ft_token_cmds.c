/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 00:09:02 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/14 00:07:45 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**re_split(char **token)
{
	int		i;
	char	**first_cmd;
	char	*tmp;

	first_cmd = ft_split_cmd(token[0]);
	if (!first_cmd)
		return (free_mat(token), NULL);
	if (get_size_mat(first_cmd) > 1)
	{
		if (get_size_mat(token) == 1)
			return (free_mat(token), free_mat(first_cmd), first_cmd);
		free(token[0]);
		(1) && (token[0] = first_cmd[0], tmp = ft_strdup(""), i = 0);
		while (first_cmd[++i])
			(1) && (tmp = ft_strjoin(tmp, first_cmd[i]),
				tmp = ft_strjoin(tmp, " "));
		tmp = ft_strjoin(tmp, token[1]);
		if (!tmp)
			return (free_mat(token), free_mat(first_cmd), NULL);
		free(token[1]);
		token[1] = tmp;
	}
	return (free_mat(first_cmd), token);
}

static int	count_empty_str(char **token)
{
	int		i;
	int		nbempty_str;

	i = -1;
	nbempty_str = 0;
	while (token[++i])
	{
		if (!*token[i])
			nbempty_str++;
	}
	return (nbempty_str);
}

static char	**skip_empty_strs(char **token)
{
	int		i;
	char	**new_token;
	char	*tmp;
	int		j;

	if (!count_empty_str(token))
		return (token);
	new_token = malloc(sizeof(char *) * (get_size_mat(token)
				- count_empty_str(token) + 1));
	if (!new_token)
		return (free_mat(token), NULL);
	(1) && (i = -1, j = -1);
	while (token[++i])
	{
		if (*token[i])
		{
			tmp = ft_strdup(token[i]);
			if (!tmp)
				return (free_mat(new_token), free_mat(token), NULL);
			new_token[++j] = tmp;
		}
	}
	new_token[++j] = NULL;
	return (free_mat(token), new_token);
}

char	**ft_token_cmds(char *cmds, char **env, int exit_status)
{
	char	**token;
	char	**expand_strs;
	char	*tmp;

	token = ft_split_cmd(cmds);
	if (!token)
		return (NULL);
	if (!ft_add_skiper(token) || !ft_expand(token, 1, exit_status, env))
		return (free_mat(token), NULL);
	if (!token)
		return (NULL);
	token = re_split(token);
	if (!token)
		return (NULL);
	if (!ft_remove_quotes(token))
		return (free_mat(token), NULL);
	token = skip_empty_strs(token);
	if (!token)
		return (NULL);
	return (token);
}
