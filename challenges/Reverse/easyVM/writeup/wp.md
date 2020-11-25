### easyVM wp

一道简单的vm题目，题目中06对应mov指令，其后面一个字节对应的是寻址方式；\x09\x00是跳转，后面一个字节是跳转方式；0xC3是ret，0x30是比较cmp，比较结果会影响reg[7]寄存器；0xCC是运算操作码，其后一个字节分别对应寻址方式和运算类型；最后可以得到执行的汇编代码，是一个希尔排序，这个算法连带着密钥都是找的，解密脚本如下：
```python
from numpy import *
def GetReverse(a,n):
	x = 0
	y = 1
	q = n
	p = a
	z = q // p
	while(1 != p and 1 != q):
		t = p
		p = q % p
		q = t

		t = y
		y = x - y * z
		x = t
		z = q // p
	y = y % n
	if(y < 0):
		y += n
	return y
def CheckReverse(a,n):
	p = 2
	while(p*p<n):
		if(a%p == n%p and 0 == a%p):
			return False
		p+=1
	return True
def MatI(m,n):
	rank = len(m)
	mm = [[0 for i in range(0,rank)] for j in range(0,rank)]
	A = [[0 for i in range(0,2*rank)] for j in range(0,rank)]
	T = [0 for i in range(0,2*rank)]
	for i in range(0, rank):
		for j in range(0, rank*2):
			if(j < rank):
				A[i][j] = m[i,j]
			else:
				if(rank == j-i):
					A[i][j] = 1
				else:
					A[i][j] = 0
	for j in range(0, rank):
		for i in range(j, rank):
			if(CheckReverse(A[i][j], n)):
				a_1 = GetReverse(A[i][j], n)
				for k in range(0, rank*2):
					A[i][k] *= a_1
					A[i][k] %= n
					T[k] = A[i][k]
					A[i][k] = A[j][k]
					A[j][k] = T[k]
				break
			if(rank-1 == i):
				return False
		for i in range(0, rank):
			if(i != j):
				t = A[i][j]
				for k in range(0, rank*2):
					A[i][k] -= t * A[j][k]
					A[i][k] %= n
					if(A[i][k]<0):
						A[i][k] += n
	for i in range(0, rank):
		for j in range(0, rank):
			mm[i][j] = A[i][j+rank]
	return mat(mm)


key = list(b'Almost heaven west virginia, blue ridge mountains')
cipher = [  93,179,142,218,101,131,33,190,246,152,152,14,157,0,99,67,229,43,154,218,48,19,233,142,9,124,0,25,197,133,199,142,254,125,248,0,51,231,107,12,131,95,2,112,88,45,83,13,214,102,182,103,61,122,192,6,11,255,60,241,241,69,196,208,196,255,81,241,136,81]
mK = mat(key).reshape(7,7)
#plain = list(b'de1ctf{7h3n_f4r3_u_w3ll_5w337_cr4g13_HILL_wh3r3_0f3n_71m35_1_v3_r0v3d}')
#print(plain)
#mP = mat(plain).reshape(10,7)
#mC = mP*mK%256
#print(mC.reshape(1,70).tolist()[0])
mC = mat(cipher).reshape(10,7)
mKI = MatI(mK,256)
mP = mC*mKI%256
print("".join(list(map(chr,mP.reshape(1,70).tolist()[0]))))
```
最后得出flag为JNCTF{7h3n_f4r3_u_w3ll_5w337_cr4g13_HILL_wh3r3_0ft3n_71m35_1_v3_r0v3d}