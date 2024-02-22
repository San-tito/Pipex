/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/02/22 17:16:07 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;

	if (argc < 5)
		return (EXIT_SUCCESS);
	shell_execve(argv[0], argv + 1, env);
	return (EXIT_SUCCESS);
}
