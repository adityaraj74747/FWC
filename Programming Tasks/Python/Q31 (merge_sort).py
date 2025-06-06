def f(a):
 if len(a)>1:
  mid=len(a)//2
  L=a[:mid]
  R=a[mid:]
  f(L)
  f(R)
  i=j=k=0
  while i<len(L) and j<len(R):
   if L[i]<R[j]:
    a[k]=L[i]
    i+=1
   else:
    a[k]=R[j]
    j+=1
   k+=1
  while i<len(L):
   a[k]=L[i]
   i+=1
   k+=1
  while j<len(R):
   a[k]=R[j]
   j+=1
   k+=1

a=[4,3,1,2]
f(a)
print(a)
