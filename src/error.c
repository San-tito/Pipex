/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:15:47 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/14 13:25:19 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	internal_error(char *arg1, char *arg2, int exit_code)
{
	ft_putstr_fd(arg1, STDERR_FILENO);
	ft_putendl_fd(arg2, STDERR_FILENO);
	return (exit_code);
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
