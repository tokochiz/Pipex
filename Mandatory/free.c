/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:51:10 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/17 19:25:12 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_split(char **split_array)
{
	int	i;

	i = 0;
	while (split_array[i])
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->split_paths != NULL)
	{
		while (pipex->split_paths[i])
		{
			free(pipex->split_paths[i]);
			i++;
		}
		free(pipex->split_paths);
	}
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_args != NULL)
	{
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
	}
	if (pipex->cmd_fullpath != NULL)
		free(pipex->cmd_fullpath);
}
