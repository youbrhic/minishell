/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hardoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 02:15:06 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/13 01:37:41 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**malloc_matr1(char *str, int flag)
{
	char	**matr;

	matr = malloc(sizeof(char *) * 2);
	if (!matr)
		return (NULL);
	matr[0] = ft_strndup(str, ft_strlen(str));
	if (!matr[0])
		return (NULL);
	matr[1] = NULL;
	if (flag)
		free (str);
	return (matr);
}

static void	ft_print_fd(int fd, char *str)
{
	if (fd < 0)
		return ;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	ft_hardoc(char *limiter)
{
	int		fd;
	char	*input;
	char	**matr;

	if (!ft_strcmp(limiter, "hardoc"))
		unlink("/tmp/hardoc");
	fd = open("/tmp/hardoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (1)
	{
		input = readline(">");
		if (!input || !ft_strcmp(input, limiter))
			return ;
		matr = malloc_matr1(input, 1);
		if (!matr)
			return ;
		ft_print_fd(fd, matr[0]);
		free_mat(matr);
	}
	close(fd);
}
