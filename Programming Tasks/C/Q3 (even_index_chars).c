#include<stdio.h>
void f(char*s){
 for(int i=0;s[i]!='\0';i+=2){  // check even index
  printf("%c\n",s[i]);
 }
}
int main(){
 f("hello");
 return 0;
}
