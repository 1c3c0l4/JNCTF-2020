# JNCTF-2020 : secret_picture

## 【解题思路】

根据提示用8位数字爆破压缩包，得到三个文件。

sunrise.jpg修改图片高度得到key，用outguess处理sunflower.jpg加得到的key解出第一部分文本文件内容，aaencode解密得到part1的flag。(获得的颜文字末尾需加分号才可正确解码)

nightsky.jpg通过steghide直接可解出第二部分文本文件内容，与熊论禅解密得到part2的flag。

## 【flag】

JNCTF{p1cTuR3_AnD_3nCr1pTI0n}
