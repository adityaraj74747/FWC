#include<stdio.h>
void f(int a[],int n){
 int i,j,min_i,t;
 for(i=0;i<n-1;i++){
  min_i=i;
  for(j=i+1;j<n;j++)
   if(a[j]<a[min_i]) min_i=j;
  t=a[i];a[i]=a[min_i];a[min_i]=t;
 }
 for(i=0;i<n;i++)printf("%d ",a[i]);
}
int main(){
 int a[]={4,2,3,1};
 f(a,4);
 return 0;
}
