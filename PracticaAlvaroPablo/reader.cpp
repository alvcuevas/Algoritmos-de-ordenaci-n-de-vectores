#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_BUF 1024

using namespace std;

int main(int argc, char** argv)
{          
	int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    while(buf[0] != 'q'){
        /* open, read, and display the message from the FIFO */
        fd = open(myfifo, O_RDONLY);
        read(fd, buf, MAX_BUF);
        
		if(fd>0)printf("%s\n", buf);
        
        close(fd);
    }
	
    return 0;
}
