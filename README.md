# OpenHTTP
OpenHTTP is an open source HTTP web server made by Cameron McLaughlin between September 10th 2025 and October 30th 2025

[Click this to skip all the technical mumbo jumbo](#how-to-actually-use-it).

## Features
Currently, OpenHTTP can receive `GET` and `HEAD` requests and respond to them, along with being able to turn a file path into a MIME type (e.g "www/index.html" -> "text/html"). The MIME conversion uses [the official Mozilla "Common Media Types" page](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/MIME_types/Common_types). OpenHTTP also has proper 404 and 206 handling for the `Range: butes=min-max` request header.

## Limitations
Unfortunately, OpenHTTP is still in the early stages of devlopment, so many features included by other web servers (such as Apache) are not compatible with OpenHTTP (unsupported requests are met with a 500 for now). The <ins>only</ins> requests that OpenHTTP can interpret and respond to are `GET` and `HEAD` requests, meaning that `POST` requests are unsupported. It also very rarely hangs for no reason.

## Speed
OpenHTTP has been benchmarked with the "Siege" HTTP load tester (`brew install siege`). Below are the results when tested with 10 concurrent clients and every directory listed in the example `www` file path and using the -i command line argument.
```
Transactions: 6862 hits
Availability: 100.00 %
Elapsed time: 60.61 secs
Data transferred: 40733.49 MB
Response time: 88.14 ms
Transaction rate: 113.22 trans/sec
Throughput: 672.06 MB/sec
Concurrency: 9.98
Successful transactions: 6862
Failed transactions: 0
Longest transaction: 370.00 ms
Shortest transaction: 0.00 ms
```
The results will vary depending on the server hardware, as this was executed on my local host.

## Future plans
For the future, I plan to (!!!MAYBE!!!) add HTTPS. Other plans include properly handling every HTTP response code as seen on [the Mozilla HTTP response status codes page](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status), compression, and a config file (prob next idk).

## Under the hood
OpenHTTP is multithreaded, meaning that everytime a request is sent to the server and succesfully connects, a new thread is started on
the CPU to handle the request. Once the server begins to handle a request, it parses the request into an 
`std::map<std::string, std::string>` (for javascript skids, this is equivalent to an object) to seperate the header into key value pairs
for future use (e.g. `"Range: bytes=0-100"` turns into `std::pair<std::string, std::string> whatever = {"Range":"bytes=0-100"};`.
Again, for the javascript skids this is equivalent to `var whatever = {"Range":"bytes=0-100"};`), after this is processes the map by
fetching the file (either using `std::string FetchResource(std::string path)` or `std::vector<unsigned char>
FetchResourceRanged(std::string path, std::streamoff begin, std::streamoff end)` depending on the existence of `Range` in the request header, then its finally ready to send!

## How to actually use it
Just put the HTML/JS/CSS files into `www/`, check that its runnning on the right port and IP, then run `./main/sh` to recompile and run the program.

Please report any errors you find in the `issues` forum on this github repo, including the request that was sent to the server before the crash (seen in Request_Log) and any error messages generated in the terminal. If you dont have these, just describe what you were doing in detail.