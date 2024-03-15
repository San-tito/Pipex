/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:00:07 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/15 20:49:27 by sguzman          ###   ########.fr       */
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
	int					infile;
	int					outfile;
	pid_t				pid;
	struct s_process	*next;
}						t_process;

/* ************************************************************************** */
/*                        Definition of the Job Structure                     */
/* ************************************************************************** */
typedef struct s_job
{
	int					stdin;
	int					stdout;
	int					is_here_doc;
	char				*limiter;
	t_process			*first_process;
}						t_job;

/* ************************************************************************** */
/*                                Get Next Line                               */
/* ************************************************************************** */
char					*get_next_line(int fd);

/* ************************************************************************** */
/*                             Process functions                              */
/* ************************************************************************** */
void					proc_add(t_process **p, char **argv);
t_process				*proc_last(t_process *p);
int						process_exit_status(int status);
int						proc_waitpid(t_process *proc);
void					launch_process(t_process *p, char **env);

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
int						internal_error(char *arg1, char *arg2, int exit_code);

/* ************************************************************************** */
/*                                  Cleanup                                   */
/* ************************************************************************** */
void					cleanup_matrix(char **matrix);
void					cleanup_processes(t_process **p);

/* ************************************************************************** */
/*                              Special exit statuses                         */
/* ************************************************************************** */
# define EX_NOEXEC 126
# define EX_NOTFOUND 127

#endif
