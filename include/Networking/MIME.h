#pragma once

#include <iostream>
#include <string.h>
#include "stdio.h"
#include <iostream>
#include <map>


std::string fileType(std::string path);

std::string MIMEmatchEXTENSION(std::string extension);

std::string MIMEmatchPATH(std::string path);

std::string MIMEmatchFIRST(std::string MIME);