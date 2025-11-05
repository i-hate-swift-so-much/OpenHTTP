#pragma once

#include <mutex>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include <algorithm> 
#include <iterator>
#include <string.h>
#include "../Networking/RequestParser.h"

struct CamfigKeyString{
    std::string Key;
    std::string Value;
};

struct CamfigKeyBool{
    std::string Key;
    bool Value;
};

struct CamfigKeyInt{
    std::string Key;
    int Value;
};

struct CamfigParserKey{
    std::string Key;
    std::string Value;
};

struct CamfigListKey{
    std::string type;

    CamfigKeyString StringKey;
    CamfigKeyBool BoolKey;
    CamfigKeyInt IntKey;
};

struct CamfigList{

    std::vector<CamfigListKey> Keys;
};

bool isDigit(char value);

bool isAlpha(char value);

CamfigListKey* FindCamfigListKeyByStringKey(CamfigList& list, const std::string& targetKey);

CamfigListKey* FindCamfigListKeyByIntegerKey(CamfigList& list, const std::string& targetKey);

CamfigListKey* FindCamfigListKeyByBoolKey(CamfigList& list, const std::string& targetKey);

std::string GetTypeOfValue(std::string value);

CamfigList ParseCamfig(std::string data);

std::string FetchCamfig();

CamfigList GetCamfig();

void DumpCamfigList(CamfigList list);