/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:54:54 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/07 17:25:40 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**find_path_from_env(char *envp[])
{
	char	*all_path_str;

	all_path_str = NULL;
	if (!envp){
		printf("erro1\n");
		put_error_after_exit(ERR_CMD, 1);
	}
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0 && *(*envp + 5) != '\0')
		{
			all_path_str = *envp + 5;
			break ;
		}
		envp++;
	}
	if (all_path_str == NULL)
		put_error_after_exit(ERR_CMD, 1);
	return (ft_split(all_path_str, ':'));
}

char	*get_cmd(t_pipex pipex, char *envp[])
{
	char	*path_with_slash;
	char	*cmd_fullpath;

	if (ft_strchr(pipex.cmd_args[0], '/') != 0)
	{
		printf("g1\n");
		if (access(pipex.cmd_args[0], X_OK) == 0)
			return (pipex.cmd_args[0]);
		else
			put_error_after_exit(ERR_DIR, 1);
	}
	printf("g2\n");
	pipex.split_path_array = find_path_from_env(envp);
	if (pipex.split_path_array == NULL)
		perror(ERR_DIR);
	while (pipex.split_path_array)
	{
		path_with_slash = ft_strjoin(*pipex.split_path_array, "/");
		cmd_fullpath = ft_strjoin(path_with_slash, pipex.cmd_args[0]);
		free(path_with_slash);
		if (access(cmd_fullpath, X_OK) == 0)
			return (cmd_fullpath);
		free(cmd_fullpath);
		pipex.split_path_array++;
	}
	return (NULL);
}

void	execute_path(t_pipex pipex, char *envp[])
{
		printf("1\n");
	if (pipex.cmd_args == NULL || pipex.cmd_args[0] == NULL
		|| *(pipex.cmd_args[0]) == '\0')
	{
		printf("error2\n");
		free_child(&pipex);
		put_error_after_exit(ERR_CMD, 1);
	}
		printf("2\n");
	pipex.cmd_fullpath = get_cmd(pipex, envp);
		printf("3\n");
	if (pipex.cmd_fullpath == NULL)
	{
		printf("error\n");
		free_child(&pipex);
		put_error_after_exit(ERR_CMD, 1);
	}
		printf("4\n");
	if (execve(pipex.cmd_fullpath, pipex.cmd_args, envp) == -1){
		printf("5\n");
		put_error_after_exit(ERR_EXECVE, 0);
	}
}

void	execute_first_command(t_pipex pipex, char *argv[], char *envp[])
{
	printf("f0\n");
	printf("%d\n", pipex.tube[1]);
	dup2(pipex.tube[1], STDOUT_FILENO);
	printf("f1\n");
	close(pipex.tube[0]);
	printf("f0\n");
	dup2(pipex.infile, STDIN_FILENO);
	printf("f0\n");
	pipex.cmd_args = ft_split(argv[2], ' ');
	printf("f1\n");
	execute_path(pipex, envp);
}

void	execute_second_command(t_pipex pipex, char *argv[], char *envp[])
{
	printf("s1\n");
	dup2(pipex.tube[0], STDIN_FILENO);
	printf("s22\n");
	close(pipex.tube[1]);
	printf("%d\n", pipex.outfile);
	printf("s33\n");
	dup2(pipex.outfile, STDOUT_FILENO);
	printf("s4\n");
	pipex.cmd_args = ft_split(argv[3], ' ');
	printf("s5\n");
	execute_path(pipex, envp);
	printf("s6\n");
}
