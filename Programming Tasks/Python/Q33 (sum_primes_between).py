def f(a,b):
 def p(x):
  if x<2:return False
  for i in range(2,int(x**0.5)+1):
   if x%i==0:return False
  return True
 s=0
 for x in range(a,b+1):
  if p(x): s+=x
 print(s)

f(1,10)
