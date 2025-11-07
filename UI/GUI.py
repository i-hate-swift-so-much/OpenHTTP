import subprocess
import sys
import threading

from Camfig import *
from tkinter import *
from tkinter import ttk
from tkinter import scrolledtext

Root = Tk(className="OpenHTTP")
Root.title("OpenHTTP Python GUI")

Root.geometry("800x400")
Root.resizable(0, 0)

Settings = RequestCamfig()

Mainframe = ttk.Frame(Root, padding=(24, 24, 24, 24))
Mainframe.pack(fill=BOTH, expand=True)

Mainframe.grid_columnconfigure(0, weight=1) 
Mainframe.grid_columnconfigure(1, weight=1) 
Mainframe.grid_columnconfigure(2, weight=1) 
Mainframe.grid_rowconfigure(0, weight=1)
Mainframe.grid_rowconfigure(1, weight=1)
Mainframe.grid_rowconfigure(2, weight=1)

PortLabel = Label(Mainframe, text=f"Port: {Settings["Port"]}", font=("Arial", 18), relief="solid", borderwidth=2)
PortLabel.grid(column=0, row=0, sticky="nsew", padx=5)

PortLabel = Label(Mainframe, text=f"Fallback_Port: {Settings["Fallback_Port"]}", font=("Arial", 18), relief="solid", borderwidth=2)
PortLabel.grid(column=0, row=1, sticky="nsew", padx=5)

AddressLabel = Label(Mainframe, text=f"Address: {Settings["Address"]}", font=("Arial", 18), relief="solid", borderwidth=2, wraplength=200)
AddressLabel.grid(column=0, row=2, sticky="nsew", padx=5)

OutputLabel = scrolledtext.ScrolledText(Mainframe, font=("Arial", 12), relief="solid", borderwidth=2, highlightbackground="white", background="white", foreground="black", wrap=WORD, width=60, height=0.5)
OutputLabel.grid(column=1, row=0, columnspan=2, rowspan=2, sticky="nesw", padx=5, pady=5)

def StopStart():
    if running:
        KillServer()
        StartStopButton.config(text="Start")
    else:
        StartServer()
        StartStopButton.config(text="Stop")

StartStopButton = Button(Mainframe, text="Start", command=StopStart, font=("Arial", 18), relief="solid")
StartStopButton.grid(column=1, row=2, columnspan=2, sticky="nesw", padx=10)

ProgramArchitecture = ""

if(len(sys.argv) > 1):
    ProgramArchitecture = sys.argv[1]

ProcessPath = ""
if ProgramArchitecture == "x86_64":
    ProcessPath = "./bin/x86_64/OpenHTTP"
elif ProgramArchitecture == "arm64" or ProgramArchitecture == "":
    ProcessPath = "./bin/arm64/OpenHTTP"

running = False

process = None

def StartServer():
    global running
    running = True
    global process
    process = subprocess.Popen(
        [ProcessPath],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1
    )
    Root.after(10, ReadOutput)

def KillServer():
    global running
    if(process):
        process.terminate()
    running = False

def ThreadReadOutput():
    ReadThread = threading.Thread(target=ReadOutput)
    ReadThread.daemon = True
    ReadThread.start()

def ReadOutput():
    global running
    if not running:
        return
    line = process.stdout.readline()
    if line:
        OutputLabel.insert(INSERT, (line.strip().replace("[31m", "ERROR: ").replace("[0m","")) + "\n")
        OutputLabel.see(END)
    
    if process.poll() is None:
        Root.after(10, ThreadReadOutput)

    else:
        KillServer()
        OutputLabel.insert(INSERT, "Process Ended \n")
        OutputLabel.see(END)

Root.protocol("WM_DELETE_WINDOW", KillServer)

Root.mainloop()