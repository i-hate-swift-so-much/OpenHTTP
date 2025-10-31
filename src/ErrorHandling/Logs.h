#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string>

#include <mutex>
#include <thread>
#include <iostream>
#include <fstream>
#include <exception>
#include <ctime>

//Used for writing to the logs directory

std::mutex ofstream_mutex;

std::string HTTPheaderFromResponse(std::string response){
    std::string toret = "";
    for(int i = 0; i < response.length(); i++){
        if(response[i] == '\r' && response[i+1] == '\n' && response[i+2] == '\r' && response[i+3] == '\n'){
            return toret;
        }else{
            toret+=response[i];
        }
    }
    return "";
}

void LogErrorE(std::exception& message){   
    std::time_t currentTime = std::time(NULL);
    std::tm* UTCdate = std::gmtime(&currentTime);
    std::string FDate = "";
    FDate += std::to_string(UTCdate->tm_year + 1900) + "-"; // Year
    FDate += std::to_string(UTCdate->tm_mon + 1) + "-"; // Month
    FDate += std::to_string(UTCdate->tm_mday) + "_"; // Day
    FDate += std::to_string(UTCdate->tm_hour) + "-"; // Hour
    FDate += std::to_string(UTCdate->tm_min) + "-"; // Minutes
    FDate += std::to_string(UTCdate->tm_sec); // Seconds

    std::string fileName = "Logs/Crash-Log_" + FDate + ".txt";
    std::cerr << "Error! Creating crash log... " + fileName << std::endl;
    std::string header = "";
    header += std::to_string(UTCdate->tm_year + 1900) + "/"; // Year
    header += std::to_string(UTCdate->tm_mon + 1) + "/"; // Month
    header += std::to_string(UTCdate->tm_mday) + " "; // Day
    header += std::to_string(UTCdate->tm_hour) + ":"; // Hour
    header += std::to_string(UTCdate->tm_min) + ":"; // Minutes
    header += std::to_string(UTCdate->tm_sec); // Seconds
    ofstream_mutex.lock();  
    std::ofstream crashLog(fileName, std::ios::out);
    if (crashLog.is_open()) {
        crashLog << FDate << std::endl << message.what() << std::endl;
        crashLog.close();
    }
    ofstream_mutex.unlock();  
}

void LogErrorS(std::string message){    
    std::time_t currentTime = std::time(NULL);
    std::tm* UTCdate = std::gmtime(&currentTime);
    std::string FDate = "";
    FDate += std::to_string(UTCdate->tm_year + 1900) + "-"; // Year
    FDate += std::to_string(UTCdate->tm_mon + 1) + "-"; // Month
    FDate += std::to_string(UTCdate->tm_mday) + "_"; // Day
    FDate += std::to_string(UTCdate->tm_hour) + "-"; // Hour
    FDate += std::to_string(UTCdate->tm_min) + "-"; // Minutes
    FDate += std::to_string(UTCdate->tm_sec); // Seconds

    std::string fileName = "Logs/Crash-Log_" + FDate + ".txt";
    std::cerr << "Error! Creating crash log... " + fileName << std::endl;
    std::string header = "";
    header += std::to_string(UTCdate->tm_year + 1900) + "/"; // Year
    header += std::to_string(UTCdate->tm_mon + 1) + "/"; // Month
    header += std::to_string(UTCdate->tm_mday) + " "; // Day
    header += std::to_string(UTCdate->tm_hour) + ":"; // Hour
    header += std::to_string(UTCdate->tm_min) + ":"; // Minutes
    header += std::to_string(UTCdate->tm_sec); // Seconds
    ofstream_mutex.lock();
    std::ofstream crashLog(fileName, std::ios::out);
    if (crashLog.is_open()) {
        crashLog << header << std::endl << message;
        crashLog.close();
    }
    ofstream_mutex.unlock();  
}

void LogRequest(std::string incomingRequest){
    std::time_t currentTime = std::time(NULL);
    std::tm* UTCdate = std::gmtime(&currentTime);
    std::string FDate = "";
    FDate += std::to_string(UTCdate->tm_year + 1900) + "-"; // Year
    FDate += std::to_string(UTCdate->tm_mon + 1) + "-"; // Month
    FDate += std::to_string(UTCdate->tm_mday); // Day

    std::string fileName = "Logs/Request-Log_" + FDate + ".txt";
    std::string header = "Received a request on ";
    header += std::to_string(UTCdate->tm_year + 1900) + "/"; // Year
    header += std::to_string(UTCdate->tm_mon + 1) + "/"; // Month
    header += std::to_string(UTCdate->tm_mday) + " at "; // Day
    header += std::to_string(UTCdate->tm_hour) + ":"; // Hour
    header += std::to_string(UTCdate->tm_min) + ":"; // Minutes
    header += std::to_string(UTCdate->tm_sec) + " which read the following: "; // Seconds
    ofstream_mutex.lock();  
    std::ofstream crashLog(fileName, std::ios::app);
    if (crashLog.is_open()) {
        crashLog << header << std::endl << incomingRequest << std::endl;
        crashLog.close();
    }
    ofstream_mutex.unlock();  
}

void LogResponse(std::string outgoingResponse, std::string path, bool addBody = true){
    std::time_t currentTime = std::time(NULL);
    std::tm* UTCdate = std::gmtime(&currentTime);
    std::string FDate = "";
    FDate += std::to_string(UTCdate->tm_year + 1900) + "-"; // Year
    FDate += std::to_string(UTCdate->tm_mon + 1) + "-"; // Month
    FDate += std::to_string(UTCdate->tm_mday); // Day

    std::string fileName = "Logs/Response-Log_" + FDate + ".txt";
    std::string header = "Sent a response on ";
    header += std::to_string(UTCdate->tm_year + 1900) + "/"; // Year
    header += std::to_string(UTCdate->tm_mon + 1) + "/"; // Month
    header += std::to_string(UTCdate->tm_mday) + " at "; // Day
    header += std::to_string(UTCdate->tm_hour) + ":"; // Hour
    header += std::to_string(UTCdate->tm_min) + ":"; // Minutes
    header += std::to_string(UTCdate->tm_sec) + " for the path: "; // Seconds
    header += path + " which read as the following: ";
    ofstream_mutex.lock();  
    std::ofstream crashLog(fileName, std::ios::app);
    if (crashLog.is_open()) {
        crashLog << header << std::endl;
        if(addBody){
            crashLog << outgoingResponse << std::endl;
        }else{
            crashLog << HTTPheaderFromResponse(outgoingResponse) << std::endl;
        }
        crashLog.close();
    }
    ofstream_mutex.unlock();  
}