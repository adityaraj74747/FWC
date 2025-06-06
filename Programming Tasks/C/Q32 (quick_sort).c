#include<stdio.h>
void swap(int *a,int *b){int t=*a;*a=*b;*b=t;}
int partition(int a[],int l,int r){
 int pivot=a[r],i=l-1,j;
 for(j=l;j<r;j++){
  if(a[j]<=pivot){
   i++;
   swap(&a[i],&a[j]);
  }
 }
 i++;
 swap(&a[i],&a[r]);
 return i;
}
void f(int a[],int l,int r){
 if(l<r){
  int p=partition(a,l,r);
  f(a,l,p-1);
  f(a,p+1,r);
 }
}
int main(){
 int a[]={3,2,5,1};
 f(a,0,3);
 for(int i=0;i<4;i++)printf("%d ",a[i]);
 return 0;
}
