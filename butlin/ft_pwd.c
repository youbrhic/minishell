/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:23:03 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/28 04:02:07 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **args)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("Error");
		return (1);
	}
	if (args[1] && (args[1][0] == '-' && args[1][1]))
	{
		printf("Error: no option\n");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
