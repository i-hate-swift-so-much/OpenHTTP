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
#include "../ErrorHandling/Logs.h"

std::string ExtractPATH(int index, char buffer[4096]);
std::string SanitizePath(std::string path);
std::string GetKey(int index, char buffer[4096]);
std::vector<unsigned char> FetchResourceRanged(std::string path, std::streamoff begin, std::streamoff end);
std::map<std::string, std::string> FindNextKeyValuePair(std::string body, int index);
int IndexOfNextLine(int index, std::string haystack);
std::string GetFirstKeyFromMap(std::map<std::string, std::string> map);
std::map<std::string, std::string> MakeRequestMap(char buffer[4096]);
std::string FetchResource(const std::string& path);
std::vector<int> InterpretRange(std::string unparsed);
std::string RangeRequestToContentRange(std::string range);
std::string CreateResponseParsed(std::map<std::string,std::string> parsed);
int ExtractResponseCodeFromResponse(std::string response);
void DumpMap(std::map<std::string, std::string> map);