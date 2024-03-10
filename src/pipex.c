/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 18:10:23 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char	**args;
	char	*command;
	int		status;
	int		arg_index;
	pid_t	pid;

	if (argc < 2)
		return (EXIT_SUCCESS);
	arg_index = 1;
	while (arg_index < argc)
	{
		pid = fork();
		if (pid == 0)
		{
			args = ft_split(*(argv + arg_index), ' ');
			if (!args)
				return (EXIT_FAILURE);
			command = search_for_command(*args, env);
			if (!command)
			{
				internal_error(*(argv + arg_index), ": command not found");
				return (EX_NOTFOUND);
			}
			return (shell_execve(command, args, env));
		}
		else if (pid < 0)
			return (EXIT_FAILURE);
		wait(&status);
		arg_index++;
	}
	if (waitpid(pid, &status, 0) != pid)
		return (EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
}
