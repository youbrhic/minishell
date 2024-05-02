/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/02 01:06:09 by aait-bab         ###   ########.fr       */
=======
/*   Updated: 2024/05/02 05:30:58 by youbrhic         ###   ########.fr       */
>>>>>>> 5e264bec34545c0e8b66ebb4f41ac087ac11752a
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
	int		exit_status;
	char	**copy_env;
	t_node	*head;

	(void)ac;
	(void)av;
<<<<<<< HEAD
	(1) && (exit_status = 0, new_env = get_matr_copy(env));
=======
	(1) && (exit_status = 0, copy_env = get_matr_copy(env));
>>>>>>> 5e264bec34545c0e8b66ebb4f41ac087ac11752a
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
			exit(1);
		if (*input)
			add_history(input);
		head = ft_create_list(input, &exit_status);
		if (!head)
			free(input);
		else
		{
			//affiche(head);
<<<<<<< HEAD
			exit_status = ft_execv_cmd(head, &env, exit_status);
=======
			exit_status = ft_execv_cmd(head, &copy_env, exit_status);
>>>>>>> 5e264bec34545c0e8b66ebb4f41ac087ac11752a
			ft_lstclear(&head);
			free(input);
		}
	}
	clear_history();
}
