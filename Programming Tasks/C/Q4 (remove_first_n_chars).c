#include<stdio.h>
void f(char*s,int n){
 printf("%s\n",s+n);  // remove first n chars
}
int main(){
 f("hello",2);
 return 0;
}
