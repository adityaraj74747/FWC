#include<stdio.h>
void f(int*x,int n){
 if(x[0]==x[n-1])  // compare first and last
  printf("Yes\n");
 else
  printf("No\n");
}
int main(){
 int a[]={1,2,3,1};
 f(a,4);
 return 0;
}
