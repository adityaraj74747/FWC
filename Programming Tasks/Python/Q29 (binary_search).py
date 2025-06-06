def f(a,x):
 l,r=0,len(a)-1
 while l<=r:
  m=(l+r)//2
  if a[m]==x: return m
  elif a[m]<x: l=m+1
  else: r=m-1
 return -1

print(f([1,2,3,4,5],3))
