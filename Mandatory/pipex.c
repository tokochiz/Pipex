/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:32:09 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/19 18:13:45 by  ctokoyod        ###   ########.fr       */
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
		put_error_and_exit(ERR_INVALID, 1);
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], (O_RDWR | O_TRUNC | O_CREAT), 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		put_error_file(pipex);
	pipe(pipex.tube);
	if (pipex.tube < 0)
		put_error_and_exit(ERR_PIPE, 0);
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
