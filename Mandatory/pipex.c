/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:34:55 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/05 20:31:51 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**find_path_from_env(char *envp[])
{
	char	*all_path_str;

	all_path_str = NULL;
	if (!envp)
		put_error_after_exit(ERR_CMD, 1);
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

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		put_error_after_exit(ERR_INVALID, 1);
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		put_error_file(pipex);
	pipe(pipex.tube);
	if (pipex.tube < 0)
		put_error_after_exit(ERR_PIPE, 0);
	pipex.split_path_array = find_path_from_env(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		execute_first_command(pipex, argv, envp);
	waitpid(pipex.pid1, NULL, WNOHANG);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		execute_second_command(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid2, NULL, WNOHANG);
	free_parent(&pipex);
	return (0);
}
