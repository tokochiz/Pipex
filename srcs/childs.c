/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:41:21 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/25 19:48:31 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_cmd_execution_path(char **paths_list, char *cmd)
{
	char	*path_with_slash;
	char	*cmd_fullpath;

	while (*paths_list)
	{
		path_with_slash = ft_strjoin(*paths_list, "/");
		cmd_fullpath = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		// TODO: コマンドの存在チェック　0	引数 mode で指定したアクセス権がある
		if (access(cmd_fullpath, 0) == 0)
			return (cmd_fullpath);
		// TODO:見つからなかったらフリー
		free(cmd_fullpath);
		// TODO: 次のパスに移動
		paths_list++;
	}
	// TODO:　全て見つからなかったらNULL返す
	return (NULL);
}

void	execute_first_command(t_pipex pipex, char **argv, char *envp[])
{
	// TODO: パイプの書き込みがわを標準出力にする　標準出力：１
	dup2(pipex.tube[1], 1);
	// TODO:　パイプの読み取りがわを閉じる
	close(pipex.tube[0]);
	// TODO: 入力ファイルを標準入力にリダイレクトする このプロセスで読み取るデータはfile１から来ることになる
	dup2(pipex.infile, 0);
	// TODO: 第２の引き数（cmd１）を空白文字で分割、結果をlこまんどとして保持
	pipex.cmd_args = ft_split(argv[2], ' ');
	// TODO: コマンドを探す　なかったら異常終了する
	pipex.cmd_fullpath = get_cmd_execution_path(pipex.cmd_paths_list,
		pipex.cmd_args[0]);
	// 指定されたコマンドが見つからない場合にエラーメッセーじを表示する
	if (pipex.cmd_fullpath == NULL)
	{
		free_child(&pipex);
		put_error_msg(ERR_CMD);
		exit(1);
	}
	// TODO: 見つかったコマンドを、指定された引数と環境変数で実行する
	// execve (実行ファイルのパス、実行時の引数、環境変数)
	execve(pipex.cmd_fullpath, pipex.cmd_args, envp);
}

void	execute_second_command(t_pipex pipex, char **argv, char *envp[])
{
	// TODO: パイプの読み込みがわを標準入力にする　標準入力：１
	dup2(pipex.tube[0], 0);
	// TODO:　パイプの読み取りがわを閉じる
	close(pipex.tube[1]);
	// TODO: 出力ファイルを標準出力にリダイレクトする
	dup2(pipex.outfile, 1);
	// TODO: 第3の引き数（cmd2）を空白文字で分割、結果をこまんどとして保持
	pipex.cmd_args = ft_split(argv[3], ' ');
	// TODO: コマンドを探す　なかったら異常終了する
	pipex.cmd_fullpath = get_cmd_execution_path(pipex.cmd_paths_list,
		pipex.cmd_args[0]);
	// 指定されたコマンドが見つからない場合にエラーメッセーじを表示する
	if (pipex.cmd_fullpath == NULL)
	{
		free_child(&pipex);
		put_error_msg(ERR_CMD);
		exit(1);
	}
	// TODO: 見つかったコマンドを、指定された引数と環境変数で実行する
	// execve (実行ファイルのパス、実行時の引数、環境変数)
	execve(pipex.cmd_fullpath, pipex.cmd_args, envp);
}
