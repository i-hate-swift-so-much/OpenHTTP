# Another parser for camfig except its in python because of the GUI

from io import TextIOWrapper

# Returns the camfig file
def FetchCamfig():
    try:
        with open(".camfig", "r") as file:
            return file.read()
    except FileNotFoundError:
        print("Couldn't read camfig")
        return ""

# Accepts a file
def ParseCamfig(camfig):
    toRet: dict = {"Address":"Any","Port":"80","Fallback_Port":"226"}
    lines = camfig.splitlines(keepends=True)
    for line in lines:
        curKey = ""
        curValue = ""
        curRead = ""
        if line.strip().startswith("#"):
            continue
        for index, char in enumerate(line):
            if char != ":" and char != "\n" and char != " " and char != "#":
                curRead += char
            elif char == ":":
                curKey = curRead
                curRead = ""
            elif char == "\n" or char == " " or index == len(line) and curRead != "":
                curValue = curRead
                toRet[curKey] = curValue
                curKey = ""
                curValue = ""
            elif char == "#":
                continue
       
    return toRet

# Fetches then Parses camfig and returns a dictionary
def RequestCamfig():
    return ParseCamfig(FetchCamfig())