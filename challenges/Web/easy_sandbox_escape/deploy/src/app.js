var fs = require("fs");
const { POINT_CONVERSION_UNCOMPRESSED } = require('constants');
const express = require('express');
const app = express();
const {VM} = require('vm2');

blacklist = ['function', 'Error', 'prototype', 'process', 'constructor', 'return',
                'Buffer', 'try', 'catch', 'require', 'exec']

function filter(unsafe) { // This filter can be used for both array and string
    str = unsafe.toString();
    for ( b in blacklist){
        if (str.indexOf(blacklist[b])!=-1){
            console.log(blacklist[b])
            console.log(str)
            return false;
        }
    }
    if (unsafe instanceof Array){
        return unsafe.join('');
    }
    else{
        return unsafe;
    }
}

app.get('/',(req,res)=>{
    if (!req.query['code']){
        res.send("This is a simple test for a filter, the code you input will run in a sandbox.<br>?code=");
    }
    else{
        unsafe = req.query['code'];
        res.send(new VM().run(filter(unsafe)));
    }
})

app.get('/robots.txt',(req,res)=>{
    var data = fs.readFileSync('app.js');
    res.send(data.toString());
})

app.listen(80, function () {
    console.log('Running')
})
