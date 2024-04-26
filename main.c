/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/26 20:30:48 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	affiche(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		printf ("cmd : %s \n", tmp->cmd);
		printf ("rederiction : %s \n", tmp->redirections);
		tmp = tmp->next;
		printf("------------------------\n");
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**token;
	t_node	*head;
	t_data	data;
	int		i;

	(void)ac;
	(void)av;
	(void)env;
	data.exit_state = 0;
	data.env = get_env(env);
	// i = -1;
	// while (data.env[++i])
	// 	printf ("%s \n", data.env[i]);
	while (1)
	{
		input = readline("minibash$ ");
		if (!input)
			exit(1);
		else
		{
			if (*input)
            	add_history(input);
			input = ft_add_space(input);
			if (!input)
				printf("minishell : syntax error unclosed quotes \n");
			else
			{
				token = ft_split_cmd(input);
				if (!token)
					printf ("error");
				else
				{
					if (ft_parse_line(token) != 258)
					{
						head = ft_get_nodes(token);
						if (!head)
							continue;
						//affiche(head);
						ft_exec_list(head, data.env);
						ft_lstclear(&head);
					}
					free_mat(&token);
				}
			}
			free(input);
		}
	}
	clear_history();
}
