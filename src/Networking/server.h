#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#include <stdint.h>
#include <stdio.h>
#include <thread>

#include <cstring>

#include <iostream>
#include <fstream>
#include <mutex>

#include "../ErrorHandling/Logs.h"

#include "MIME.h"
#include "RequestParser.h"
#include <ctime>

#define RESET_COL   "\033[0m"
#define RED_COL     "\033[31m"

class WebServer{
    private:
        int server_fd;
        int p;
        struct sockaddr_in address;
        std::mutex cout_mutex;
        bool running;
    public:
        WebServer(int port){
            p = port;
        };

        void startServer(){
            running = true;
            std::cout << "Starting server" << std::endl;
            server_fd = socket(AF_INET, SOCK_STREAM, 0);
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons((p != NULL) ? p : 4000);
            //address.sin_port = htons(4000);

            if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) != -1){
                std::cout << "Socket established" << std::endl;

                listen(server_fd, 3);

                std::cout << "Listening on port " << ((p != NULL) ? p : 4000) << std::endl;

                int addrlen = sizeof(address);

                while(running){
                    int client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                    if(client_fd >= 0){
                        std::thread t([this, client_fd]() {
                            processClient(client_fd);
                            close(client_fd);
                        });
                        t.detach();
                    }
                }
            }else{
                std::cerr << RED_COL << "Socket " << std::to_string(p) << " is busy! Resulting to fallback port of 226" << RESET_COL << std::endl;
                p = 226;
                startServer();
                return;
            };
        }

        void closeServer(){
            running = false;
            std::cout << "Closing server"  << std::endl;
            close(server_fd);
            std::cout << "Server closed"  << std::endl;
        }

        void processClient(int client){
            char buffer[4096] = {0};
            read(client, buffer, 4096);
            LogRequest(buffer);
            std::map<std::string, std::string> RequestMap = MakeRequestMap(buffer);
            std::string response = CreateResponseParsed(RequestMap);
            std::string path = RequestMap["Path"];
            int code = ExtractResponseCodeFromResponse(response);
            
            if(code == 404){
                cout_mutex.lock();
                std::cout << "Received Request... Response: 404" << std::endl;
                cout_mutex.unlock();
                write(client, response.data(), response.size());
            }else{
                cout_mutex.lock();
                std::cout << "Received Request... Response: " << path << " Content-Type: " << MIMEmatchPATH(path) << std::endl;
                cout_mutex.unlock();
                write(client, response.data(), response.size());
            }
        }
};