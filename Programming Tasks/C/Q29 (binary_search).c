#include<stdio.h>
int f(int a[],int n,int x){
 int l=0,r=n-1,m;
 while(l<=r){
  m=(l+r)/2;
  if(a[m]==x) return m;
  else if(a[m]<x) l=m+1;
  else r=m-1;
 }
 return -1;
}
int main(){
 int a[]={1,2,3,4,5};
 printf("%d\n",f(a,5,3));
 return 0;
}
