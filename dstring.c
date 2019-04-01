#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/types.h>

int main (int argc,char **argv)

{

FILE *fptr = fopen("process.txt","r");
char inp[100];
int x=0;
while(fgets(inp,100,fptr)!=NULL)
{
	x++;
	if(x % 3 ==0)
		{printf("%s\n",inp);}
}
fclose(fptr);
wait(NULL);
}

