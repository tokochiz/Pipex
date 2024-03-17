/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:18:46 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/03/17 21:33:05 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	put_error_file(t_pipex pipex)
{
	if (pipex.infile < 0)
		perror(ERR_INFILE);
	if (pipex.outfile < 0)
		perror(ERR_OUTFILE);
	exit(EXIT_FAILURE);
}

void	put_error(const char *msg, int is_manual)
{
	if (is_manual == 1)
		ft_putstr_fd(msg, STDERR_FILENO);
	else
		perror(msg);
	exit(EXIT_FAILURE);
}

