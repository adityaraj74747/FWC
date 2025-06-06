#include<stdio.h>
void f(int a[],int n){
 for(int i=0;i<n-1;i++)
  for(int j=0;j<n-i-1;j++)
   if(a[j]>a[j+1]){int t=a[j];a[j]=a[j+1];a[j+1]=t;}  // bubble sort
 for(int i=0;i<n;i++)printf("%d ",a[i]);
}
int main(){
 int a[]={3,1,4,2};
 f(a,4);
 return 0;
}
