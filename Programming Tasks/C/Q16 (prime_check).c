#include<stdio.h>
void f(int n){
 if(n<2){printf("No\n");return;}
 for(int i=2;i<n;i++)
  if(n%i==0){printf("No\n");return;}  // not prime
 printf("Yes\n");
}
int main(){
 f(7);
 return 0;
}
