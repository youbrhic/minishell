/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/23 05:42:27 by youbrhic         ###   ########.fr       */
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
		printf ("input : %d \n", tmp->input);
		printf ("output : %d \n", tmp->output);
		printf ("file / rederiction : %s \n", head->list_files_redirections);
		tmp = tmp->next;
		printf("------------------------\n");
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**matrice;
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
				matrice = ft_split_cmd(input);
				if (!matrice)
					printf ("error");
				else
				{
					if (parse_line(matrice) > 0)
					{
						head = get_nodes(matrice);
						if (!head)
						{
							printf ("it's her \n");
							exit(-1);
						}
						affiche(head);
						ft_lstclear(&head);
					}
					free_mat(&matrice);
				}
			}
			free(input);
		}
	}
	clear_history();
}
