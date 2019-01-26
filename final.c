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
int thres=0;
unsigned char color[H][W][3];
unsigned char ncolor[H][W][3];
int place=0;
void * grey(void *n)
{
place=(H/4)*(*(int*)n);
// 0.21 R + 0.72 G + 0.07 B this is the luminosity method to convert to greyscale
//for(int i=0,c = *(int*)n;i<W;color[c][i][0]=color[c][i][1]=color[c][i][2]= (color[c][i][0]*0.21 + color[c][i][1]*0.72+ color[c][i][2]*0.07),i++);
for(int c=(H/4)*(*(int*)n-1);c<place;c++)
for(int i=0;i<W;color[c][i][0]=color[c][i][1]=color[c][i][2]= (color[c][i][0] + color[c][i][1]+ color[c][i][2])/3,i++);
}

void * gauss(void *n)
{
unsigned char temp;
//This is a 5*5 kernel used for this program
int c = *((int *)n);
for(int i=2;i<W-4;i++)
for(int z=0;z<3;z++)
{
//ncolor[c][i][z]=(color[c-1][i-1][z]+ color[c-1][i][z] + color[c-1][i+1][z]+ color[c][i-1][z]+ color[c][i+1][z]+ color[c][i][z]+ color[c+1][i-1][z]+ color[c][i][z]+ color[c+1][i+1][z])/9;
ncolor[c][i][z]=(color[c-2][i-2][z]+ color[c-2][i-1][z] + color[c-2][i][z]+ color[c-2][i+1][z]+ color[c-2][i+2][z]+ color[c-1][i-2][z]+ color[c-1][i-1][z]+ color[c-1][i][z]+ color[c-1][i+1][z] + color[c-1][i+2][z] + color[c][i-2][z] + color[c][i-1][z] + color[c][i][z] +  color[c][i+1][z] + color[c][i+2][z] + color[c-1][i-2][z] + color[c-1][i-1][z] + color[c-1][i][z] + color[c-1][i+1][z] + color[c-1][i+2][z] + color[c-2][i-2][z] + color[c-2][i-1][z] +  color[c-2][i][z] +  color[c-2][i+1][z] +  color[c-2][i+2][z])/25;}
}

void * edge(void *n)
{
//This is a 5*5 kernel used for this program  hence centre is 24 for 3*3 , its 8
int c = *(int *)n;
for(int i=2;i<W-4;i++)
{
int x;
x =  -(color[c-2][i-2][0] + color[c-2][i-1][0] + color[c-2][i][0] +color[c-2][i+1][0] + color[c-2][i+2][0] + color[c-1][i-2][0] + color[c-1][i-1][0] + color[c-2][i][0] +color[c-1][i+1][0] + color[c-1][i+2][0]  + color[c][i-2][0] + color[c][i-1][0] +color[c][i+1][0] + color[c][i+2][0] + color[c+1][i-2][0] + color[c+1][i-1][0] + color[c+1][i][0] +color[c+1][i+1][0] + color[c+1][i+2][0] + color[c+2][i-2][0] + color[c+2][i-1][0] + color[c+2][i][0] +color[c+2][i+1][0] + color[c+2][i+2][0]) + color[c][i][0]* 24;
if(x>thres)
ncolor[c][i][0]= ncolor[c][i][1]= ncolor[c][i][2]=x;
}
}


void main(int argc,char **argv)
{
thres = atoi(argv[3]);
unsigned char image_data[60];
pthread_t t[H];
int n=open(argv[1],O_RDWR);
unsigned char c;
read(n,image_data,16);
int m=open("copy.ppm",O_RDWR);
write(m,image_data,16);
read(n,color,H*W*3);
int i=0,j=0;
for(i=1;i<=4;pthread_create(t+i,NULL,(void *)grey,(void *)&(i)),i++);
for(i=1;i<=4;pthread_detach(t[i]),i++);
for(i=0;i<atoi(argv[2]);i++)
for(i=0;i<H;pthread_create(t+i,NULL,(void *)gauss,(void *)&i),pthread_join(t[i],NULL),i++);
memcpy(color,ncolor,H*W*3);
memset(ncolor,0,H*W*3);
for(i=2;i<H-4;pthread_create(t+i,NULL,(void *)edge,(void *)&i),pthread_join(t[i],NULL),i++);
write(m,ncolor,H*W*3);
close(n);
close(m);
//system("xdg-open copy.ppm");
}
