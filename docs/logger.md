# logger

## 動き方
- 通信方式はPUBSUB
- loggerサーバーがSUBで待ち受けて、各プロセスがPUBでログ送信
- 送信データはprotobuf使用
    - process_name : string
    - msg : string

## Todo
- loggerと子プロセスとのハンドシェイク
-
