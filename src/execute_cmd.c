/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:51:52 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/22 19:42:31 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	shell_execve(char *command, char **args, char **env)
{
	int	errnum;
	int	last_command_exit_value;

	execve(command, args, env);
	errnum = errno;
	if (errnum != ENOEXEC)
	{
		perror(command);
		last_command_exit_value = EX_NOEXEC;
		if (errnum == ENOENT)
			last_command_exit_value = EX_NOTFOUND;
	}
	return (last_command_exit_value);
}
