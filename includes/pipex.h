/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:06:35 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/24 20:39:30 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// write, read, fork, execve, pipe, access
# include <unistd.h>

// perror
# include <stdio.h>

// malloc, free, exit, exit
# include <stdlib.h>

// open
# include <fcntl.h>

// exit 関数　引数　
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int infile;  // openの返り値がint
	int outfile; // openの返り値がint
	int		tube[2];
	char *paths; // one line paths
	char	**cmd_paths_list;
	char	**cmd_args;
	char	*cmd_fullpath;
}			t_pipex;

/* ---srcs--- */
char		*find_path_from_env(char **envp);
void		error_msg(const char *msg);

#endif

// int access(const char *pathname, int how);