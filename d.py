n=10
d=3
r=0
for i in range(n+1):
	r+=(i//d)*(i//d-1)//2
print(r)
