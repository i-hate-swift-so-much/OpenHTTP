#include "Camfig/Camfig.h"

std::mutex camfig_mutex;

bool isDigit(char value){
    char Digits[10] = {'1','2','3','4','5','6','7','8','9','0'};
    return std::find(std::begin(Digits), std::end(Digits), value) != std::end(Digits);
}

bool isAlpha(char value){
    char Alphas[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','.'};
    return std::find(std::begin(Alphas), std::end(Alphas), value) != std::end(Alphas);
}

CamfigListKey* FindCamfigListKeyByStringKey(CamfigList& list, const std::string& targetKey) {
    for (auto& key : list.Keys) {
        if (key.StringKey.Key == targetKey) {
            return &key;
        }
    }
    return nullptr; // not found
}

CamfigListKey* FindCamfigListKeyByIntegerKey(CamfigList& list, const std::string& targetKey) {
    for (auto& key : list.Keys) {
        if (key.IntKey.Key == targetKey) {
            return &key;
        }
    }
    return nullptr; // not found
}

CamfigListKey* FindCamfigListKeyByBoolKey(CamfigList& list, const std::string& targetKey) {
    for (auto& key : list.Keys) {
        if (key.BoolKey.Key == targetKey) {
            return &key;
        }
    }
    return nullptr; // not found
}

std::string GetTypeOfValue(std::string value){
    bool ContainsDigit = false;
    bool ContainsAlpha = false;
    if(value == "false" || value == "true") { return "Bool"; }

    for(int i = 0; i < value.size(); i++){
        bool digit = isDigit(value[i]);
        bool alpha = isAlpha(value[i]);
        if(!ContainsDigit){ContainsDigit = digit;}
        if(!ContainsAlpha){ContainsAlpha = alpha;}
    }
    
    std::string type = "";

    if(ContainsDigit){
        type = "Integer";
    }
    if(ContainsAlpha){
        type = "String";
    }
    if(ContainsAlpha && ContainsDigit){
        type = "String";
    }

    return type;
}

CamfigList ParseCamfig(std::string data){
    CamfigList toRet = CamfigList();

    CamfigParserKey curListKey = CamfigParserKey();

    std::string curTemp = "";
    for(int i = 0; i < data.size(); i++){
        char curChar = data[i];
        if(curChar != ':' && curChar != '\n' && curChar != ' ' && curChar != '#'){
            curTemp+=curChar;
        }else if (curChar == ':'){
            curListKey.Key = curTemp;
            curTemp = "";
        }else if (curChar == '\n' && curTemp != ""){
            curListKey.Value = curTemp;
            std::string type = GetTypeOfValue(curListKey.Value);
            CamfigListKey toAdd;
            toAdd.type = type;
            if(type == "String"){
                CamfigKeyString StringKey;
                StringKey.Key = curListKey.Key;
                StringKey.Value = curListKey.Value;
                toAdd.StringKey = StringKey;
            }else if(type == "Integer"){
                CamfigKeyInt IntKey;
                IntKey.Key = curListKey.Key;
                IntKey.Value = std::stoi(curListKey.Value);
                toAdd.IntKey = IntKey;
            }else if(type == "Bool"){
                CamfigKeyBool BoolKey;
                BoolKey.Key = curListKey.Key;
                BoolKey.Value = curListKey.Value == "true";
                toAdd.BoolKey = BoolKey;
            }else{
                std::cout << "Unrecognized Camfig type: " << curListKey.Key << "|" << curListKey.Value << "|" << type << std::endl;
            }
            toRet.Keys.push_back(toAdd);
            curTemp = "";
        }else if (curChar == ' ' && curTemp != ""){
            curListKey.Value = curTemp;
            std::string type = GetTypeOfValue(curListKey.Value);
            CamfigListKey toAdd;
            toAdd.type = type;
            if(type == "String"){
                CamfigKeyString StringKey;
                StringKey.Key = curListKey.Key;
                StringKey.Value = curListKey.Value;
                toAdd.StringKey = StringKey;
            }else if(type == "Integer"){
                CamfigKeyInt IntKey;
                IntKey.Key = curListKey.Key;
                IntKey.Value = std::stoi(curListKey.Value);
                toAdd.IntKey = IntKey;
            }else if(type == "Bool"){
                CamfigKeyBool BoolKey;
                BoolKey.Key = curListKey.Key;
                BoolKey.Value = curListKey.Value == "true";
                toAdd.BoolKey = BoolKey;
            }else{
                std::cout << "Unrecognized Camfig type: " << curListKey.Key << "|" << curListKey.Value << "|" << type << std::endl;
            }
            toRet.Keys.push_back(toAdd);
            int nextNewLine = IndexOfNextLine(i, data);
            i = nextNewLine;
            curTemp = "";
        }else if (curChar == '#'){
            int nextNewLine = IndexOfNextLine(i, data);
            if(nextNewLine == i){
                break;
            }
            i = nextNewLine;
        }
        if(i == data.size()-1){
            curListKey.Value = curTemp;
            std::string type = GetTypeOfValue(curListKey.Value);
            CamfigListKey toAdd;
            toAdd.type = type;
            if(type == "String"){
                CamfigKeyString StringKey;
                StringKey.Key = curListKey.Key;
                StringKey.Value = curListKey.Value;
                toAdd.StringKey = StringKey;
            }else if(type == "Integer"){
                CamfigKeyInt IntKey;
                IntKey.Key = curListKey.Key;
                IntKey.Value = std::stoi(curListKey.Value);
                toAdd.IntKey = IntKey;
            }else if(type == "Bool"){
                CamfigKeyBool BoolKey;
                BoolKey.Key = curListKey.Key;
                BoolKey.Value = curListKey.Value == "true";
                toAdd.BoolKey = BoolKey;
            }else{
                std::cout << "Unrecognized Camfig type: " << curListKey.Key << "|" << curListKey.Value << "|" << type << std::endl;
            }
            toRet.Keys.push_back(toAdd);
            curTemp = "";
        }
    }
    return toRet;
}

std::string FetchCamfig(){
    std::ifstream file(".camfig", std::ios::out);

    file.seekg(0, std::ios::end);
    std::streampos end = file.tellg();
    file.seekg(0, std::ios::beg);
    std::streampos start = file.tellg();

    int size = end-start;

    std::string data(size, '\0');

    if (!file.read(&data[0], size)) {
        std::cerr << "Couldn't read camfig" << std::endl;
        return "";
    }

    return data;
}

CamfigList GetCamfig(){
    std::string fileData = FetchCamfig();
    return ParseCamfig(fileData);
}

void DumpCamfigList(CamfigList list){
    for(auto& key : list.Keys){
        std::string type = key.type;
        if(type == "Bool"){
            std::cout << key.BoolKey.Key << "|" << key.BoolKey.Value << std::endl;
        }else if(type == "String"){
            std::cout << key.StringKey.Key << "|" << key.StringKey.Value << std::endl;
        }else if(type == "Integer"){
            std::cout << key.IntKey.Key << "|" << key.IntKey.Value << std::endl;
        }
    }
}