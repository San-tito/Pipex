/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/11 20:42:30 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	launch_job(t_job j, char **env)
{
	t_process	*p;
	int			status;
	pid_t		pid;
	int			fd[2];
	int			infile;
	int			outfile;

	infile = j.stdin;
	p = j.process;
	while (p)
	{
		if ((*p).next)
		{
			if (pipe(fd))
				exit(EXIT_FAILURE);
			outfile = *(fd + 1);
		}
		else
			outfile = j.stdout;
		pid = fork();
		if (pid == 0)
			launch_process(p, env, infile, outfile);
		else if (pid < 0)
			exit(EXIT_FAILURE);
		else
		{
			if (waitpid(pid, &status, WAIT_MYPGRP) != pid)
				exit(EXIT_FAILURE);
		}
		if (infile != j.stdin)
			close(infile);
		if (outfile != j.stdout)
			close(outfile);
		infile = *fd;
		p = (*p).next;
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	t_job	job;
	char	**args;
	int		arg_index;

	if (argc < 5)
		return (EXIT_SUCCESS);
	job = (t_job){};
	arg_index = 1;
	while (++arg_index < argc - 1)
	{
		args = ft_split(*(argv + arg_index), ' ');
		if (!args)
			return (EXIT_FAILURE);
		proc_add(&job.process, args);
	}
	job.stdin = open(*(argv + 1), O_RDONLY);
	if (job.stdin == -1)
		return (EXIT_FAILURE);
	job.stdout = open(*(argv + arg_index), O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (job.stdout == -1)
		return (EXIT_FAILURE);
	launch_job(job, env);
}
