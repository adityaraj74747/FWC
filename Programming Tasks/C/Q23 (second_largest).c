#include<stdio.h>
void f(int a[],int n){
 for(int i=0;i<n-1;i++)
  for(int j=0;j<n-i-1;j++)
   if(a[j]>a[j+1]){int t=a[j];a[j]=a[j+1];a[j+1]=t;}  // bubble sort
 printf("%d\n",a[n-2]);  // second last
}
int main(){
 int a[]={1,5,2,4};
 f(a,4);
 return 0;
}
