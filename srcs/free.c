/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:38:03 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/25 14:03:39 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	// 入力ファイル、出力ファイルのファイルディスクりぷたをクローズする
	close(pipex->infile);
	close(pipex->outfile);
	// 実行可能なコマンドのパスが格納された文字列の配列　を、メモリから解放する
	while (pipex->cmd_paths_list[i])
	{
		free(pipex->cmd_paths_list[i]);
		i++;
	}
	//配列自体をメモリから解放する、→配列の各要素と配列自体をどちらもクリーンする
	free(pipex->cmd_paths_list);
}

void	free_child(t_pipex *pipex)
{
	// 子プロセスによって使用されたリソース・・・動的に確保されたメモリ、fd、パイプ　を解放する
	int i;

	i = 0;
	// 実行するコマンドの引数が格納された文字列の配列をクリーンする
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	// 配列自体をメモリから解放する
	free(pipex->cmd_args);
	// コマンド自体を表す文字列もメモリから解放する
	free(pipex->cmd_fullpath);
}