# JNCTF-2020 : 大道无形

## 【解题思路】

第一步binwalk分离出压缩包。第二步补全data matrix码（两边加黑线），得到passwd : 825620118233df0c。

使用passwd解密压缩包得到二维码一个，扫描二维码得到PDF417码，解码得flag。

## 【flag】

JNCTF{BaRc00e_For_U}