#include<stdio.h>
#include<string.h>
void f(char*s){
 int l=strlen(s);
 for(int i=0;i<l/2;i++)
  if(s[i]!=s[l-1-i]){printf("No\n");return;}
 printf("Yes\n");
}
int main(){
 f("madam");
 return 0;
}
