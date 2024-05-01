/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/05/01 01:50:32 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s1, int n)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)malloc(n + 1);
	if (new == NULL)
		return (NULL);
	while (s1[i] && i < n)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strlen(char *c)
{
	int	i;

	if (!c)
		return (0);
	i = 0;
	while (c[i])
		i++;
	return (i);
}

void	free_mat(char **mtr)
{
	int		i;

	i = 0;
	while (mtr[i])
	{
		free(mtr[i]);
		i++;
	}
	free(mtr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		++i;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		++i;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strexsit(char *s, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == str[j])
		{
			while (s[i] == str[j] && str[j])
			{
				i++;
				j++;
			}
			if (!str[j])
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_alphanum(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)malloc(ft_strlen((char *)s1) + 1);
	if (new == NULL)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
