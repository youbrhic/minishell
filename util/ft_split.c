/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:10:31 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/01 08:20:56 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words2(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			cnt++;
		while (s[i] != c && s[i])
			i++;
	}
	return (cnt);
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

char	**ft_split(char const *s, char c)
{
	int		i;
	int		index;
	int		tail_token;
	char	**arr;

	tail_token = count_words2(s, c);
	index = -1;
	arr = (char **)malloc((sizeof(char *)) * (tail_token + 1));
	if (!arr || !s)
		return (NULL);
	while (++index < tail_token)
	{
		i = 0;
		while (*s && *s == c)
			s++;
		while (*(s + i) != c && *(s + i))
			i++;
		arr[index] = ft_strndup(s, i);
		if (arr[index] == NULL)
			return (free2d(arr, index));
		while (*s && *s != c)
			s++;
	}
	arr[index] = NULL;
	return (arr);
}