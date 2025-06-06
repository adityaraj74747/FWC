#include<stdio.h>
int main(){
 int a=1,b=10,s=0;
 for(int x=a;x<=b;x++)
  if(x%2!=0) s+=x;
 printf("%d\n",s);
 return 0;
}
