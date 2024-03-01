/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:37:43 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/29 14:48:43 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

// write, read, fork, execve, pipe, access
# include <unistd.h>

// perror
# include <stdio.h>

// malloc, free, exit, exit
# include <stdlib.h>

// open
# include <fcntl.h>

// waitpid, wait
# include <sys/wait.h>

// to Libft
# include "../Libft/libft.h"

// exit
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

// errors msg
# define ERR_INVALID "Invalid number of arguments"
# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_PIPE "pipe"
# define ERR_EXECVE "execve"
#define ERR_DUP2 "dup2 "
# define ERR_CMD "Error : command not found"
# define ERR_DIR "Error : No such file of directory"

typedef struct s_pipex
{
	pid_t	pid;
	int		infile;
	int		outfile[2];
	int		pipe_fd[2][2];
	int		current_pipe;
	int		next_pipe;
	char	**split_path_array;
	char	**cmd_args;
	char	*cmd_fullpath;
}			t_pipex;

#endif