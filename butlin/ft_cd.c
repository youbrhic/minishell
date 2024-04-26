/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:21:27 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/24 09:07:54 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char **path)
{
	int		ret;

	if (!path[1] || !ft_strcmp(path[1], "~"))
		ret = chdir(getenv("HOME"));
	else if (!ft_strcmp(path[1], "-"))
		ret = chdir(getenv("OLDPWD"));
	else
		ret = chdir(path[1]);
	if (ret < 0)
	{
		perror("Error");
		return ;
	}
}
