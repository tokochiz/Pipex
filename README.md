# Level2 : Pipex

## 課題要件
- Program name : pipex
- Turn in file : Makefile, *.h, *.c
- Makefile NAME, all, clean, fclean, re
- Arguments : file1 cmd1 cmd2 file2
- 以下のプログラムの要件として指定されている関数以外は使用しないこと : open, close, read, write, malloc, free, perror, strerror, access, dup, dup2,execve, exit, fork, pipe, unlink, wait, waitpid
- Libft authorized Yes
- Description This project is about handling pipes.

## 概要
- 目的　: シェルの「リダイレクション」と「パイプ」の処理を扱う

### Mandatory
- プログラムは以下のように実行する
	- 4つの引数を取る：
	- file1とfile2はファイル名
	- cmd1とcmd2はそのパラメータを含むシェルコマンド
```shell
./pipex file1 cmd1 cmd2 file2
```
- file1の内容をcmd1に渡し、その出力をcmd2に渡し、最終的な出力をfile2に書き込む
- 以下の出力と同じ動作をする
```shell
< file1 cmd1 | cmd2 > file2
```




