#include<stdio.h>
void f(int n){
 int a=0,b=1,t;
 while(a<=n){
  printf("%d\n",a);
  t=a+b; a=b; b=t;  // next term
 }
}
int main(){
 f(20);
 return 0;
}
