#include"global.hpp"

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

// TODO：这里为什么写这么复杂?
char getch() {
    char buf = 0;
    struct termios old = {0};
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");

    old.c_lflag &= ~ICANON; // 非标准模式
    old.c_lflag &= ~ECHO; //不回显输入字符
    old.c_cc[VMIN] = 1;  // 非标准模式下读的最小字符数
    old.c_cc[VTIME] = 0; // 非标准模式下读时的延时

    if(tcsetattr(0, TCSANOW, &old) < 0)  // 改变立刻发生
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

void getKeypressDownInput(char &c) {
    c = getch();
}


void cleanScreen() {
    system("clear");
}