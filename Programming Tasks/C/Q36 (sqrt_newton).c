#include<stdio.h>
int main(){
 double x=25,r=x;
 for(int i=0;i<10;i++)
  r=(r+x/r)/2;
 printf("%f\n",r);
 return 0;
}
