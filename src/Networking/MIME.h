#pragma once

#include <iostream>
#include <string.h>
#include "stdio.h"
#include <iostream>
#include <map>

std::map<std::string, std::string> ExtensionToMIME = {
    {"aac", "audio/aac"},
    {"abw", "application/x-abiword"},
    {"apng", "image/apng"},
    {"arc", "application/x-abiword"},
    {"avif", "image/avif"},
    {"avi", "video/x-msvideo"},
    {"azw", "application/vnd.amazon.ebook"},
    {"bin", "application/octet-stream"},
    {"bmp", "image/bmp"},
    {"bz", "application/x-bzip"},
    {"bz2", "application/x-bzip2"},
    {"cda", "application/x-cdf"},
    {"csh", "application/x-csh"},
    {"css", "text/css"},
    {"csv", "text/csv"},
    {"doc", "application/msword"},
    {"docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
    {"eot", "application/vnd.ms-fontobject"},
    {"epub", "application/epub+zip"},
    {"gz", "application/gzip"},
    {"gif", "image/gif"},
    {"htm", "text/html"},
    {"html", "text/html"},
    {"ico", "image/vnd.microsoft.icon"},
    {"ics", "text/calendar"},
    {"jar", "application/java-archive"},
    {"jpeg", "image/jpeg"},
    {"jpg", "image/jpeg"},
    {"js", "text/javascript"},
    {"json", "application/json"},
    {"jsonld", "application/ld+json"},
    {"md", "text/markdown"},
    {"mid", "audio/midi"},
    {"midi", "audio/midi"},
    {"mjs", "text/javascript"},
    {"mp3", "audio/mpeg"},
    {"mp4", "video/mp4"},
    {"mpeg", "video/mped"},
    {"mpkg", "application/vnd.apple.installer+xml"},
    {"odp", "application/vnd.oasis.opendocument.presentation"},
    {"ods", "application/vnd.oasis.opendocument.spreadsheet"},
    {"odt", "application/vnd.oasis.opendocument.text"},
    {"oga", "audio/ogg"},
    {"ogv", "video/ogg"},
    {"ogx", "application/ogg"},
    {"opus", "audio/ogg"},
    {"otf", "font/otf"},
    {"png", "image/png"},
    {"pdf", "application/pdf"},
    {"php", "application/x-httpd-php"},
    {"ppt", "application/vnd.ms-powerpoint"},
    {"pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
    {"rar", "application/vnd.rar"},
    {"rtf", "application/rtf"},
    {"sh", "application/x-sh"},
    {"svg", "image/svg+xml"},
    {"tar", "application/x-tar"},
    {"tif", "image/tiff"},
    {"tiff", "image/tiff"},
    {"ts", "video/mp2t"},
    {"ttf", "font/ttf"},
    {"txt", "text/plain"},
    {"vsd", "application/vnd.visio"},
    {"wav", "audio/wav"},
    {"weba", "audio/webm"},
    {"webm", "video/webm"},
    {"webmanifest", "application/manifest+json"},
    {"webp", "image/webp"},
    {"woff", "font/woff"},
    {"woff2", "font/woff2"},
    {"xhtml", "application/xhtml+xml"},
    {"xls", "application/vnd.ms-excel"},
    {"xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
    {"xml", "application/xml"},
    {"xul", "application/vnd.mozilla.xul+xml"},
    {"zip", "application/zip"},
    {"7z", "application/x-7z-compressed"},
    {"error","message/error"}
};


//Made for 'server.h', converts file type to MIME type, also extracts file type from a file.

std::string fileType(std::string path){
    //Get index of the final period in the path (incase theres more than one).
    int lastPeriodIndex = 0;
    for(int i = 0; i < path.length(); i++){
        if(path[i] == '.'){
            lastPeriodIndex=i;
        }
    }

    if(lastPeriodIndex == 0){
        return "error";
    }

    std::string extension = "";
    //Scan the rest of the letters for the file extension
    for(int i = lastPeriodIndex+1; i < path.length(); i++){
        extension+=path[i];
    }

    return extension;
}

std::string MIMEmatchEXTENSION(std::string extension){
    if(ExtensionToMIME.find(extension) != ExtensionToMIME.end()){
        return ExtensionToMIME[extension];
    }
    return "application/octet-stream";  
}

std::string MIMEmatchPATH(std::string path){
    std::string extension = fileType(path);
    if(extension == "error") {return "backend/error";}
    return MIMEmatchEXTENSION(extension);
}

//Takes a MIME as an input and returns the first part of it ("audio/mpeg" -> "audio")
std::string MIMEmatchFIRST(std::string MIME){
    std::string toret = "";
    for(int i = 0; i < MIME.length(); i++){
        if(MIME[i] != '/'){
            toret+=MIME[i];
        }else{
            return toret;
        }
    }
    return toret;
}
