/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:34:42 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/27 18:07:57 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*get_cmd_execution_path(char **split_path_array, char *cmd)
{
	char	*path_with_slash;
	char	*cmd_fullpath;

	if (ft_strchr(cmd[0], '/') != 0)
	{
		if (access(cmd[0], F_OK) == 0)
			return (cmd[0]);
		else
			put_error_msg(ERR_DIR);
	}
	while (*split_path_array)
	{
		path_with_slash = ft_strjoin(*split_path_array, "/");
		cmd_fullpath = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (access(cmd_fullpath, F_OK) == 0)
			return (cmd_fullpath);
		free(cmd_fullpath);
		split_path_array++;
	}
	return (NULL);
}

char	**find_path_from_env(char *envp[])
{
	char	*all_path_str;

	all_path_str = NULL;
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
		{
			all_path_str = *envp + 5;
			break ;
		}
		envp++;
	}
	if (all_path_str == NULL)
		return (NULL);
	return (ft_split(all_path_str, ':'));
}

int		execute_command(int infile, int outfile[], char **cmd_args,
			char *cmd_fullpath);
{
	pid_t pid;
	
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		dup2(outfile[1], STDOUT_FILENO);
		if (outfile[0])
			close(outfile[0]);
		dup2(infile, 0);

		if (pipex.cmd_fullpath == NULL)
		{
			free_child(&pipex);
			put_error_msg(ERR_CMD);
			exit(1);
		}
		execve(pipex.cmd_fullpath, pipex.cmd_args, NULL);
	}
	waitpid(pipex.pid);
	return (outfile[0]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex pipex;
	int cmd_index;

	if (argc != 5)
		put_error_msg(ERR_INVALID);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		put_error_msg(ERR_INFILE);
	pipex.outfile[0] = open((argc - 1), O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex.outfile < 0)
		put_error_msg(ERR_OUTFILE);
	pipex.split_path_array = find_path_from_env(envp);
	cmd_index = 2;
	while (cmd_index <= argc - 2)
	{
		pipe(pipex.tube);
		if (pipex.tube < 0)
			put_error_msg(ERR_PIPE);
		pipex.cmd_args = ft_split(argv[cmd_index], ' ');
		pipex.cmd_fullpath = get_cmd_execution_path(pipex.split_path_array,
			pipex.cmd_args[0]);
		pipex.infile = execute_command(pipex.infile, pipex.tube, pipex.cmd_args,
			pipex.split_path_array);
		// pipe 奇数の時、偶数の時で分ける
			// pip を４つ用意
			// 
	}
}
// heardoc GNL folder入れる
