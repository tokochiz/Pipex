/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:34:55 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/07 17:29:09 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

//pipex.split_path_array = find_path_from_env(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0){
	printf("m2\n");
		execute_first_command(pipex, argv, envp);
	}
	printf("m3\n");
	waitpid(pipex.pid1, NULL, 0);
	printf("m4\n");
	pipex.pid2 = fork();
	printf("m5\n");
	if (pipex.pid2 == 0){
	printf("m7\n");
		execute_second_command(pipex, argv, envp);
	}
	printf("m6\n");
	close_pipes(&pipex);
	
	waitpid(pipex.pid2, NULL, 0);
	printf("m8\n");
	free_parent(&pipex);
	printf("m9\n");
	return (0);
}
