#include<stdio.h>
#include<unistd.h>
int main()
{
printf(“Before\n”);
execl(“/bin/ps”,”ps”,NULL);
printf(After\n”);
} 