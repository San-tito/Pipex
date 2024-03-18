/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/18 16:11:50 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_here_document(int *redirect, char *limiter)
{
	char		*line;
	int			fd[2];
	const char	*filename = "/tmp/pipex.XXXXXX";

	*(fd + 1) = open(filename, O_CREAT | O_WRONLY | O_EXCL, 0600);
	if (*(fd + 1) < 0)
		(perror(filename));
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		(perror(filename));
	unlink(filename);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, *(fd + 1));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(*(fd + 1));
	*redirect = *fd;
}

void	launch_job(t_job *j, char **env)
{
	t_process	*p;
	int			fd[2];

	p = (*j).process;
	while (p)
	{
		(*p).infile = *fd;
		if (p == (*j).process)
			(*p).infile = (*j).stdin;
		if (pipe(fd))
			return (cleanup_processes(&(*j).process), exit(EXIT_FAILURE));
		(*p).outfile = (*j).stdout;
		if ((*p).next)
			(*p).outfile = *(fd + 1);
		(*p).pid = fork();
		if ((*p).pid == 0)
			launch_process(j, p, env);
		else if ((*p).pid < 0)
			return (cleanup_processes(&(*j).process), exit(EXIT_FAILURE));
		close((*p).infile);
		close((*p).outfile);
		p = (*p).next;
	}
	exit(proc_waitpid((*j).process));
}

void	create_job(int ac, char **av, t_job *job, int is_here_doc)
{
	char	**argv;
	int		flags;
	int		arg_index;

	arg_index = 1;
	if (is_here_doc)
		arg_index++;
	while (++arg_index < ac - 1)
	{
		argv = ft_split(*(av + arg_index), ' ');
		if (!argv)
			return (cleanup_processes(&(*job).process), exit(EXIT_FAILURE));
		proc_add(&(*job).process, argv);
	}
	if (!is_here_doc)
		(*job).stdin = open(*(av + 1), O_RDONLY);
	if ((*job).stdin < 0)
		perror(*(av + 1));
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (is_here_doc)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	(*job).stdout = open(*(av + arg_index), flags, 0644);
	if ((*job).stdout < 0)
		perror(*(av + arg_index));
}

int	main(int argc, char **argv, char **env)
{
	t_job	job;
	int		is_here_doc;

	job = (t_job){};
	if (argc < 5)
		return (ft_putstr_fd("Usage: ", STDERR_FILENO), internal_error(*argv,
				" file1 cmd1 cmd2 ... cmdn file2", EXIT_FAILURE));
	is_here_doc = ft_strncmp(*(argv + 1), "here_doc", 9) == 0;
	if (argc < 6 && is_here_doc)
		return (ft_putstr_fd("Usage: ", STDERR_FILENO), internal_error(*argv,
				" here_doc LIMITER cmd cmd1 ... cmdn file", EXIT_FAILURE));
	if (is_here_doc)
		make_here_document(&job.stdin, *(argv + 2));
	create_job(argc, argv, &job, is_here_doc);
	launch_job(&job, env);
}
