/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/04 17:45:13 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	internal_error(char *format, char *arg)
{
	ft_putstr_fd(format, STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
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
	return (shell_execve(command, argv + 2, env));
}
