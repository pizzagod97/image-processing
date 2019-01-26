#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>

# define H 720
# define W 1280
# define flag puts("lol")
unsigned char color[H][W][3];
unsigned char ncolor[H][W][3]={0};
unsigned char count=0;
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
void main(int argc,char **argv)
{

unsigned char image_data[60];
pthread_t t[H];
int n=open("copy.ppm",O_RDWR);
unsigned char c;
read(n,image_data,16);
int m=open("copyg.ppm",O_RDWR);
write(m,image_data,16);
read(n,(unsigned char *)color,H*W*3);


for(int x=0;x<atoi(argv[1]);x++)
{
for(int i=2;i<H-4;pthread_create(t+i,NULL,(void *)gauss,(void *)&i),pthread_join(t[i],NULL),i++);   
}

write(m,(unsigned char*)ncolor,H*W*3);
close(n);
close(m);

}
