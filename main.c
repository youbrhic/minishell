/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/20 03:00:54 by youbrhic         ###   ########.fr       */
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

// void f()
// {
// 	system ("leaks minishell");
// }

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**token;
	t_node	*head;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		input = readline("minibash$ ");
		if (!input)
			exit(1);
		else
		{
			if (*input)
            	add_history(input);
			input = add_space(input);
			if (!input)
				printf("syntaxe error : quote not close (\" or \')\n");
			else
			{
				token = ft_split_cmd(input);
				if (!token)
					printf ("error");
				else
				{
					expand(token);
					if (parse_line(token) > 0)
					{
						head = get_nodes(token);
						if (!head)
						{
							printf ("it's her \n");
							exit(-1);
						}
						affiche(head);
						//exec_list(head, env);
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
