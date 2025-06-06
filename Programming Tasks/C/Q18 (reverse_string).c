#include<stdio.h>
#include<string.h>
void f(char*s){
 for(int i=strlen(s)-1;i>=0;i--)  // reverse
  printf("%c",s[i]);
 printf("\n");
}
int main(){
 f("abc");
 return 0;
}
