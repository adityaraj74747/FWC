def f(n):
 s=0
 while n:
  s+=n%10  # get digit
  n//=10
 print(s)

f(123)
