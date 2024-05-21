/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:32:46 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/18 02:14:57 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (key[0] != '_' && !ft_isalpha(key[0]))
	{
		write(2, "minishell: export:", 18);
		write(2, key, ft_strlen(key));
		write(2, ": not a valid identifier \n", 27);
		return (1);
	}
	while (key[i])
	{
		if (!is_alphanum(key[i]) && key[i] != '_')
		{
			write(2, "minishell: export:", 18);
			write(2, key, ft_strlen(key));
			write(2, ": not a valid identifier \n", 27);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_arg(char *arg)
{
	char	*key;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=' && (i - 1 >= 0) && arg[i - 1] == '+')
		i--;
	key = ft_strndup(arg, i);
	if (!key)
		return (1);
	if (check_key(key))
		return (free(key), 1);
	free(key);
	return (0);
}
