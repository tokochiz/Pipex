/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:19:21 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/17 18:33:40 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
ボーナスを作りたい場合は、再帰で多段パイプを実装
*/

// TODO :引数の解析
// TODO :ファイルオープンとリダイレクション
// TODO :パイプの作成
// TODO :プロセスのフォーク？
// TODO :実行とクリーンアップ

// TODO :ボーナス　再帰で多段パイプを実装　複数パイプ処理関数
// TODO :ボーナス　ヒアドキュメント処理関数作成する　here_doc の場合の処理




int	main(int argc, char **argv)
{
	// TODO(1) : 引数受け取り　
	// TODO(1)-1 : 引数の数をカウントする→５つ必要
	if (argc != 5)
	{
		fprintf(stderr, "Usage : %s file1 cmd1 cmd2 file2\n", argv[0]);
		return (1);
	}
	//  引数からファイル名とコマンドを取得
	char *file1;
	char *cmd1;
	char *cmd2;
	char *file2;
	file1 = argv[1];
	cmd1 = argv[2];
	cmd2 = argv[3];
	file2 = argv[4];

	// TODO : pipex関数に渡す
	pipex(file1, cmd1, cmd2, file2);

	return (0);
}
