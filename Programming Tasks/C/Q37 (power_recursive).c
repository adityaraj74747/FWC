#include<stdio.h>
int f(int a,int b){
 if(b==0) return 1;
 return a*f(a,b-1);
}
int main(){
 printf("%d\n",f(2,3));
 return 0;
}
