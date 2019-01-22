from eulerlib import Divisors
from math import gcd

divi=Divisors()

n=1
r=0
for i in range(1,n):
	for j in range(i+1,n+1):
		r+=gcd(i,j)
print(r)


k=1
p=7
r=0
for l in range(k+1):
	for d in range(l+1):
		r+=(p**d)*divi.phi(p**(l-d))
print(r)
