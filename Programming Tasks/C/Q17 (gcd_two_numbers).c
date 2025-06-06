#include<stdio.h>
int f(int a,int b){
 while(b){int t=b;b=a%b;a=t;}  // Euclidean
 return a;
}
int main(){
 printf("%d\n",f(12,18));
 return 0;
}
