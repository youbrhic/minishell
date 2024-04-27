/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:43:47 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/19 20:00:51 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *cmd)
{
	int	i;
	int	no_nl;

	i = 0;
	no_nl = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			i++;
		while (cmd[i] && cmd[i] != ' ')
		{
			if (cmd[i] == '-' && cmd[i + 1] == 'n')
			{
				i += 2;
				no_nl = 1;
			}
			else if (cmd[i] == '\"')
				i++;
			else
				printf("%c", cmd[i++]);
		}
		if (cmd[i - 2] != '-' && cmd[i - 1] != 'n' && cmd[i])
			printf(" ");
	}
	if (!no_nl)
		printf("\n");
}

void	ft_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

void	ft_cd(char *path)
{
	int	ret;

	if (path[0] == '\0')
	{
		chdir(getenv("HOME"));
		return ;
	}
	if (path[0] == ' ')
		path++;
	else if (path[0] == '~')
		path = ft_strjoin(getenv("HOME"), path + 1);
	else if (path[0] == '-')
		path = ft_strjoin(getenv("OLDPWD"), path + 1);
	ret = chdir(path);
	if (ret < 0)
	{
		perror("Error");
		return ;
	}
}
