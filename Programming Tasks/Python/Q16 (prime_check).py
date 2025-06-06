def f(n):
 if n<2: print("No"); return
 for i in range(2,n):
  if n%i==0: print("No"); return  # not prime
 print("Yes")

f(7)
