/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:02:24 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/20 04:33:26 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_pipe_redirection(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static void	help_norm1(int *count, char *str, int *i)
{
	char	c;

	if (is_pipe_redirection(str[*i]) && !is_pipe_redirection(str[*i + 1]))
		(*count)++;
	else if (is_pipe_redirection(str[*i]) && is_pipe_redirection(str[*i + 1])
		&& str[*i] == str[*i + 1] && str[*i] != '|')
	{
		(*count)++;
		(*i)++;
	}
	else if (str[*i] == '\"' || str[*i] == '\'')
	{
		c = str[*i];
		(*i)++;
		while (str[*i] != c && str[*i])
			(*i)++;
		if (!str[*i])
		{
			write(2, "minishell: syntax error \n", 25);
			*i = -1;
		}
	}
}

static int	count_pipe_rederection(char *str)
{
	int		count;
	int		i;

	if (!str)
		return (0);
	count = 0;
	i = -1;
	while (str[++i])
	{
		help_norm1(&count, str, &i);
		if (i == -1)
			return (-1);
		if (is_pipe_redirection(str[i])
			&& is_pipe_redirection(str[i + 1]))
			count += 2;
	}
	return (count);
}

static int	help_norm2(char *input, char *new_input, int *size, int *i)
{
	int		n;
	char	c;

	n = *i + 1;
	if (is_pipe_redirection(input[*size])
		&&is_pipe_redirection(input[*size + 1])
		&& input[*size] == input[*size + 1] && input[*size] != '|')
	{
		new_input[(*i)++] = ' ';
		new_input[(*i)++] = input[*size];
		(*size)++;
	}
	else if (is_pipe_redirection(input[*size]))
		new_input[(*i)++] = ' ';
	else if (input[*size] == '\"' || input[*size] == '\'')
	{
		c = input[*size];
		new_input[(*i)++] = input[(*size)++];
		while (input[*size] && c != input[*size])
			new_input[(*i)++] = input[(*size)++];
		n = -1;
	}
	return (n);
}

char	*ft_add_space(char *input)
{
	char	*new_input;
	int		size;
	int		i;
	int		n;

	size = count_pipe_rederection(input);
	if (size < 0)
		return (free(input), NULL);
	new_input = malloc((2 * size) + ft_strlen(input) + 2);
	if (!new_input)
		return (free(input), input = NULL);
	size = -1;
	i = 0;
	while (input[++size])
	{
		n = help_norm2(input, new_input, &size, &i);
		new_input[i++] = input[size];
		if (n != i && n != -1)
			new_input[i++] = ' ';
	}
	new_input[i] = '\0';
	return (free(input), input = NULL, new_input);
}
