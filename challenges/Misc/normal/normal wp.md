# JNCTF-2020 : Normal

## 【解题思路】

log文件，如果没有思路打开文件开头有btsnoop，稍微搜索一下可以知道这是安卓蓝牙数据包。直接使用wireshark分析，搜索关键词可以看到在obex协议中传输了flag.zip，分组字节流导出发现加密。根据提示，可以在HCI_EVT协议中找到敏感pc名DESKTOP-058FBK8（其实是我的pc蓝牙名），解密得到flag。

## 【flag】

JNCTF{AndroId_B1uEt00Th_1s_hhhhRd}

