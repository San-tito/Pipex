/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:15:47 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/12 17:42:28 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	internal_error(char *arg1, char *arg2)
{
	ft_putstr_fd(arg1, STDERR_FILENO);
	ft_putendl_fd(arg2, STDERR_FILENO);
}
