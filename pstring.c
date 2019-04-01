#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/types.h>

it main()

{
	
char buf[100] ="./dstring";

execlp("/user/bin/xterm","xterm","-hold","-e","./dstring",NULL);

wait(NULL);

return 0;
}