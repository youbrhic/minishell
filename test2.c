void    ft_dup(int i, int *pipes1, int *pipes2, int nb_cmd)
{
	if ((i % 2) && (i + 1 <= nb_cmd))
	{
		if (pipe(pipes1) < 0)
			perror("pipes1 : pipe ");
		if ((dup2(1, pipes1[1]) < 0) || (dup2(0, pipes1[0]) < 0))
			perror ("pipes2 : dup2");
		if (i - 1 != 0  && (dup2(0, pipes2[0]) < 0))
			perror ("pipes2 : dup2");
	}
	else if (!(i % 2) && (i + 1) <= nb_cmd)
	{
		if (pipe(pipes2) < 0)
			perror("pipes2 : pipe ");
		if ((dup2(1, pipes2[1]) < 0) || (dup2(0, pipes2[0]) < 0))
			perror ("pipes2 : dup2");
		if (i - 1 != 0 && (dup2(0, pipes1[0]) < 0))
			perror ("pipes2 : dup2");
	}
	else 
	{
		if (i % 2 && (dup2(0, pipes2[0]) < 0))
			perror ("last one pipes2");
		else if ((!(i % 2) && (dup2(0, pipes1[0]) < 0)))
			perror ("last one pipes1");
	}
}

void    ft_dup_child(int i, int *pipes1, int *pipes2, int nb_cmd)
{
	if ((i % 2) && (i + 1 <= nb_cmd))
	{
		if (pipe(pipes1) < 0)
			perror("pipes1 : pipe child ");
		if ((dup2(pipes1[1], 1) < 0) || (dup2(pipes2[0], 0) < 0))
			perror ("pipes2 : dup2 child");
		if (i - 1 != 0 && (dup2(pipes2[0], 0) < 0))
			perror ("pipes2 : dup2 child ");
	}
	else if (!(i % 2) && (i + 1) <= nb_cmd)
	{
		if (pipe(pipes2) < 0)
			perror("pipes2 : pipe child ");
		if ((dup2(pipes2[1], 1) < 0) || (dup2(pipes2[0], 0) < 0))
			perror ("pipes2 : dup2 child ");
		if (i - 1 != 0 && close(pipes1[1]) < 0 && (dup2(pipes1[0], 0) < 0))
			perror ("pipes2 : dup2 child ");
	}
	else 
	{
		if (i % 2 && (close(pipes2[1] < 0) && dup2(pipes2[0], 0) < 0))
			perror ("last one pipes2 child");
		else if (((i % 2 == 0) && (dup2(pipes1[0], 0) < 0)))
			perror ("last one pipes1 child");
	}
}

