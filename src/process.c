/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:25:41 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/18 16:11:53 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_process	*proc_last(t_process *p)
{
	t_process	*proc;

	if (!p)
		return (NULL);
	proc = p;
	while ((*proc).next)
		proc = (*proc).next;
	return (proc);
}

void	proc_add(t_process **p, char **argv)
{
	t_process	*last;
	t_process	*new;

	if (!p)
		return ;
	new = ft_calloc(sizeof(t_process), 1);
	if (!new)
		return ;
	(*new).argv = argv;
	(*new).next = NULL;
	if (!*p)
		*p = new;
	else
	{
		last = proc_last(*p);
		(*last).next = new;
	}
}

int	process_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (WEXITSTATUS(status));
}

int	proc_waitpid(t_process *proc)
{
	t_process	*p;
	int			status;

	p = proc;
	while (p)
	{
		if (waitpid((*p).pid, &status, WUNTRACED | WCONTINUED) != (*p).pid)
			return (cleanup_processes(&proc), EXIT_FAILURE);
		p = (*p).next;
	}
	return (cleanup_processes(&proc), process_exit_status(status));
}

void	launch_process(t_job *j, t_process *p, char **env)
{
	char	*command;
	int		infile;
	int		outfile;

	command = search_for_command(*(*p).argv, env);
	infile = (*p).infile;
	outfile = (*p).outfile;
	if (!command)
	{
		internal_error(*(*p).argv, ": command not found", EX_NOTFOUND);
		return (cleanup_processes(&(*j).process), exit(EX_NOTFOUND));
	}
	if (dup2(infile, STDIN_FILENO) < 0)
		return (cleanup_processes(&(*j).process), free(command),
			exit(EXIT_FAILURE));
	close(infile);
	if (dup2(outfile, STDOUT_FILENO) < 0)
		return (cleanup_processes(&(*j).process), free(command),
			exit(EXIT_FAILURE));
	close(outfile);
	exit(shell_execve(command, (*p).argv, env));
}
