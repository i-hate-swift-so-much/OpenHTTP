#include "Networking/server.h"

int ResetCount = 0;

WebServer:: WebServer(int port){
    p = port;
};

void WebServer::startServer(){
    running = true;
    CamfigList camfig = GetCamfig();
    std::cout << "Starting server" << std::endl;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    CamfigListKey* CamfigAddress = FindCamfigListKeyByStringKey(camfig, "Address");
    if(CamfigAddress != nullptr && !OverrideAddress){ 
        const char* localhost_str = "0.0.0.0";
        if(CamfigAddress->StringKey.Value == "localhost"){
            address.sin_addr.s_addr = inet_addr(localhost_str);
            std::cout << "Address set to localhost." << std::endl;
        }else if(CamfigAddress->StringKey.Value == "Any"){
            address.sin_addr.s_addr = htonl(INADDR_ANY);
            std::cout << "Address set to all network interfaces." << std::endl;
        }else if(CamfigAddress->StringKey.Value != ""){
            const char* setAddress = CamfigAddress->StringKey.Value.c_str();
            address.sin_addr.s_addr = inet_addr(setAddress);
            std::cout << "Address set to " << CamfigAddress->StringKey.Value << std::endl;
        }else{
            address.sin_addr.s_addr = htonl(INADDR_ANY);
            std::cout << "Address set to all network interfaces." << std::endl;
        }
    }else if (CamfigAddress == nullptr){
        std::cout << "No Address Provided. Address set to localhost" << std::endl;
        const char* localhost_str = "0.0.0.0";
        address.sin_addr.s_addr = inet_addr(localhost_str);
    }else{
        address.sin_addr.s_addr = htonl(INADDR_ANY);
        std::cout << "Address set to all network interfaces." << std::endl;
    }

    CamfigListKey* CamfigPort = FindCamfigListKeyByIntegerKey(camfig, "Port");
    if(CamfigPort != nullptr){ 
        p = CamfigPort->IntKey.Value;
    }
    
    int fallback = 226;
    CamfigListKey* CamfigFallback = FindCamfigListKeyByIntegerKey(camfig, "Fallback_Port");
    if(CamfigFallback != nullptr){ 
        fallback = CamfigFallback->IntKey.Value;
    }

    int ResetLimit = 5;
    CamfigListKey* CamfigResetLimit= FindCamfigListKeyByIntegerKey(camfig, "Reset_Limit");
    if(CamfigResetLimit != nullptr){ 
        ResetLimit = CamfigResetLimit->IntKey.Value;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(p);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) != -1){
        std::cout << "Socket established" << std::endl;

        listen(server_fd, 3);

        std::cout << "Listening on port " << (p) << std::endl;

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
        if(ResetCount >= ResetLimit-1){
            std::cout << "The server has reset the maximum amount of " << ResetLimit << " times please check your .camfig file and check that the configuration is correct." << std::endl;
            LogErrorS("Maximum amount of server restarts (" + std::to_string(ResetLimit) + ") has been reached, please check your .camfig file and check that the configuration is correct.");
            return;
        }
        std::cerr << RED_COL << "Server crashed during initialization! Port " << p << " might be busy, Resulting to fallback port of " << fallback << " and now using all available network interfaces" << RESET_COL << std::endl;
        std::cout << "Attempt " << ResetCount+2 << "..." << std::endl;
        p = fallback;
        ResetCount++;
        OverrideAddress = true;
        startServer();
        return;
    };
}

void WebServer::closeServer(){
    running = false;
    std::cout << "Closing server"  << std::endl;
    close(server_fd);
    std::cout << "Server closed"  << std::endl;
}

void WebServer::processClient(int client){
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