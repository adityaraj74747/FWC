def f(n):
 p=0  # previous number
 for i in range(n):
  s=i+p  # sum of current and previous
  print("Sum:",s)
  p=i  # update previous

f(5)
