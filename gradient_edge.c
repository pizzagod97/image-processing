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
int threshold=255;
int w=10;
float sq=0;
int thres=0;
void * gauss(void *n)
{
//This is a 3*3 kernel used for this program
int c = *(int *)n;
for(int i=1;i<W-2;i++)
{

	float x,y;
	x =-color[c-1][i-1][0] - w*color[c][i-1][0] -color[c+1][i-1][0] + color[c+1][i+1][0] + w*color[c][i+1][0] + color[c+1][i+1][0];
	y = color[c-1][i-1][0] + w*color[c-1][i][0] + color[c-1][i+1][0] - color[c+1][i-1][0] - w*color[c+1][i][0] - color[c+1][i+1][0];
	float arc = atan2f(y,x)*57.2958;

	sq = sqrt(x*x + y*y);
	if(arc<0)
         arc+=360;



if((thres < sq) && (sq<(3*thres)))
{
if((arc<22.5) || (arc > 337.5) || ((arc>157.5) && (arc<202.5)) )
{
if((color[c][i-1][0] <= color[c][i][0]) && (color[c][i+1][0] <= color[c][i][0]))
ncolor[c][i][0]=ncolor[c][i][1]=ncolor[c][i][2]=sq;
}
//if((color[c-1][i][0] <= color[c][i][0]) && (color[c+1][i][0] <= color[c][i][0]))
//ncolor[c][i][0]=ncolor[c][i][1]=ncolor[c][i][2]=threshold;

if((arc>22.5) && (arc < 67.5) || ((arc>202.5) && (arc<247.5)) )
{
	
	if((color[c-1][i+1][0] <= color[c][i][0]) && (color[c+1][i-1][0] <= color[c][i][0]))
        ncolor[c][i][0]=ncolor[c][i][1]=ncolor[c][i][2]=sq;
}


if((arc>112.5) && (arc < 157.5) || ((arc>292.5) && (arc<337.5)) )
{
	        
	        if((color[c-1][i-1][0] <= color[c][i][0]) && (color[c+1][i+1][0] <= color[c][i][0]))
	        ncolor[c][i][0]=ncolor[c][i][1]=ncolor[c][i][2]=sq;
}


 if((67.5<arc<112.5) || (247.5<arc<292.5 ))
{
if((color[c-1][i][0] <= color[c][i][0]) && (color[c+1][i][0] <= color[c][i][0]))
ncolor[c][i][0]=ncolor[c][i][1]=ncolor[c][i][2]=sq;
}


}
//for difference of gaussians
//for(int z=0;z<3;z++)
//dcolor[c][i][z] = dcolor[c][i][z] - color[c][i][z];
}
}

void main(int argc,char **argv)
{
thres = atoi(argv[1]);
//threshold  = atoi(argv[1]);
//printf("%d",threshold);
unsigned char image_data[60];
pthread_t t[H];
int n=open("copy.ppm",O_RDWR);
unsigned char c;
read(n,image_data,60);
int m=open("copye.ppm",O_RDWR);
write(m,image_data,60);
read(n,(unsigned char *)color,H*W*3);
//memcpy(dcolor,color,H*W*3);

for(int i=1;i<H-3;pthread_create(t+i,NULL,(void *)gauss,(void *)&i),i+=1);   
for(int j=1;j<H-3;pthread_join(t[j],NULL),j+=1);

write(m,(unsigned char*)ncolor,H*W*3);
close(n);
close(m);

}
