#include<stdio.h>
int main(){
 int n=123,s=0;
 while(n){s+=n%10;n/=10;}  // get digit
 printf("%d\n",s);
 return 0;
}
