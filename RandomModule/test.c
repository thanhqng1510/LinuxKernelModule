#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
 
int main(){
   int num;
   int ret, fd;

   fd = open("/dev/Random", O_RDWR);           
   if (fd < 0){
      perror("Failed to open the device...");
      return errno;
   }
   ret = read(fd, &num, sizeof(num)); 
   if(ret < 0){
       printf("Failed to read\n");
       return errno;
   }
   else{
       printf("Random number is %d\n",num);
   }
   return 0;
}
