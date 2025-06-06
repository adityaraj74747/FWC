#include<stdio.h>
int g(int a,int b){return b==0?a:g(b,a%b);}
int main(){
 int a=4,b=6;
 printf("%d\n",a*b/g(a,b));  // lcm
 return 0;
}
