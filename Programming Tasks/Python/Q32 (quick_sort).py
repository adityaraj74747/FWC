def f(a,l,r):
 if l<r:
  p=partition(a,l,r)
  f(a,l,p-1)
  f(a,p+1,r)
def partition(a,l,r):
 pivot=a[r]
 i=l-1
 for j in range(l,r):
  if a[j]<=pivot:
   i+=1
   a[i],a[j]=a[j],a[i]
 i+=1
 a[i],a[r]=a[r],a[i]
 return i

a=[3,2,5,1]
f(a,0,len(a)-1)
print(a)
