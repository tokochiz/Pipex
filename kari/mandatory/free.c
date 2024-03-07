/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:51:10 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/07 17:39:01 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	printf("fp1\n");
	printf("%d %d\n",pipex->infile,pipex->outfile);
	close(pipex->infile);
	printf("%d %d\n",pipex->infile,pipex->outfile);
	// close(pipex->outfile);
	printf("fp1");
	while (pipex->split_path_array[i])
	{
		printf("%s\n",pipex->split_path_array[0]);
		free(pipex->split_path_array[i]);
		i++;
	}
	free(pipex->split_path_array);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd_fullpath);
}
