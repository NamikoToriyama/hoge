#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <string.h>

int main(void){
    int rsock, wsock;
    struct sockaddr_in addr, client; // netinet/in.hに入っている構造体
    int len;
    int ret;
    char buf[2048], inbuf[2048];

    /* make sockert */
    // int socket(int domain, int type, int protocol)
    // AD_INET ... IPv4インターネットプロトコル
    // SOCK_STREAM ... 双方向のバイトストリーム形式の通信を提供する
    if((rsock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Error. Can not make socket\n");
        close(rsock);
        return -1;
    }

    /* socket setting */
    // IPv4に8080番ポートを指定する
    // アドレスは指定しないためINADDR_ANYを選択
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    /* binding socket */
    if ((ret = bind(rsock, (struct sockaddr*)&addr, sizeof(addr))) < 0) {
        fprintf(stderr, "Error. Can not bind socket\n");
        close(rsock);
        return -1;
    }

    /* listen socket */
    // int listen(int socket_fd, int backlog)
    // ソケット上の接続要求を受け付ける意志とキュー長を指定する
    // ここではキューの最大長は適当に5に指定している
    if (listen(rsock, 5) < 0) {
        fprintf(stderr, "error: listen()\n");
        close(rsock);
        return -1;
    }

    // 応答用HTTPメッセージ作成
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf),
	 "HTTP/1.0 200 OK\r\n"
	 "Content-Length: 20\r\n"
	 "Content-Type: text/html\r\n"
	 "\r\n"
	 "HELLO\r\n");

    

    /* accept TCP connection from client */
    while(1){
        len = sizeof(client);
        if((wsock = accept(rsock, (struct sockaddr *)&client, &len) < 0)) {
            fprintf(stderr, "error: accepting a socket.\n");
            break;
        }
        
        /* send message */
        fprintf(stderr, "%s", buf);
        memset(inbuf, 0, sizeof(inbuf));
        recv(wsock, inbuf, sizeof(inbuf), 0);
        // 相手が何を言おうとダミーHTTPメッセージ送信
        send(wsock, buf, (int)strlen(buf), 0);
        // write(wsock, "HTTP1.1 200 OK", 14);
        close(wsock);
        
    }

    /* close TCP session */
    close(rsock);

    return 0;
}
