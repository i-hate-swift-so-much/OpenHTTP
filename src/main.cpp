#include "Networking/server.h"
#include "stdio.h"
#include <iostream>
#include "Networking/MIME.h"
#include "Networking/RequestParser.h"
#include "ErrorHandling/Logs.h"
#include <signal.h>

int serverMain(){
    WebServer server(80);
    try{
        server.startServer();
    }catch(std::exception& e){
        LogErrorE(e);
        server.closeServer();
        std::cerr << "An error occurred and was logged.";
    }
    server.closeServer();

    return 0;
}

int debugMain(){
    char bufferImage[4096] = "GET /Images/Buttons/Last_Song.png HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:143.0) Gecko/20100101 Firefox/143.0\r\nAccept: image/avif,image/webp,image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br, zstd\r\nPrefer: safe\r\nConnection: keep-alive\r\nReferer: http://127.0.0.1/\r\nSec-Fetch-Dest: image\r\nSec-Fetch-Mode: no-cors\r\nSec-Fetch-Site: same-origin\r\nPriority: u=5\r\n\r\n";
    char bufferSongRange[4096] = "GET /Songs/KanyeWest/GoodAssJob/mamasboyfriend.mp3 HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:143.0) Gecko/20100101 Firefox/143.0\r\nAccept: */*\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br, zstd, identity\r\nPrefer: safe\r\nRange: bytes=1963-2091\r\nIf-Modified-Since: Sat, 01 Jan 1970 00:00:00 GMT\r\nConnection: keep-alive\r\nReferer: http://127.0.0.1/\r\nSec-Fetch-Dest: empty\r\nSec-Fetch-Mode: cors\r\nSec-Fetch-Site: same-origin\r\n\r\n";
    char bufferCSS[4096] = "GET /CSS/main.css HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:143.0) Gecko/20100101 Firefox/143.0\r\nAccept: text/css,*/*;q=0.1\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br, zstd\r\nPrefer: safe\r\nConnection: keep-alive\r\nReferer: http://127.0.0.1/\r\nSec-Fetch-Dest: style\r\nSec-Fetch-Mode: no-cors\r\nSec-Fetch-Site: same-origin\r\nPriority: u=2\r\n";
    char bufferHTML[4096] = "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:143.0) Gecko/20100101 Firefox/143.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br, zstd\r\nPrefer: safe\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nSec-Fetch-Dest: document\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-Site: none\r\nSec-Fetch-User: ?1\r\nPriority: u=0, i\r\n\r\n";
    char bufferSong[4096] = "HEAD /Songs/KanyeWest/GoodAssJob/flashinglights2.mp3 HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:143.0) Gecko/20100101 Firefox/143.0\r\nAccept: */*\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br, zstd\r\nPrefer: safe\r\nIf-Modified-Since: Sat, 01 Jan 1970 00:00:00 GMT\r\nConnection: keep-alive\r\nReferer: http://127.0.0.1/\r\nSec-Fetch-Dest: empty\r\nSec-Fetch-Mode: cors\r\nSec-Fetch-Site: same-origin\r\n\r\n";
    char bufferCITS[4096] = "HEAD /Songs/KanyeWest/Yandhi/cityinthesky.mp3 HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:143.0) Gecko/20100101 Firefox/143.0\r\nAccept: */*\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br, zstd\r\nPrefer: safe\r\nIf-Modified-Since: Sat, 01 Jan 1970 00:00:00 GMT\r\nConnection: keep-alive\r\nReferer: http://127.0.0.1/\r\nSec-Fetch-Dest: empty\r\nSec-Fetch-Mode: cors\r\nSec-Fetch-Site: same-origin\r\nPragma: no-cache\r\nCache-Control: no-cache\r\n\r\n";
    std::map<std::string, std::string> RequestMapTest = MakeRequestMap(bufferHTML);
    //DumpMap(RequestMapTest);
    //InterpretRange("bytes=1963-2091");
    CreateResponseParsed(RequestMapTest);
    return 0;
}

int main(){
    signal(SIGPIPE, SIG_IGN);
    serverMain();
    return 0;
}