/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:37:43 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/27 22:26:34 by  ctokoyod        ###   ########.fr       */
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
# include <sys/wait.h>

// to Libft
# include "../Libft/libft.h"

// errors msg
# define ERR_INVALID "Invalid number of arguments\n"
# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_PIPE "pipe"
# define ERR_EXECVE "execve"
# define ERR_CMD "Error : Command not found\n"
# define ERR_DIR "Error : No such file of directory\n"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		tube[2];
	char	**split_path_array;
	char	**cmd_args;
	char	*cmd_fullpath;
}			t_pipex;

/* childs */
char		**find_path_from_env(char *envp[]);
char		*get_cmd_execution_path(char **paths_list, char *cmd);
void		execute_first_command(t_pipex pipex, char *argv[], char *envp[]);
void		execute_second_command(t_pipex pipex, char *argv[], char *envp[]);

/* free */
void		free_parent(t_pipex *pipex);
void		free_child(t_pipex *pipex);
/* error */
void	put_error_msg(const char *msg, int is_manual);
void	put_error_file(t_pipex *pipex);

#endif