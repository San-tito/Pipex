/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:25:41 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/12 19:49:58 by sguzman          ###   ########.fr       */
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

void	cleanup_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (*(matrix + i))
		free(*(matrix + i++));
	free(matrix);
}

void	cleanup_processes(t_process **p)
{
	t_process	*proc;

	while (*p)
	{
		proc = (**p).next;
		cleanup_matrix((**p).argv);
		free(*p);
		*p = proc;
	}
}

void	launch_process(t_process *p, char **env, int infile, int outfile)
{
	char	*command;

	command = search_for_command(*(*p).argv, env);
	if (!command)
	{
		internal_error(*(*p).argv, ": command not found");
		exit(EX_NOTFOUND);
	}
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	exit(shell_execve(command, (*p).argv, env));
}
