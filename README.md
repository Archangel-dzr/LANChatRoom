# LANChatRoom 局域网聊天室
## English Version
Client refers to the client-side executable file.  
	Server refers to the server-side executable file.  	
	The client source code is composed of Client.c and Client.h.  
	The server source code is composed of Server.c and Server.h.  
	users.txt is used on the server side to store user account information. Running the Client file without users.txt will result in a segmentation fault.  
### Overview:
This is a Local Area Network Chat Room (LANChatRoom) based on C language and network programming, divided into a server and client, allowing multiple clients to be online simultaneously.  
#### Client Section:
Uses sockets to establish a connection with the server. A socket is created using the socket() function, and the connect() function is used to connect to the server.  
Utilizes the POSIX thread library (pthread) to create and manage threads. One thread is created for sending messages, and another for receiving messages from the server.  
Communicates over the network, using inet_pton() to convert IP addresses to network byte order, and read() and write() for data reception and transmission.  
Outputs information and prompts using printf(), and reads user input from standard input using fgets().  
Compares user-entered commands using the strcmp() function and processes strings using functions like strcpy().  
Outputs error information using the perror() function for debugging and error diagnosis during runtime.  
Uses the struct sockaddr_in structure to handle address information, including IP addresses and port numbers.  
Implements a simple command protocol, allowing users to interact with the chat system by entering specific commands, enabling functions such as login, registration, message sending, chat room creation and entry, and viewing online user information.  
#### Server Section:
Implements network communication using the POSIX socket API, including socket creation, binding, listening, and accepting connections.  
	Uses the pthread library to create threads, allowing simultaneous handling of multiple client connections and ensuring the server can process requests from multiple users in parallel.  
	Implements user registration and login functionality through usernames and passwords, with the server maintaining user information and processing corresponding commands.  
	Uses file read and write operations (such as fopen, fscanf, fprintf, etc.) to save and load user information, ensuring the persistence of user data.  
	By parsing user-entered commands, the server can identify the operations users wish to perform and respond accordingly.  
  
## 中文版本
 Client为客户端可执行文件  
  Server为服务器端可执行文件  
  客户端源码为Client.c Client.h  
  服务器源码为Server.c Server.h  
  users.txt用于服务器端存放用户账户信息，缺少users.txt运行Client文件会导致段错误。  
### 简介:
这是一个基于c语言和网络编程的局域网聊天室（LANChatRoom），分为服务端和客户端，可同时在线多个客户端。
#### 客户端:
 客户端部分使用套接字来建立与服务器的连接。通过 socket() 函数创建套接字，使用 connect() 函数连接到服务器。  
            使用POSIX线程库（pthread）来创建和管理线程。创建一个线程用于发送消息，另一个线程用于接收来自服务器的消息。  
            通过网络进行通信，使用 inet_pton() 将IP地址转换为网络字节顺序，使用 read() 和 write() 进行数据的接收与发送。  
            使用 printf() 输出信息和提示，使用 fgets() 从标准输入读取用户输入  
            使用 strcmp() 函数比较用户输入的命令，并通过 strcpy() 等函数来处理字符串。  
            使用 perror() 函数输出错误信息，以便于调试和运行期间的错误诊断。  
            使用 struct sockaddr_in 结构体来处理地址信息，包含IP地址和端口号等。  
            实现简单的命令协议，允许用户通过输入特定命令与聊天系统进行交互，实现登录、注册、发送消息，聊天室创建与进入，在线用户信息查看等功能
#### 服务器端:
 服务器端部分使用 POSIX 套接字 API 实现网络通信，包括创建套接字、绑定、监听和接受连接等操作。  
              使用 pthread 库创建线程，以便同时处理多个客户端连接，确保服务器能够并行处理来自多个用户的请求。  
              通过用户名和密码实现用户的注册和登录功能，服务器维护用户的信息并处理相应的命令。  
              使用文件读写操作（如 fopen、fscanf、fprintf 等）来保存和加载用户信息，确保用户数据的持久化。  
              通过解析用户输入的命令，服务器能够识别用户希望执行的操作并作出相应的处理。  
