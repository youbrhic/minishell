/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:09:14 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/20 11:26:11 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_expand(char *str, int i, int flag)
{
	if (flag)
	{
		return ((i + 1 < ft_strlen(str) && (is_alphanum(str[i + 1])
					|| str[i + 1] == '?' || str[i + 1] == '_')));
	}
	else
		return ((i + 1 < ft_strlen(str)
				&& str[i] == '\\' && str[i + 1] == '\''));
	return (0);
}

static int	get_index_dollar(char *str, int flag)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (check_expand(str, i, 0) && flag)
			while (str[++i] && !check_expand(str, i, 0))
				;
		else if (str[i] == '$' && check_expand(str, i, 1))
			return (i);
	}
	return (-1);
}

static char	*get_str_env(char *str, int *index_d, char **env, int exit_status)
{
	char	*str_env;
	char	*tmp;
	int		i;
	int		size;

	i = *index_d;
	size = 0;
	while (str[++i] && (is_alphanum(str[i]) || str[i] == '_'))
		size++;
	if (str[i] == '?' && i == *index_d + 1)
		return (((*index_d) += 2), ft_itoa(exit_status));
	else if (str[i])
		size--;
	tmp = ft_strndup(&str[*index_d + 1], size + 1);
	if (!tmp)
		return (NULL);
	str_env = ft_getenv(tmp, env);
	if (!str_env)
		str_env = "";
	return (free(tmp), (*index_d = i), ft_strdup(str_env));
}

static char	*ft_str_expand(char *str, int index_d, char **env, int exit_status)
{
	char	*tmp;
	char	*new_str;

	new_str = ft_strndup(str, index_d);
	if (!new_str)
		return (NULL);
	tmp = get_str_env(str, &index_d, env, exit_status);
	if (!tmp)
		return (free(new_str), NULL);
	new_str = ft_strjoin(new_str, tmp);
	if (!new_str)
		return (free(tmp), NULL);
	free(tmp);
	tmp = ft_strdup(&str[index_d]);
	if (!tmp)
		return (free(new_str), NULL);
	new_str = ft_strjoin(new_str, tmp);
	return (free(tmp), new_str);
}

int	ft_expand(char **token, int flag, int exit_status, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (token[++i])
	{
		if (get_index_dollar(token[i], flag) >= 0
			&& !(i > 0 && !ft_strcmp(token[i - 1], "<<")))
		{
			tmp = ft_str_expand(token[i],
					get_index_dollar(token[i], flag), env, exit_status);
			if (!tmp)
				return (0);
			free(token[i]);
			token[i] = tmp;
			i--;
		}
	}
	return (1);
}
