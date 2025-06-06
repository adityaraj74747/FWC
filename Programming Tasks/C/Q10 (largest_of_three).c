#include<stdio.h>
int main(){
 int a=3,b=7,c=5,m;
 m=a;
 if(b>m)m=b;
 if(c>m)m=c;
 printf("%d\n",m);  // print max
 return 0;
}
