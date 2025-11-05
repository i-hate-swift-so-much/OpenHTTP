program_arm64 := bin/arm64/OpenHTTP
program_x86_64 := bin/x86_64/OpenHTTP

files := src/main.cpp src/Camfig/Camfig.cpp src/ErrorHandling/Logs.cpp src/Networking/MIME.cpp src/Networking/RequestParser.cpp src/Networking/server.cpp

arm64: ${files}
	g++ -arch arm64 ${files} -Iinclude -o ${program_arm64}

x86_64: ${files}
	g++ -arch x86_64 ${files} -Iinclude -o ${program_x86_64}