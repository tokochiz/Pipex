/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:18:46 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/27 22:26:45 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	put_error_msg(const char *msg, int is_manual)
{
	if (is_manual == 1)
		ft_putstr_fd(msg, STDERR_FILENO);
	else
		perror(msg);
	exit(EXIT_FAILURE);
}

void	put_error_file(t_pipex *pipex)
{
	if (pipex->infile < 0)
		ft_putstr_fd(ERR_INFILE, STDERR_FILENO);
	if (pipex->outfile < 0)
		ft_putstr_fd(ERR_OUTFILE, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
