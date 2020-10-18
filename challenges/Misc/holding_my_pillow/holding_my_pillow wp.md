# JNCTF-2020 : 握着我的抱枕

## 【解题思路】

OpenPuff加解密工具需要三个密码方可解密。

音频文件调整至最开始可从左声道出得到五个一组的高低采样点，以摩斯密码解密得到keyA : 72350591。

HEX编辑器观察文件尾部得到common cathode 3f4f6f7f7d6d5b7d，此处需要了解数电知识，此为共阴极数码管段码，加上0x逐个解密得到KEYB : 03986526。

slienteye解密得到keyC : 89490211。

放入OpenPuff解密即可得到flag文件。

## 【flag】

JNCTF{mUs1C_ls_WAv_m0Re_FUn!}