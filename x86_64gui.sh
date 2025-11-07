#!/bin/bash

command -v python3 >/dev/null 2>&1 && python3 UI/GUI.py x86_64
command -v python >/dev/null 2>&1 && python UI/GUI.py x86_64