#include<stdio.h>
void f(int n){
 int p=0;  // previous number
 for(int i=0;i<n;i++){
  int s=i+p;  // sum of current and previous
  printf("Sum: %d\n",s);
  p=i;  // update previous
 }
}
int main(){
 f(5);
 return 0;
}
