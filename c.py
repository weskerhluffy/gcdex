n=10
r=0
for i in range(2,n+1):
	a=i*(i-1)
	r+=a
	print("i {} a {} r {}".format(i,a,r))
print(r)
