/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/13 23:08:03 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (WEXITSTATUS(status));
}

void	launch_job(t_job j, char **env)
{
	t_process	*p;
	int			status;
	pid_t		pid;
	int			fd[2];
	int			infile;
	int			outfile;

	infile = j.stdin;
	p = j.first_process;
	while (p)
	{
		if (pipe(fd))
			exit(EXIT_FAILURE);
		outfile = j.stdout;
		if ((*p).next)
			outfile = *(fd + 1);
		pid = fork();
		if (pid == 0)
			launch_process(p, env, infile, outfile);
		else if (pid < 0)
			exit(EXIT_FAILURE);
		if (infile != j.stdin)
			close(infile);
		if (outfile != j.stdout)
			close(outfile);
		infile = *fd;
		p = (*p).next;
	}
	if (waitpid(pid, &status, 0) != pid)
		exit(EXIT_FAILURE);
	exit(process_exit_status(status));
}

int	main(int argc, char **argv, char **env)
{
	t_job	job;
	char	**args;
	int		arg_index;

	if (argc < 5)
		return (ft_putstr_fd("Usage: ", STDERR_FILENO), internal_error(*argv,
				" file1 cmd1 cmd2 ... cmdn file2", EXIT_FAILURE));
	job = (t_job){};
	arg_index = 1;
	while (++arg_index < argc - 1)
	{
		args = ft_split(*(argv + arg_index), ' ');
		if (!args)
			return (EXIT_FAILURE);
		proc_add(&job.first_process, args);
	}
	job.stdin = open(*(argv + 1), O_RDONLY);
	if (job.stdin < 0)
		perror(*(argv + 1));
	job.stdout = open(*(argv + arg_index), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (job.stdout < 0)
		perror(*(argv + arg_index));
	launch_job(job, env);
}
