/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:26:27 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/20 05:48:43 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_wait(int pid)
{
	int		status;

	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (WEXITSTATUS(status));
}

char	*get_file_hardoc(void)
{
	char	*tmp;
	int		i;
	char	*nb;

	(1) && (i = 0, tmp = ft_strdup("/tmp/hardoc"));
	if (!tmp)
		return (NULL);
	while (++i && !access(tmp, F_OK))
	{
		if (i > 1)
		{
			free (tmp);
			tmp = ft_strdup("/tmp/hardoc");
			if (!tmp)
				return (NULL);
		}
		nb = ft_itoa(i);
		if (!nb)
			return (NULL);
		tmp = ft_strjoin(tmp, nb);
		if (!tmp)
			return (free(nb), NULL);
		free(nb);
	}
	return (tmp);
}

static char	*expand_remove_str(char *str, char **env, int exit_status, int flag)
{
	char	**matr;
	char	*tmp;

	if (!str)
		return (NULL);
	matr = malloc(sizeof(char *) * 2);
	if (!matr)
		return (str);
	matr[0] = ft_strdup(str);
	if (!matr[0])
		return (free_mat(matr), str);
	matr[1] = NULL;
	if (flag == 1)
	{
		if (!ft_expand(matr, 0, exit_status, env))
			return (free_mat(matr), str);
	}
	else if (flag == 2)
		if (!ft_add_skiper(matr) || !ft_remove_quotes(matr))
			return (free_mat(matr), str);
	tmp = ft_strdup(matr[0]);
	if (!tmp)
		return (str);
	return (free(str), free_mat(matr), tmp);
}

void	write_hardoc(char *file, char *limiter, char **env, int exit_status)
{
	char	*input;
	int		flag;
	char	*new_limter;
	int		fd;

	flag = 1;
	fd = open(file, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return ;
	if (quotes_in_str(limiter) >= 0)
		(1) && (flag = 1,
			new_limter = expand_remove_str(limiter, env, exit_status, 2));
	while (1)
	{
		input = readline(">");
		input = expand_remove_str(input, env, exit_status, flag);
		if (!input || !ft_strcmp(input, limiter))
		{
			if (input)
				free(input);
			exit(0);
		}
		write_fd(fd, input);
	}
}
