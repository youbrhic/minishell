/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:23:54 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/20 02:25:49 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	help_norm(char const *s, int *i)
{
	char	quote;

	while (!is_space(s[*i]) && s[*i])
	{
		if (is_quot(s[*i]))
		{
			quote = s[*i];
			(*i)++;
			while (s[*i] && s[*i] != quote)
				(*i)++;
		}
		(*i)++;
	}
}

int	count_words(char const *s)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		if (s[i] != '\0')
			cnt++;
		help_norm(s, &i);
	}
	return (cnt);
}

int	is_quot(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
