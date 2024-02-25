/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:06:35 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/25 14:56:35 by  ctokoyod        ###   ########.fr       */
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

// waitpid, wait
#include <sys/wait.h>

// to Libft
#include "../Libft/libft.h"

// exit 関数　引数　
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

// errors
# define ERR_INVALID_NUM_ARGS "Invalid number of arguments"
# define ERR_IN_FILE "err infile"
# define ERR_OUT_FILE "err outfile"
# define ERR_PIPE "err pipe"
#define ERR_CMD "err command not found"

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

/* ------------ srcs ------------ */
char		*find_path_from_env(char **envp);

// child
char		*get_cmd_execution_path(char **paths_list, char *cmd);
void		execute_first_command(t_pipex pipex, char **argv, char *envp[]);
void		execute_second_command(t_pipex pipex, char **argv, char *envp[]);

// error
void		put_error_msg(const char *msg);

// free
void		free_parent(t_pipex *pipex);
void		free_child(t_pipex *pipex);

#endif

// int access(const char *pathname, int how);
// pid_t waitpid(pid_t pid, int *status_ptr, int options);