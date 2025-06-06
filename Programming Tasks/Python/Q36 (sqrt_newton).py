def f(x):
 r=x
 for _ in range(10):
  r=(r+x/r)/2
 print(r)

f(25)
