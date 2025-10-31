#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <map>
#include <fstream>
#include <mutex>
#include <thread>
#include <iostream>
#include <exception>
#include <vector>
#include "MIME.h"
#include "RequestParser.h"

std::mutex cout_mutex;
std::mutex cerr_mutex;

std::string ExtractPATH(int index, char buffer[4096]){
    std::string cur = "";
    for(int i = index; i < 4096; i++){
        if(buffer[i] != ' ' && buffer[i] != '?'){
            cur+=buffer[i];
        }else{
            break;
        }
    }
    if(cur == "/"){
        cur = "index.html";
    }
    return cur;
}

std::string SanitizePath(std::string path) {
    std::string sanitized = path;
    
    // Remove any '../' sequences
    size_t pos;
    while ((pos = sanitized.find("..")) != std::string::npos) {
        sanitized.erase(pos, 2);
    }
    
    // Optional: replace leading '/' with ""
    if (!sanitized.empty() && sanitized[0] == '/') {
        sanitized = sanitized.substr(1);
    }
    
    // Default to index.html if path is empty
    if (sanitized.empty()) sanitized = "index.html";
    
    return sanitized;
}

std::string GetKey(int index, char buffer[4096]){
    std::string cur = "";
    for(int i = index; i < 4096; i++){
        if(buffer[i] != ' '){
            cur+=buffer[i];
        }else{
            break;
        }
    }
    return cur;
}

std::vector<unsigned char> FetchResourceRanged(std::string path, std::streamoff begin, std::streamoff end){
    std::vector<unsigned char> data;

    std::ifstream file(path, std::ios::binary);


    if (!file.is_open()) {
        cout_mutex.lock();
        std::cout << "Failed to open file: " << path << std::endl;
        cout_mutex.unlock();
        if(MIMEmatchPATH(path) == "text/html"){
            std::vector<unsigned char> charlist;
            std::string message = "<center><h1>404</h1><h3>The requested file was not found on this server.</h3><a href='/'>Return to the main page</a></center>";
            for(int i = 0; i < message.length(); i++){
                charlist.push_back(message[i]);
            }
            return charlist;
        }else{
            std::vector<unsigned char> charlist;
            std::string message = "<center><h1>404</h1><h3>The requested file was not found on this server.</h3><a href='/'>Return to the main page</a></center>";
            for(int i = 0; i < message.length(); i++){
                charlist.push_back(message[i]);
            }
            return charlist;
        }
    }

    if (!file) {
        cerr_mutex.lock();
        std::cerr << "Failed to open file: " << path << std::endl;
        cerr_mutex.unlock();
        return data;
    }

    // Get file size
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    if (begin >= fileSize) {
        cerr_mutex.lock();
        std::cerr << "Begin position exceeds file size (" << fileSize << ")" << std::endl;
        cerr_mutex.unlock();
        return data;
    }

    
    // Clamp end to file size if needed
    if (end > fileSize) end = fileSize;
    if (end < begin) end = fileSize;
    if (begin > fileSize) begin = 0;
    if (begin < 0) begin = 0;

    std::streamsize size = end - begin;
    data.resize(size);

    file.seekg(begin);
    file.read(reinterpret_cast<char*>(data.data()), size);

    if (!file) {
        cerr_mutex.lock();
        std::cerr << "Error reading file (read " << file.gcount() << " bytes instead of " << size << ")" << std::endl;
        cerr_mutex.unlock();
        data.resize(file.gcount());
    }

    cout_mutex.lock();
    std::cout << "Read " << size << " bytes from " << path << std::endl;
    cout_mutex.unlock();
    return data;
}   

std::map<std::string, std::string> FindNextKeyValuePair(std::string body, int index){
    int length = body.size();
    std::map<std::string, std::string> ret;
    std::string cur = "";
    for(index; index < length; index++){
        if(body[index] != '\r'){
            cur+=body[index];
        }else{
            index++;
            break;
        }
    }

    int keyEnd = 0;
    std::string key = "";
    for(int i = 0; i < cur.size(); i++){
        if(cur[i] != ':'){
            key+=cur[i];
        }else{
            keyEnd = i+2;
            break;
        }
    }

    std::string value = "";
    for(int i = keyEnd; i < cur.size(); i++){
        value+=cur[i];
    }
    ret[key] = value;

    return ret;
}

int IndexOfNextLine(int index, std::string haystack){
    int startI = index;
    for(index; index < haystack.size(); index++){
        if(haystack[index] == '\n'){
            return index;
        }
    }
    std::cerr << "Couldn't find a newline" << std::endl;
    return startI;
}

