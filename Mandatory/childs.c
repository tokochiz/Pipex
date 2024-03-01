/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:54:54 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/01 16:27:59 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_cmd_execution_path(char **split_path_array, char *cmd)
{
	char	*path_with_slash;
	char	*cmd_fullpath;

	if (ft_strchr(&cmd[0], '/') != 0)
	{
		if (access(&cmd[0], X_OK) == 0)
			return (&cmd[0]);
		else
			put_error_after_exit(ERR_DIR, 1);
	}
	if(*split_path_array == NULL)
		perror(ERR_DIR);
	while (*split_path_array)
	{
		path_with_slash = ft_strjoin(*split_path_array, "/");
		cmd_fullpath = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (access(cmd_fullpath, X_OK) == 0)
			return (cmd_fullpath);
		free(cmd_fullpath);
		split_path_array++;
	}
	return (NULL);
}

void	execute_first_command(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[1], STDOUT_FILENO);
	close(pipex.tube[0]);
	dup2(pipex.infile, STDIN_FILENO);
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (pipex.cmd_args == NULL || pipex.cmd_args[0] == NULL
		|| *(pipex.cmd_args[0]) == '\0')
	{
		free_child(&pipex);
		put_error_after_exit(ERR_CMD, 1);
	}
	pipex.cmd_fullpath = get_cmd_execution_path(pipex.split_path_array,
			pipex.cmd_args[0]);
	if (pipex.cmd_fullpath == NULL)
	{
		free_child(&pipex);
		put_error_after_exit(ERR_CMD, 1);
	}
	if (execve(pipex.cmd_fullpath, pipex.cmd_args, envp) == -1)
		put_error_after_exit(ERR_EXECVE, 0);
}

void	execute_second_command(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[0], STDIN_FILENO);
	close(pipex.tube[1]);
	dup2(pipex.outfile, STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (pipex.cmd_args == NULL || pipex.cmd_args[0] == NULL
		|| *(pipex.cmd_args[0]) == '\0')
	{
		free_child(&pipex);
		put_error_after_exit(ERR_CMD, 1);
	}
	pipex.cmd_fullpath = get_cmd_execution_path(pipex.split_path_array,
			pipex.cmd_args[0]);
	if (pipex.cmd_fullpath == NULL)
	{
		free_child(&pipex);
		put_error_after_exit(ERR_CMD, 1);
	}
	if (execve(pipex.cmd_fullpath, pipex.cmd_args, envp) == -1)
		put_error_after_exit(ERR_EXECVE, 0);
}
