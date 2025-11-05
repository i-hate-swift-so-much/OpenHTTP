#pragma once

#include <ifaddrs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#include <stdint.h>
#include <stdio.h>
#include <thread>

#include <cstring>

#include <iostream>
#include <fstream>
#include <mutex>

#include "ErrorHandling/Logs.h"
#include "Camfig/Camfig.h"

#include "MIME.h"
#include "Networking/RequestParser.h"
#include <ctime>

#define RESET_COL   "\033[0m"
#define RED_COL     "\033[31m"

class WebServer{
    private:
        int server_fd;
        int p = 80;
        struct sockaddr_in address;
        std::mutex cout_mutex;
        bool running;
        bool OverrideAddress = false;
    public:
        WebServer(int port);
        void startServer();
        void closeServer();
        void processClient(int client);
};