#include<stdio.h>
void f(int a[],int b[],int n1,int n2){
 for(int i=0;i<n1;i++)
  for(int j=0;j<n2;j++)
   if(a[i]==b[j]){printf("%d ",a[i]);break;}
}
int main(){
 int a[]={1,2,3},b[]={2,3,4};
 f(a,b,3,3);
 return 0;
}
