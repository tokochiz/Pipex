/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:19:21 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/22 18:34:02 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


// 環境変数へのアクセスが必要な場合 char *envp[]を引数に追加
int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;

	// 引数チェック
	if (argc != 5)
		return (error_msg("Invalid number of arguments"));
			// TODO: ERROR msg を出力させる
			
	// ファイルオープン
	pipex.infile = open(argv[1], O_RDONLY); // 読み取り専用でファイルを開く
	if (pipex.infile < 0)
		error_msg(); // TODO: ERROR msg を出力させる
		
	pipex.outfile = open(argv[argc - 1], O_RDWR, ); //読み書きできるように権限を設定する
	if (pipex.outfile < 0) 
		error_msg();        // TODO: ERROR msg を出力させる
		
	// パイプ作成
	pipe(pipex.tube);
	if (pipex.tube < 0)
		error_mgs();
		
	// コマンドパスの検索
	pipex.paths = find_path_from_env(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	
	// ２つの子プロセスの作成
	pipex.pid1 = fork();
	if (pipex.pid1 == 0) //成功した場合、親プロセスには子プロセスの PID ,子プロセスには 0 が返る
		first_child_process();
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child_process();

	// パイプのクローズ
	close_pipes(&pipex);

	
	// 子プロセスの終了をまつ
	wait_pid();
	wait_pid();
	
	// 親リソースの解放
	releace_parent_resource();
	
	return (0);
}
