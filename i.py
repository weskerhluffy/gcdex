from eulerlib import Divisors
from math import gcd

N=1000001

divobj=Divisors(N)

def funcion(n):
	global d
	divis=divobj.divisors(n)
	r=0
#	print("divis {}".format(divis))
	for d in divis[:]:
		r+=d*divobj.phi(n//d)
#		print("d {} phi {} es {}".format(d,n//d,divobj.phi(n//d)))
	return int(r)

for i in range(1,N+1):
#	print("f[{}]={} phi {}".format(i,funcion(i),int(divobj.phi(i))))
	print("f[{}]={}".format(i,funcion(i)))
