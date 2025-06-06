#include<stdio.h>
void merge(int a[],int l,int m,int r){
 int n1=m-l+1,n2=r-m,i,j,k;
 int L[n1],R[n2];
 for(i=0;i<n1;i++)L[i]=a[l+i];
 for(j=0;j<n2;j++)R[j]=a[m+1+j];
 i=j=0;k=l;
 while(i<n1 && j<n2){
  if(L[i]<=R[j]) a[k++]=L[i++];
  else a[k++]=R[j++];
 }
 while(i<n1) a[k++]=L[i++];
 while(j<n2) a[k++]=R[j++];
}
void f(int a[],int l,int r){
 if(l<r){
  int m=l+(r-l)/2;
  f(a,l,m);
  f(a,m+1,r);
  merge(a,l,m,r);
 }
}
int main(){
 int a[]={4,3,1,2};
 f(a,0,3);
 for(int i=0;i<4;i++)printf("%d ",a[i]);
 return 0;
}
