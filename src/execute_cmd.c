/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:51:52 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/22 17:19:28 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	shell_execve(char *command, char **args, char **env)
{
	int i, last_command_exit_value;
	execve(command, args, env);
	i = errno;
	if (i != ENOEXEC)
	{
		last_command_exit_value = (i == ENOENT) ? EX_NOTFOUND : EX_NOEXEC;
	}
	return (last_command_exit_value);
}