std::string GetFirstKeyFromMap(std::map<std::string, std::string> map){
    if(!map.empty()){
        std::map<std::string, std::string>::iterator it = map.begin();

        std::string firstKey = it->first;

        return firstKey;
    }else{
        std::cerr << "Length of the given map is 0. | GetFirstKeyFromMap | RequestParser.h | Line 126" << std::endl;
        throw "Length of the given map is 0. | GetFirstKeyFromMap | RequestParser.h | Line 126";
        return "";
    }
}

std::map<std::string, std::string> MakeRequestMap(char buffer[4096]){
    int curIndex = 0;
    
    std::map<std::string, std::string> toReturn;

    //Get method
    std::string METHOD = "";
    for(curIndex; curIndex < 4096; curIndex++){
        if(buffer[curIndex] != ' '){
            METHOD+=buffer[curIndex];
        }else{
            curIndex++;
            break;
        }
    }
    toReturn["Method"] = METHOD;

    //Get path
    std::string PATH = ExtractPATH(curIndex, buffer);
    toReturn["Path"]= PATH;

    //Get host
    curIndex = curIndex+ 11 + PATH.size(); 

    for(int i = curIndex; i < strlen(buffer); i++){
        std::map<std::string, std::string> NEXT = FindNextKeyValuePair(buffer, i);
        toReturn.insert(NEXT.begin(), NEXT.end());
        int lastI = i;
        i = IndexOfNextLine(i, buffer);
        if(lastI == i){
            break;
        }
    }

    return toReturn;

}

std::string FetchResource(const std::string& path) {
    std::ifstream fetched(path, std::ios::binary);


    if (!fetched.is_open()) {
        cout_mutex.lock();
        std::cout << "Failed to open file: " << path << std::endl;
        cout_mutex.unlock();
        if(MIMEmatchPATH(path) == "text/html"){
            return "<center><h1>404</h1><h3>The requested file was not found on this server.</h3><a href='/'>Return to the main page</a></center>";
        }else{
            return "";
        }
    }
    
    fetched.seekg(0, std::ios::end);
    std::streampos end = fetched.tellg();
    fetched.seekg(0, std::ios::beg);
    std::streampos start = fetched.tellg();

    std::streamsize size = end - start;
    std::string fileData(size, '\0');

    if (!fetched.read(&fileData[0], size)) {
        cerr_mutex.lock();
        std::cerr << "Error reading file: " << path << std::endl;
        cerr_mutex.unlock();
        return "";
    }

    std::cout << "Read " << size << " bytes from " << path << std::endl;
    return fileData;
}

std::vector<int> InterpretRange(std::string unparsed){
    std::vector<int> toReturn;
    std::string num1 = "0";

    for(int i = 6; i < unparsed.size(); i++){
        if(unparsed[i] != '-'){
            num1+=unparsed[i];
        }else{
            break;
        }
    }

    std::string num2 = "";
    for(int i = 6+num1.size(); i < unparsed.size(); i++){
        if(unparsed[i] != '-'){
           num2+=unparsed[i];
        }else{
            break;
        }
    }

    if(num2 == ""){
        num2 = "-1";
    }

    toReturn.push_back(std::stoi(num1));
    toReturn.push_back(std::stoi(num2));

    return toReturn;
}

std::string RangeRequestToContentRange(std::string range){
    std::string final = "";
    
    std::string unit = "";

    for(int i = 0; i < range.size(); i++){
        if(range[i] != '='){
            unit+=range[i];
        }else{
            break;
        }
    }

    std::vector<int> interpret = InterpretRange(range);

    final +=unit + " ";
    final += std::to_string(interpret[0]) + "-";
    final += std::to_string(interpret[1]) + "/";
    final += "*";

    return final;
}

