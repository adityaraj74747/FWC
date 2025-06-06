#include<stdio.h>
#include<math.h>
int p(int x){
 if(x<2)return 0;
 for(int i=2;i<=sqrt(x);i++)
  if(x%i==0)return 0;
 return 1;
}
int main(){
 int a=1,b=10,s=0;
 for(int x=a;x<=b;x++)
  if(p(x)) s+=x;
 printf("%d\n",s);
 return 0;
}
