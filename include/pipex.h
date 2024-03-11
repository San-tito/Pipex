/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:00:07 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/11 20:44:06 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

/* ************************************************************************** */
/*                        Definition of the Process  Structure                */
/* ************************************************************************** */
typedef struct s_process
{
	char				**argv;
	struct s_process	*next;
}						t_process;

/* ************************************************************************** */
/*                        Definition of the Job Structure                     */
/* ************************************************************************** */
typedef struct s_job
{
	t_process			*process;
	int					stdin;
	int					stdout;
}						t_job;

/* ************************************************************************** */
/*                             Process functions                              */
/* ************************************************************************** */
void					proc_add(t_process **p, char **argv);
void					launch_process(t_process *p, char **env, int infile,
							int outfile);

/* ************************************************************************** */
/*                                Search for command                          */
/* ************************************************************************** */
char					*search_for_command(char *pathname, char **env);

/* ************************************************************************** */
/*                                Execute a command                           */
/* ************************************************************************** */
int						shell_execve(char *command, char **args, char **env);

/* ************************************************************************** */
/*                                Report an error                             */
/* ************************************************************************** */
void					internal_error(char *arg1, char *arg2);

/* ************************************************************************** */
/*                              Special exit statuses                         */
/* ************************************************************************** */
# define EX_NOEXEC 126
# define EX_NOTFOUND 127

#endif
