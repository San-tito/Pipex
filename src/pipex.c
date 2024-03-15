/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/15 20:48:23 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_dispatcher(t_job j, t_process *p, int write_end)
{
	char	*line;

	if (j.is_here_doc)
	{
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			if (!ft_strncmp(line, j.limiter, ft_strlen(j.limiter)))
				break ;
			ft_putstr_fd(line, write_end);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		close(write_end);
		(*p).infile = STDIN_FILENO;
	}
	else
		(*p).infile = j.stdin;
}

void	launch_job(t_job j, char **env)
{
	t_process	*p;
	int			fd[2];

	p = j.first_process;
	while (p)
	{
		(*p).infile = *fd;
		if (pipe(fd))
			exit(EXIT_FAILURE);
		if (p == j.first_process)
			input_dispatcher(j, p, *(fd + 1));
		(*p).outfile = j.stdout;
		if ((*p).next)
			(*p).outfile = *(fd + 1);
		(*p).pid = fork();
		if ((*p).pid == 0)
			launch_process(p, env);
		else if ((*p).pid < 0)
			exit(EXIT_FAILURE);
		close((*p).infile);
		close((*p).outfile);
		p = (*p).next;
	}
	proc_waitpid(j.first_process);
}

void	create_job(int ac, char **av, t_job *job)
{
	char	**argv;
	int		flags;
	int		arg_index;

	arg_index = 1;
	if ((*job).is_here_doc)
		arg_index++;
	while (++arg_index < ac - 1)
	{
		argv = ft_split(*(av + arg_index), ' ');
		if (!argv)
			return (cleanup_processes(&(*job).first_process),
				exit(EXIT_FAILURE));
		proc_add(&(*job).first_process, argv);
	}
	if (!(*job).is_here_doc)
		(*job).stdin = open(*(av + 1), O_RDONLY);
	if ((*job).stdin < 0)
		perror(*(av + 1));
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if ((*job).is_here_doc)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	(*job).stdout = open(*(av + arg_index), flags, 0644);
	if ((*job).stdout < 0)
		perror(*(av + arg_index));
}

int	main(int argc, char **argv, char **env)
{
	t_job	job;

	job = (t_job){};
	if (argc < 5)
		return (ft_putstr_fd("Usage: ", STDERR_FILENO), internal_error(*argv,
				" file1 cmd1 cmd2 ... cmdn file2", EXIT_FAILURE));
	job.is_here_doc = ft_strncmp(*(argv + 1), "here_doc", 9) == 0;
	if (argc < 6 && job.is_here_doc)
		return (ft_putstr_fd("Usage: ", STDERR_FILENO), internal_error(*argv,
				" here_doc LIMITER cmd cmd1 ... cmdn file", EXIT_FAILURE));
	if (job.is_here_doc)
		job.limiter = *(argv + 2);
	create_job(argc, argv, &job);
	launch_job(job, env);
}
