```python
def decryption():
    str_list_encry = ['f', 'j', 'y', 'p', 'b', '{', 'e', 'p', "'", 'o', ' ', 'n', 'a', 'w', 'h', 'h', 'u', ' ', 'a', 'v', '}']
    k = 22
    str_list_decry = str_list_encry
    i = 0
    while i < len(str_list_encry):
        if ord(str_list_encry[i]) >= 97 and ord(str_list_encry[i]) <= 122:
            if ord(str_list_encry[i]) >= 97 + k:
                str_list_decry[i] = chr(ord(str_list_encry[i]) - k)
            else:
                str_list_decry[i] = chr(ord(str_list_encry[i]) + 26 - k)
        i = i + 1
    ans = ''
    for i in str_list_decry:
        ans += i
    print(ans)
if __name__ == '__main__':
    decryption()
```

flag

```
jnctf{it's really ez}
```

