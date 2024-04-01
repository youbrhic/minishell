/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:14:01 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/14 22:08:23 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	help_norm1(char const *s, int *i)
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

static char const	*help_norm2(char const *s)
{
	char		quote;
	char const	*tmp;

	tmp = s;
	while (*tmp && !is_space(*tmp))
	{
		if (is_quot(*tmp))
		{
			quote = *tmp;
			tmp++;
			while (*tmp && *tmp != quote)
				tmp++;
		}
		tmp++;
	}
	return (tmp);
}

static char	**free2d(char **arr, int index)
{
	int	i;

	i = 0;
	while (index - i >= 0)
	{
		free(arr[index - i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split_cmd(char const *s)
{
	int		i;
	int		index;
	int		tail_token;
	char	**arr;

	tail_token = count_words(s);
	index = -1;
	arr = (char **)malloc((sizeof(char *)) * (tail_token + 1));
	if (!arr || !s)
		return (NULL);
	while (++index < tail_token)
	{
		i = 0;
		while (*s && is_space(*s))
			s++;
		help_norm1(s, &i);
		arr[index] = ft_strndup(s, i);
		if (arr[index] == NULL)
			return (free2d(arr, index));
		s = help_norm2(s);
	}
	return (arr[index] = NULL, arr);
}
