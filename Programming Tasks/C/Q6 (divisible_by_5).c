#include<stdio.h>
void f(int*x,int n){
 for(int i=0;i<n;i++){
  if(x[i]%5==0)  // check divisible by 5
   printf("%d\n",x[i]);
 }
}
int main(){
 int a[]={10,12,15,17};
 f(a,4);
 return 0;
}
