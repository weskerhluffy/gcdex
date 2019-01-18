from eulerlib import Divisors
from functools import reduce

d=Divisors()
#print(d.phi(123))
n=10

i=1
r=0
for i in range(1,n+1):
	phi=d.phi(i)
	ci=n//i
	print("i {} ci {} phi {}".format(i,ci,phi))
	r+=phi*(ci*(ci-1))//2
print(r)

n=200000
i=1
r=0
while(i<=n):
	la=n//(n//i)
	ci=n//i
	print("i {} ci {} la {} rang {}".format(i,ci,la,list(range(i,la+1))))
	suma_phi=reduce(lambda x,y:x+d.phi(y),range(i,la+1),0)
	print("phis {} {}".format(list(range(i,la+1)), list(map(d.phi,range(i,la+1)))))
	print("sum phi {}".format(suma_phi))
	r+=((ci*(ci-1))//2)*suma_phi
	i=la+1

print(r)

n=10
r=0
for i in range(n+1):
	phi=d.phi(i)
	r+=phi
	print("para i {} phi {} ac {}".format(i,phi,r))
print(r)
