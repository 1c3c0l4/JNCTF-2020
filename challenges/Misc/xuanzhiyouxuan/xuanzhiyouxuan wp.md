# JNCTF-2020 : 玄之又玄

## 【解题思路】

考察word隐写方式，分为三部分。

part1观察到文本最后换行符位置有问题，选择后改文本颜色为黑色，再放大可得到part1的flag。

part2应了解到word中有隐藏文本信息的功能，以office为例，打开文件->选项->显示，勾选隐藏文字即可得到part2的flag。

part3右键文件->属性->详细信息，可在备注中找到part3的flag。

## 【flag】

JNCTF{st3GAn0gRa9h7_1S_AwwwS0mE_In_w0R0}