std::string CreateResponseParsed(std::map<std::string,std::string> parsed){
    std::string path = parsed["Path"];
    path = SanitizePath(path);
    int ResponseCode = 200;
    if(parsed.find("Range") != parsed.end()){
        std::string range = parsed["Range"];
        std::vector<int> ranges = InterpretRange(range);
        
        std::vector<unsigned char> resource = FetchResourceRanged("www/" + path, ranges[0], ranges[1]);
        std::vector<unsigned char> char404;
        std::string message = "<center><h1>404</h1><h3>The requested file was not found on this server.</h3><a href='/'>Return to the main page</a></center>";
        for(int i = 0; i < message.length(); i++){
            char404.push_back(message[i]);
        }

        if(resource == char404){
            ResponseCode = 404;
        }else{
            ResponseCode = 206;
        }

        std::string ResponseString = "";
        switch(ResponseCode){
            case 200:
                ResponseString = "200 OK";
                break;
            case 404:
                ResponseString = "404 Not Found";
                break;
            case 206:
                ResponseString= "206 Partial Content";
                break;
            default:
                ResponseString = "500 Internal Server Error";
                break;
        }

        std::string MIME = MIMEmatchPATH(path);

        if (MIME == "backend/error"){
            MIME = "*/*";
            ResponseString = "404 Not Found";
            resource = char404;
            std::string toReturn = "HTTP/1.1 " + ResponseString + "\r\n Content-Length: " + std::to_string(resource.size()) + "\r\n Content-Type: " + MIME + "\r\n\r\n";
        
            std::string resourceString = "";
            for(int i = 0; i < resource.size(); i++){
                resourceString.push_back(resource[i]);
            }

            std::string fType = MIMEmatchFIRST(MIME);
            bool addBody = fType != "audio" && fType != "video" && fType != "image" && fType != "application";

            if(parsed["Method"] != "HEAD"){
                toReturn+=resourceString;
            }

            LogResponse(toReturn, path, addBody);

            return toReturn;
        }

        std::string ContentRange = RangeRequestToContentRange(range);

        std::string toReturn = "HTTP/1.1 " + ResponseString + "\r\n Content-Length: " + std::to_string(resource.size()) + "\r\nContent-Range: " + ContentRange + "\r\n Content-Type: " + MIME + "\r\n\r\n";
        
        std::string resourceString = "";
        for(int i = 0; i < resource.size(); i++){
            resourceString.push_back(resource[i]);
        }

        std::string fType = MIMEmatchFIRST(MIME);
        bool addBody = fType != "audio" && fType != "video" && fType != "image" && fType != "application";

        if(parsed["Method"] != "HEAD"){
            toReturn+=resourceString;
        }

        LogResponse(toReturn, path, addBody);

        return toReturn;
    }else{
        std::string resource = FetchResource("www/"+path);
        std::string message = "<center><h1>404</h1><h3>The requested file was not found on this server.</h3><a href='/'>Return to the main page</a></center>";
        if(resource == message){
            ResponseCode = 404;
        }else{
            ResponseCode = 200;
        }

        std::string ResponseString = "";
        switch(ResponseCode){
            case 200:
                ResponseString = "200 OK";
                break;
            case 404:
                ResponseString = "404 Not Found";
                break;
            case 206:
                ResponseString= "206 Partial Content";
                break;
            default:
                ResponseString = "500 Internal Server Error";
                break;
        }

        std::string MIME = MIMEmatchPATH(path);

        if (MIME == "backend/error"){
            MIME = "*/*";
            ResponseString = "404 Not Found";
            resource = message;
            std::string toReturn = "HTTP/1.1 " + ResponseString + "\r\n Content-Length: " + std::to_string(resource.size()) + "\r\n Content-Type: " + MIME + "\r\n\r\n";

            std::string fType = MIMEmatchFIRST(MIME);
            bool addBody = fType != "audio" && fType != "video" && fType != "image" && fType != "application" && fType != "*";

            toReturn+=resource;

            LogResponse(toReturn, path, addBody);

            return toReturn;
        }
        
        std::string toReturn = "HTTP/1.1 " + ResponseString + "\r\n Content-Length: " + std::to_string(resource.size()) + "\r\n Content-Type: " + MIME + "\r\n\r\n";

        
        if(parsed["Method"] != "HEAD"){
            toReturn+=resource;
        }

        std::string fType = MIMEmatchFIRST(MIME);
        bool addBody = fType != "audio" && fType != "video" && fType != "image" && fType != "application";

        
        LogResponse(toReturn, path, addBody);

        return toReturn;
    }
}

int ExtractResponseCodeFromResponse(std::string response){
    std::string code = "";
    for(int i = 9; i < 9+4; i++){
        code+=response[i];
    }
    return std::stoi(code);
}

void DumpMap(std::map<std::string, std::string> map){
    
    for(std::map<std::string,std::string>::iterator it = map.begin(); it != map.end(); it++) {
        cout_mutex.lock();
        std::cout << it->first << ": " << it->second << std::endl;
        cout_mutex.unlock();
    }
}