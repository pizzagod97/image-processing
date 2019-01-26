#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

# define H 720
# define W 1280
# define flag puts("lol")
# define eq(x) {color[c][i][0]=color[c][i][1]=color[c][i][2]=x;}	
unsigned char color[H][W][3];
unsigned char ncolor[H][W][3]={0};
int count=0;
int w=10;
float sq=0;
int thres=0;
void * gauss(void *n)
{
//This is a 3*3 kernel used for this program
int c = *(int *)n;
for(int i=1;i<W-2;i++)
{
        int x;

	x =  -(color[c-1][i][0] + color[c][i-1][0] + color[c+1][i][0] + color[c][i+1][0] + color[c-1][i-1][0] + color[c-1][i+1][0] + color[c+1][i-1][0] + color[c+1][i+1][0]) + color[c][i][0] * 8;
	if(x>=thres)
	ncolor[c][i][0]= ncolor[c][i][1]= ncolor[c][i][2]=255;
	
}
}

void main(int argc,char **argv)
{
thres = atoi(argv[1]);
//threshold  = atoi(argv[1]);
//printf("%d",threshold);
unsigned char image_data[60];
pthread_t t[H];
int n=open("copyg.ppm",O_RDWR);
unsigned char c;
read(n,image_data,16);
int m=open("copye.ppm",O_RDWR);
write(m,image_data,16);
read(n,(unsigned char *)color,H*W*3);
//memcpy(dcolor,color,H*W*3);

for(int i=1;i<H-3;pthread_create(t+i,NULL,(void *)gauss,(void *)&i),i+=1);   
for(int j=1;j<H-3;pthread_join(t[j],NULL),j+=1);
write(m,(unsigned char*)ncolor,H*W*3);
close(n);
close(m);

}
