/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/07 18:31:38 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	internal_error(char *arg, char *arg2)
{
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(arg2, STDERR_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	char	*command;

	// pid_t	pid;
	(void)argc;
	command = search_for_command(*(argv + 1), env);
	if (!command)
	{
		internal_error(*(argv + 1), ": command not found");
		return (EX_NOTFOUND);
	}
	return (shell_execve(command, argv + 1, env));
}
