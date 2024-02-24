/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:19:21 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/24 19:38:36 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path_from_env(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0) // "PATH"で始まる環境変数を探す
			return (*envp + 5);  // "PATH="の長さ（５）後のパスのリストを指す
		envp++;
	}
	return (NULL);
}

// 環境変数へのアクセスが必要な場合 char *envp[]を引数に追加
int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	// 引数チェック
	if (argc != 5)
		error_msg("Invalid number of arguments");
		return(1);
	// TODO: ERROR msg を出力させる
	// ファイルオープン
	pipex.infile = open(argv[1], O_RDONLY); // 読み取り専用でファイルを開く
	if (pipex.infile < 0)
		error_msg(); // TODO: ERROR msg を出力させる
	pipex.outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0000644); //読み書き両方でオープンもしくは、ファイルが存在しなければ新規作成、ファイルサイズを0に切り詰める
	if (pipex.outfile < 0)
		error_msg(); // TODO: ERROR msg を出力させる
	// パイプ作成
	pipe(pipex.tube);
	if (pipex.tube < 0)
		error_mgs();

	// コマンドパスの検索
	pipex.paths = find_path_from_env(envp);
	pipex.cmd_paths_list = ft_split(pipex.paths, ':');

	// ２つの子プロセスの作成
	pipex.pid1 = fork();
	if (pipex.pid1 == 0) //成功した場合、親プロセスには子プロセスの PID ,子プロセスには 0 が返る
		execute_first_command(pipex, argv, envp);
	waitpid(pipex.pid1, NULL, 0);

	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		execute_second_command(pipex, argv, envp);

	// パイプのクローズ
	close_pipes(&pipex);

	// 親プロセスで子プロセスの終了を待つ
	waitpid(pipex.pid2, NULL, 0);

	// 親リソースの解放
	releace_parent_resources(&pipex);
	return (0);
}
