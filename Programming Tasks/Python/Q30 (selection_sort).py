def f(a):
 n=len(a)
 for i in range(n):
  min_i=i
  for j in range(i+1,n):
   if a[j]<a[min_i]: min_i=j
  a[i],a[min_i]=a[min_i],a[i]
 print(a)

f([4,2,3,1])
