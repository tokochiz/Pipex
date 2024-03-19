/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:37:43 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/19 18:23:43 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERR_INVALID "Invalid number of arguments\n"
# define ERR_INFILE "infile "
# define ERR_OUTFILE "outfile "
# define ERR_PIPE "pipe "
# define ERR_EXECVE "execve "
# define ERR_DUP2 "dup2 "
# define ERR_CMD "Error : Command not found\n"
# define ERR_DIR "Error : No such file of directory\n"


typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		tube[2];
	char	**split_paths;
	char	**cmd_args;
	char	*cmd_fullpath;
}			t_pipex;

void		close_pipes(t_pipex *pipex);

char		**extract_path_from_env(char *envp[]);
char		*get_path(t_pipex pipex, char *envp[]);
char		*execute_command(t_pipex pipex, char *envp[]);
void		execute_first_command(t_pipex pipex, char *argv[], char *envp[]);
void		execute_second_command(t_pipex pipex, char *argv[], char *envp[]);

void		free_split(char **split_array);
void		free_parent(t_pipex *pipex);
void		free_child(t_pipex *pipex);

void		put_error_file(t_pipex pipex);
void	put_error_and_exit(const char *msg, int is_manual);

#endif