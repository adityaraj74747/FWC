#include<stdio.h>
int u[100];
void f(int a[],int n){
 int k=0,dup;
 for(int i=0;i<n;i++){
  dup=0;
  for(int j=0;j<k;j++)if(u[j]==a[i]){dup=1;break;}
  if(!dup)u[k++]=a[i];
 }
 for(int i=0;i<k;i++)printf("%d ",u[i]);
}
int main(){
 int a[]={1,2,2,3,1};
 f(a,5);
 return 0;
}
