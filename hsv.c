#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

# define H 183
# define W 275
# define C 3
# define HEAD 15

char im[W][H][C];


void hsv()
{
float r,g,b,max,min,h,s;
for(int i=0;i<W;i++)
for(int j=0;j<H;j++)
{
/////////////////////////////////calculating r',g',b' and max and min and Hue
r=(float)(im[i][j][0])/255;
g=(float)(im[i][j][1])/255;
b=(float)(im[i][j][2])/255;
if((r>=g) && (r>=b))
{
max=r;
if(g>b)
min=b;
else
min=g;
h=60*((int)(((g-b)/max-min))%6);
}
else if((g>=r) && (g>=b))
{
max=g;
if(r>b)
min=b;
else
min=r;
h=60*(((b-r)/max-min)+2);
}
else if((b>=r) && (b>=g))
{
max=b;
if(r>g)
min=g;
else
min=r;
h=60*(((r-g)/max-min)+4);
}
/////////////////////////////////////// saturation and value
s=(max-min)/max;
//printf("h = %f s= %f v=%f \n",h,s,max);
im[i][j][0]=h;
im[i][j][1]=s;
im[i][j][2]=max;
}
}



void main(int argc,char **argv)
{
int fd = open(argv[1],O_RDONLY);
int nd = open("hsv.ppm",O_WRONLY);
char header[HEAD];
read(fd,header,HEAD);
write(nd,header,HEAD);
printf("%s",header);
read(fd,im,H*W*C);
hsv();
write(nd,im,H*W*C);
}
