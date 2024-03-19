/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:24:26 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/19 18:24:56 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**extract_path_from_env(char *envp[])
{
	char	*path_str;
	char	**paths;

	path_str = NULL;
	if (envp == NULL)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			path_str = *envp + 5;
			break ;
		}
		envp++;
	}
	if (path_str == NULL)
		put_error_and_exit(ERR_CMD, 1);
	paths = ft_split(path_str, ':');
	if (paths == NULL)
		put_error_and_exit(ERR_CMD, 1);
	return (paths);
}

char	*get_path(t_pipex pipex, char *envp[])
{
	char	*cmd_fullpath;

	pipex.split_paths = extract_path_from_env(envp);
	if (pipex.split_paths == NULL)
	{
		if (access(pipex.cmd_args[0], X_OK) == 0)
			return (pipex.cmd_args[0]);
		else
			put_error_and_exit(ERR_DIR, 1);
	}
	while (*pipex.split_paths)
	{
		cmd_fullpath = ft_strjoin(*pipex.split_paths, "/");
		cmd_fullpath = ft_strjoin(cmd_fullpath, pipex.cmd_args[0]);
		if (access(cmd_fullpath, X_OK) == 0)
			return (cmd_fullpath);
		free(cmd_fullpath);
		pipex.split_paths++;
	}
	free_split(pipex.split_paths);
	return (NULL);
}

char	*execute_command(t_pipex pipex, char *envp[])
{
	if (pipex.cmd_args == NULL || pipex.cmd_args[0] == NULL
		|| *(pipex.cmd_args[0]) == '\0')
	{
		free_child(&pipex);
		put_error_and_exit(ERR_CMD, 1);
	}
	if (ft_strchr(pipex.cmd_args[0], '/') != 0)
	{
		if (access(pipex.cmd_args[0], X_OK) == 0)
		{
			if (execve(pipex.cmd_args[0], pipex.cmd_args, envp) == -1)
				put_error_and_exit(ERR_EXECVE, 0);
		}
		else
			put_error_and_exit(ERR_DIR, 1);
	}
	pipex.cmd_fullpath = get_path(pipex, envp);
	if (pipex.cmd_fullpath == NULL)
	{
		free_child(&pipex);
		put_error_and_exit(ERR_CMD, 1);
	}
	if (execve(pipex.cmd_fullpath, pipex.cmd_args, envp) == -1)
		put_error_and_exit(ERR_EXECVE, 0);
	return (NULL);
}

void	execute_first_command(t_pipex pipex, char *argv[], char *envp[])
{
	if (dup2(pipex.tube[1], STDOUT_FILENO) < 0)
		put_error_and_exit(ERR_DUP2, 0);
	if (close(pipex.tube[0]) < 0)
		put_error_and_exit(ERR_PIPE, 0);
	if (dup2(pipex.infile, STDIN_FILENO) < 0)
		put_error_and_exit(ERR_DUP2, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (pipex.cmd_args == NULL)
		put_error_and_exit(ERR_CMD, 1);
	execute_command(pipex, envp);
}

void	execute_second_command(t_pipex pipex, char *argv[], char *envp[])
{
	if (dup2(pipex.tube[0], STDIN_FILENO) < 0)
		put_error_and_exit(ERR_DUP2, 0);
	if (close(pipex.tube[1]) < 0)
		put_error_and_exit(ERR_PIPE, 0);
	if (dup2(pipex.outfile, STDOUT_FILENO) < 0)
		put_error_and_exit(ERR_DUP2, 0);
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (pipex.cmd_args == NULL)
		put_error_and_exit(ERR_CMD, 1);
	execute_command(pipex, envp);
}
