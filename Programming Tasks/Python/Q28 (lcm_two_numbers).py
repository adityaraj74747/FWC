def f(a,b):
 g=lambda x,y: x if y==0 else g(y,x%y)
 print(a*b//g(a,b))  # lcm

f(4,6)
