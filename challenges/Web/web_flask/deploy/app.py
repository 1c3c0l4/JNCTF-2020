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
            u = re.search(r'http://(\d{1,3})\.\d{1,3}\.\d{1,3}\.\d{1,3}',request.args['u'])
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

if __name__ == '__main__':
    app.run()