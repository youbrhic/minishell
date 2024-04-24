/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hardoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 02:15:06 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/24 03:20:31 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **malloc_matr1(char *str)
{
    char    **matr;

    matr = malloc(sizeof(char *) * 2);
    if (!matr)
      ft_perror("malloc", -1);
    matr[0] = ft_strndup(str, ft_strlen(str));
	matr[1] = NULL;
	return (matr);
}

void    ft_hardoc(char *limiter)
{
    char    *input;
    int     fd;
    char    **matr;

    if (!ft_strcmp(limiter, "hardoc"))
        unlink("/tmp/hardoc");
    fd = open("/tmp/hardoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    while (1)
    {
        input = readline(">");
        if (!input || !ft_strcmp(input, limiter))
            break ;
		matr = malloc_matr1(input);
		expand(matr, 0);
        write(fd, matr[0], ft_strlen(matr[0]));
        write(fd, "\n", 1);
        free(input);
		free_mat(&matr);
    }
    close(fd);
}
