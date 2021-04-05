#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/param.h>
#include<sys/uio.h>
#include<unistd.h>

#define BUF_LEN 256 // バッファのサイズ

int main(int argc, char *argv[]){
    int s; // socket用のファイルディスクリプタ
    struct hostent *servhost; // ホスト名とIPアドレスを扱うための構造体
    struct sockaddr_in  server; // ソケットを扱うための構造体
    struct servent *service; // サービスを扱うための構造体

    char send_buf[BUF_LEN]; // サーバに送るhttpプロトコル用のバッファ
    char host[BUF_LEN] = "localhost"; // 接続するホスト名
    char path[BUF_LEN] = "/"; // 要求するパス
    unsigned short port = 80; // 接続するポート番号

    if (argc == 0) {
        fprintf(stderr, "usage: ./http_client {URL}\n");
        return -1;
    }
    char host_path[BUF_LEN];
    if (strlen(argv[1]) > BUF_LEN -1) {
        fprintf(stderr, "error: too long URL.\n");
        return -1;
    }

    if(strstr(argv[1], "http://") && sscanf(argv[1], "http://%s", host_path) && strcmp(argv[1], "http://")) {
        char *p;
        p = strchr(host_path, '/'); // "/"以降の文字列をpathにコピー
        if(p != NULL) {
            strcpy(path, p);
            *p = '\0';
        }
        strcpy(host, host_path);

        p = strchr(host, ':'); // :の部分の処理
        if(p != NULL) {
            port = atoi(p+1); // ポート番号の取得
            if(port <= 0)
                port = 80;
            *p = '\0';
        }
    } else {
        fprintf(stderr, "usage: ./http_client http：//{host}/{path}\n");
        return -1;
    }

    printf("http://%s%s を取得します。\n\n", host, path);

    // ホストの情報を取得する
    servhost = gethostbyname(host);
    if(servhost == NULL){
        fprintf(stderr, "[%s] から IP アドレスへの変換に失敗しました。\n", host);
        return 0;
    }

    memset(&server, 0, sizeof(server)); // 構造体をクリア (サンプルではbzeroが使われていた)

    server.sin_family = AF_INET; // AD_INET ... IPv4インターネットプロトコル

    // void *memcpy(void *dest, const void *src, size_t n);
    memcpy(&server.sin_addr, servhost->h_addr, servhost->h_length); // 構造体をコピーする

    if(port != 0) {
        server.sin_port = htons(port);
    } else {
        if((service = getservbyname("http", "tcp")) != NULL) // getservbyname でポート番号を取得
            server.sin_port = service->s_port;
        else    
            server.sin_port = htons(80);
    }

    // ソケット生成
    if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "error: fail to create socket.\n");
        return -1;
    }

    // サーバに接続
    if(connect(s, (struct sockaddr *)&server, sizeof(server)) == -1){
        fprintf(stderr, "error: fail to connect.\n");
        return -1;
    }

    // httpプロトコル作成
	sprintf(send_buf, "GET %s HTTP/1.1\r\n", path);
	write(s, send_buf, strlen(send_buf));

	sprintf(send_buf, "host: %s\r\n", host);
	write(s, send_buf, strlen(send_buf));

	sprintf(send_buf, "\r\n");
	write(s, send_buf, strlen(send_buf));

    // read
	while (1) {
		char buf[BUF_LEN];
		memset(buf, '\0', BUF_LEN);
		int read_size;
		read_size = read(s, buf, BUF_LEN);
		if (read_size > 0) {
			write(1, buf, read_size);
		} else {
			break;
		}
	}

	close(s);

	return 0;
}