def f(s,n):
 print(s[n:])  # remove first n chars

f("hello",2)
#include<stdio.h>
void f(char*s,int n){
 printf("%s\n",s+n);  // remove first n chars
}
int main(){
 f("hello",2);
 return 0;
}
