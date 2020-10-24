## boost writeup
这道题目是道逻辑清晰的C++逆向题目，用户输入然后校验输入是否正确，这道题目的校验可以分为四步，第一步在boostFn函数内，这个函数是检查输入的格式是不是 'string'+'@'+'string'+'#'+'string'的格式，
第二步检验就是boostFunc函数的内容，是对输入的第一部分进行校验，源码如下：
```C
void boostFunc(unsigned short& num) {
	//随机数check
	//预期的num是102
	if (num > 111) {
		_exit(0);
	}
	boost::mt19937 rng(num);
	rng.discard(num % 12);
	//拷贝构造，保留了所有状态
	boost::mt19937 rng_(rng);
	rng_.discard(num / 12);
	//这里相当于丢弃了num个随机结果
	if (rng_() != 1340652423) {
		_exit(0);
	}
	num -= (rng_() % 45);	// 45
}
```
一个unsigned short传入，小于等于111，把它作为随机引擎的种子，丢弃掉num % 12个随机数，然后用一次随机引擎的拷贝构造

注意，这里拷贝构造会完全保留随机引擎的状态，而不是回归初始状态

在IDA中就表现为直接一个memcpy

接着再丢弃掉num/12个随机数

然后输出一个随机数要求等于3570126595，最后由于是引用，传入的数值被改变
第三部分校验的源码如下:
```C
const char* what = "NQJtW9cf0qwryuLZvbXCEK8VghjklzxIOPASBNM2RsdfF56TYU34p7ioGHJcnm";
	int len = strlen(what);


	//20637
	if (what[str[0] - '0'] == 'J') {
		if (what[str[1] - '0'] == 'N') {
			if (what[str[2] - '0'] == 'c') {
				if (what[str[3] - '0'] == 't') {
					if (what[str[4] - '0'] == 'f') {
						goto out;
					}
				}
			}
		}
	}
```
很简单，要求第二部分转化为数字作为what数组的序列进行比较，输入应该是20637，
第三部分校验如下:
```C
	if ((res.num3 % res.num1 != 12) && (res.num3 / res.num1) != 3) {
		//3 * 34 + 12 == 222
		std::cout << "You failed...again";
		_exit(0);
	}
```
是利用第一部分输入变化后进行第三部分校验，过程很简单，应该是114，
综上输入应该是
102@20637#222
flag为：
JNCTF{102@20637#222}