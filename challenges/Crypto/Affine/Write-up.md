直接用记事本打开发现里面存在一个.txt文本，因此将起改为.zip文件，打开里面的文本文件发现

如下：

根据文本的名字发现：Affine Cipher，你可以发现这是一个仿射密码，百度其加密原理，进行解密



解密文本：

```pythn
def get(a, b):
    if b == 0:
        return 1, 0
    else:
        k = a // b
        remainder = a % b
        x1, y1 = get(b, remainder)
        x, y = y1, x1 - k * y1
    return x, y
s = input("请输入解密字符：").upper()
a = int(input("请输入a："))
b = int(input("请输入b："))
x, y = get(a, 26)
a1 = x % 26
l = len(s)
for i in range(l):
    cipher = a1 * (ord(s[i]) - 65 - b) % 26
    res = chr(cipher + 65)
    print(res, end='')
```

flag

```
jnctf{it's really ez}
```