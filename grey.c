#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
# define flag puts("fine")
#define H  720
#define W 1280
unsigned char color[H][W][3];
void * grey(void *n)
{
int place=0;
int j=*(int *)n;
place=(H/4)*j;
printf("%d",place);
// 0.21 R + 0.72 G + 0.07 B this is the luminosity method to convert to greyscale
//for(int i=0,c = *(int*)n;i<W;color[c][i][0]=color[c][i][1]=color[c][i][2]= (color[c][i][0]*0.21 + color[c][i][1]*0.72+ color[c][i][2]*0.07),i++);
for(int c=(H/4)*(*(int*)n-1);c<place;c++)
for(int i=0;i<W;color[c][i][0]=color[c][i][1]=color[c][i][2]= (color[c][i][0] + color[c][i][1]+ color[c][i][2])/3,i++);
}

void main(int argc,char **argv)
{
unsigned char image_data[60];
pthread_t t[4];
int n=open(argv[1],O_RDWR);
unsigned char c;
read(n,image_data,16);
int m=open("copy.ppm",O_RDWR);
write(m,image_data,16);
read(n,color,H*W*3);
int i=0,j=0;
for(i=1;i<=4;pthread_create(t+i,NULL,(void *)grey,(void *)&(i)),i++);
for(i=1;i<=4;pthread_detach(t[i]),i++);
write(m,color,H*W*3);
close(n);
close(m);
//system("xdg-open copy.ppm");
}
