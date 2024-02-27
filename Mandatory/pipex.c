/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:34:55 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/27 20:10:49 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	put_error_msg(const char *msg, int is_manual)
{
	if(is_manual == 1)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else{
	perror(msg);
	exit(EXIT_FAILURE);
	}
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

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		put_error_msg(ERR_INVALID, 1);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		put_error_msg(ERR_INFILE, 0);
	pipex.outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex.outfile < 0)
		put_error_msg(ERR_OUTFILE, 0);
	pipe(pipex.tube);
	if (pipex.tube < 0)
		put_error_msg(ERR_PIPE, 0);
	pipex.split_path_array = find_path_from_env(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		execute_first_command(pipex, argv, envp);
	waitpid(pipex.pid1, NULL, 0);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		execute_second_command(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid2, NULL, 0);
	free_parent(&pipex);
	return (0);
}
