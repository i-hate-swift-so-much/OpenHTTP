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

std::string HTTPHeaderFromResponse(std::string response);

void LogErrorE(std::exception& message);

void LogErrorS(std::string message);

void LogRequest(std::string incomingRequest);

void LogResponse(std::string outgoingResponse, std::string path, bool addBody);