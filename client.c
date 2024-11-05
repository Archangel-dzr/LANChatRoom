/*
 *  ┌─────────────────────────────────────────────────────────────┐
 *  │┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐│
 *  ││Esc│!1 │@2 │#3 │$4 │%5 │^6 │&7 │*8 │(9 │)0 │_- │+= │|\ │`~ ││
 *  │├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤│
 *  ││ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{[ │}] │ BS  ││
 *  │├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤│
 *  ││ Ctrl │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│ Enter  ││
 *  │├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤│
 *  ││ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│Shift │Fn ││
 *  │└─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴──┬┴───┴┬──┴┬─────┴───┘│
 *  │      │Fn │ Alt │         Space         │ Alt │Win│   HHKB   │
 *  │      └───┴─────┴───────────────────────┴─────┴───┘          │
 *  └─────────────────────────────────────────────────────────────┘
 * 
 * @Author: Archangel 781446156@qq.com
 * @Date: 2024-11-04 20:12:37
 * @LastEditTime: 2024-11-05 09:44:36
 * @LastEditors: Archangel 781446156@qq.com
 * @Description: 
 * @FilePath: \LANChatRoom\client.c
 * Copyright (c) 2024 by Archangel email: 781446156@qq.com, All Rights Reserved. 
 */

#include "client.h"

int main()
{
    pthread_t thread;             // pthread_t 线程，gcc编译时需加上-lpthread
    struct sockaddr_in serv_addr; // struct sockaddr_in
    char buf[BUFFSIZE], temp[BUFFSIZE];

    // 初始化服务端地址结构
    bzero(&serv_addr, sizeof(struct sockaddr_in)); // bzero 清零
    serv_addr.sin_family = AF_INET;                // sin_family   AF_INET
    serv_addr.sin_port = htons(PORT);              // sin_port     htons(PORT)
    inet_pton(HOST_IP, &serv_addr.sin_addr);       // inet_pton
    // 创建客户端套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket 创建套接字
    if (sockfd < 0)
    {
        perror("套接字操作失败");
        exit(-1);
    }
    // 与服务器建立连接
    printf("连接中... \n");
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("连接服务器失败");
        exit(-2);
    }

    printf("输入 \"login\" 登录\n");
    printf("输入 \"register\" 建立账户\n");
    printf("输入 \"quit\" 退出聊天系统\n");
    printf("输入 \"help\" 获取帮助信息\n");
    printf("--------------------------------------------------------------------------------\n");

    /* === 从此处开始 程序分做两个线程 === */
    // 创建发送消息的线程，调用发送消息的函数snd
    pthread_create(&thread, NULL, (void *)(&snd), NULL); // pthread_create
    // 接收消息的线程
    while (1)
    {
        int len;
        if ((len = read(sockfd, buf, BUFFSIZE)) > 0) // read 读取通信套接字
        {
            write(1, buf, len); //1：标准输出
            printf("\n");
        }
    }
    return 0;
}

/*发送消息的函数*/
void snd()
{
    char buf[BUFFSIZE];
    while (1)
    {
        fgets(buf, BUFFSIZE, stdin);
        if (strcmp(buf, "help\n") == 0)
        {
            get_help();
            continue;
        }
        if (strcmp(buf, "\n") != 0)
            write(sockfd, buf, strlen(buf));
        if (strcmp(buf, "quit\n") == 0) // 注意此处的\n
            exit(0);
    }
}

/*获取帮助信息*/
void get_help()
{
    printf("命令介绍:\n");
    printf("\t'ls -users':\t\t显示所有在线用户\n");
    printf("\t'ls -chatrooms':\t显示所有聊天室\n");
    printf("\t'ls -inrmusr':\t\t显示你所在聊天室的所有在线用户\n");
    printf("\t'send username msg':\t向名为 'username' 的用户发送消息，msg:消息内容\n");
    printf("\t'join chatroom passwd':\t加入名为 'chatroom' 的聊天室，密码为 'passwd'\n");
    printf("\t'create chatrname passwd':\t创建名为 'chatrname' 的聊天室，密码为 'passwd'\n");
    printf("\t'chgpsw passwd':\t\t将你的密码更改为 'passwd'\n");
    printf("\t'send -chatroom msg':\t向聊天室发送消息\n");
    printf("\t'exit':\t\t\t退出你所加入的聊天室\n");
    printf("\t'send -all msg':\t向所有在线用户发送消息\n");
    printf("\t'login':\t\t登录聊天系统\n");
    printf("\t'register':\t\t创建一个账户\n");
    printf("\t'quit':\t\t\t退出聊天系统\n");
    printf("\t'help':\t\t\t获取更多帮助信息\n\n");
    printf("注意:\n");
    printf("\t1. 输入命令时，末尾请不要输入空格，输入命令时请用英文输入法，不要使用中文输入法。\n");
    printf("--------------------------------------------------------------------------------\n");
}

