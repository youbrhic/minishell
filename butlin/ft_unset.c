/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:23:24 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/28 14:17:52 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **args, char ***env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!args[1])
		return (0);
	if (args[1][0] == '-' && args[1][1])
	{
		printf("Error: no option\n");
		return (2);
	}
	while (args[++i])
	{
		j = -1;
		len = ft_strlen(args[i]);
		while ((*env)[++j])
		{
			if (!ft_strncmp(args[i], (*env)[j], len) && (*env)[j][len] == '=')
			{
				while ((*env)[j])
				{
					(*env)[j] = (*env)[j + 1];
					j++;
				}
				(*env)[j] = NULL;
				break ;
			}
		}
	}
	return (0);
}
