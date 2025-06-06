#include<stdio.h>
#include<string.h>
void f(char*s,char*w){
 int c=0;
 int l=strlen(w);
 for(int i=0;s[i]!='\0';i++){
  if(strncmp(s+i,w,l)==0)  // check match
   c++;
 }
 printf("%d\n",c);
}
int main(){
 f("abcabcabc","abc");
 return 0;
}
