#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#define IDEA_ADD_MODULAR    65536  
#define IDEA_MP_MODULAR     65537
#define maxim 65537
unsigned char key[20]; 
unsigned short subKey[52];
unsigned short invKey[52];
unsigned short add_mod(unsigned short a, unsigned short b) //模65536的加法
{
	unsigned long tmp = a + b;
	unsigned short ret = tmp % IDEA_ADD_MODULAR;
	return ret;
}

unsigned short multi_mod(unsigned short a, unsigned short b)//模65537乘
{
	unsigned long long tmp, tmp_a, tmp_b; 
	tmp_a = a == 0 ? (1 << 16) : a;
	tmp_b = b == 0 ? (1 << 16) : b;
	tmp = (tmp_a * tmp_b) % IDEA_MP_MODULAR;
	return (unsigned short)(tmp);
}
unsigned short inv(unsigned short xin)
{
	long n1,n2,q,r,b1,b2,t;
	if(xin==0) b2=0;
	else
	{ n1=maxim; n2=xin; b2=1; b1=0;
		do { r = (n1 % n2); q = (n1-r)/n2;
			 if(r==0) { if(b2<0) b2=maxim+b2; }
			 else { n1=n2; n2=r; t=b2; b2=b1-q*b2; b1=t; }
		   } while (r!=0);
	}
	return (unsigned short)b2;
}
void RolLeft(unsigned short tmpKey[])//循环左移
{
	unsigned highPart = tmpKey[0] >> (16 - 5);
	int i;
	for (i = 0; i < 7; i++) {
		tmpKey[i] = (tmpKey[i] << 5) | (tmpKey[i + 1] >> (16 - 5));
	}

	tmpKey[7] = (tmpKey[7] << 5) | highPart;
}

//产生52个16位子密钥 所有的子密钥都是由这128位key而来的 首先128 = 16 * 8 初始有8个子密钥
void ExtendKey()//扩展key
{
	unsigned short tmpKey[8];
	int i,j,k;

	for (i = 0; i < 8; i++) {
		subKey[i] = (key[2 * i] << 8) | (key[2 * i + 1]);//获得初始的8个subkey
		tmpKey[i] = (key[2 * i] << 8) | (key[2 * i + 1]);
	}

	//前48个
	for (i = 1; i <= 5; i++) {
		for ( k = 0; k < 5; k++)//每次移动五位 移动五次
			RolLeft(tmpKey);
		for (j = 0; j < 8; j++) {
			subKey[8 * i + j] = tmpKey[j];
		}
	}

	//最后四个
	for ( k = 0; k < 5; k++)//每次移动五位 移动五次
		RolLeft(tmpKey);
	for (i = 0; i < 4; i++) {
		subKey[48 + i] = tmpKey[i];
	}

}
void inv_key()
{
	int i,j;
	unsigned int temp;
	invKey[0]=inv(subKey[48]);
	invKey[1]=IDEA_ADD_MODULAR-subKey[49];
	invKey[2]=IDEA_ADD_MODULAR-subKey[50];
	invKey[3]=inv(subKey[51]);
	for(i=4,j=47;i<52;)
	{
		invKey[i]=subKey[j-1];
		invKey[i+1]=subKey[j];
		invKey[i+2]=inv(subKey[j-5]);
		invKey[i+3]=IDEA_ADD_MODULAR-subKey[j-3];
		invKey[i+4]=IDEA_ADD_MODULAR-subKey[j-4];
		invKey[i+5]=inv(subKey[j-2]);
		 i+=6;
		 j-=6;
	}
	temp=invKey[49];
	invKey[49]=invKey[50];
	invKey[50]=temp;
}
void DIDEARound(unsigned short x[], int round)
{
	int i;
	unsigned short temp;
	unsigned short tmp[4];
	unsigned short out[6];

	for (i = 0; i < 4; i++)
		tmp[i] = x[i];

	tmp[0] = multi_mod(x[0], invKey[6 * round]);//1
	tmp[1] = add_mod(x[1], invKey[6 * round + 1]);//2
	tmp[2] = add_mod(x[2], invKey[6 * round + 2]);//3
	tmp[3] = multi_mod(x[3], invKey[6 * round + 3]);//4


	out[0] = tmp[0] ^ tmp[2];//5
	out[1] = tmp[1] ^ tmp[3];//6

	out[2] = multi_mod(out[0], invKey[6 * round + 4]);//7
	out[3] = add_mod(out[1], out[2]);//8

	out[4] = multi_mod(out[3], invKey[6 * round + 5]);//9
	out[5] = add_mod(out[2], out[4]);//10

	out[0] = tmp[0] ^ out[4];//11
	out[1] = tmp[1] ^ out[5];//12

	out[2] = tmp[2] ^ out[4];//13
	out[3] = tmp[3] ^ out[5];//14

	temp = out[1];
	out[1] = out[2];
	out[2] = temp;

	for (i = 0; i < 4; i++) {
		x[i] = out[i];//重新赋值
		
	}

}
void DIDEAEncrypt(char *plaintext)
{
	int i;
	int count,j;
	int len;
	unsigned short temp;
	unsigned short x[4];
	unsigned char *data = plaintext;

	
	if (strlen((const char *)plaintext) % 8 != 0) {
		len = (strlen((const char *)plaintext) / 8)+1;
	}
	else
		len = strlen((const char *)plaintext) / 8;//加密组数

	for (count = 0; count < len; count++) {
		for (i = 0; i < 4; i++) {//将明文分割成16位一组
			x[i] = (data[2 * i] << 8) | data[2 * i + 1];
		}

		for (j = 0; j < 8; j++) {
			DIDEARound(x, j);
		}

		//最后一轮不进行变换 故再交换一次
		temp = x[1];
		x[1] = x[2];
		x[2] = temp;

		//第九轮变换 需要用到最后的4个子密钥了
		x[0] = multi_mod(x[0], invKey[48]);
		x[1] = add_mod(x[1], invKey[49]);
		x[2] = add_mod(x[2], invKey[50]);
		x[3] = multi_mod(x[3], invKey[51]);

		for (i = 0; i < 4; i++) {
			data[2 * i] = x[i] >> 8;
			data[2 * i + 1] = x[i] & 0xff;
		}

		data += 8;//移动到下个块
	}
}
int sum(int s[])
{
	int i,result=0;
	for(i=0;i<9;i++)
		result+=s[i];
	return result;
}
int check_r(char str[],int t)
{
	int temp[9];
	int i;
	for(i=0;i<9;i++)
		temp[9]=str[t*9+i] &0xf;
	if(sum(temp)==45)
		return 1;
	else return 0;
}
int check_c(char str[],int t)
{
	int temp[9];
	int i;
	for(i=0;i<9;i++)
		temp[i]=str[i*9+t] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
int check_s1(char str[])
{
	int i,j=0;
	int temp[9];
	for(i=0;i<3;i++)
		temp[j++]=str[0*9+i] & 0xf;
	for(i=0;i<3;i++)
		temp[j++]=str[1*9+i] & 0xf;
	for(i=0;i<3;i++)
		temp[j++]=str[2*9+i] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
int check_s4(char str[])
{
	int i,j=0;
	int temp[9];
	for(i=0;i<3;i++)
		temp[j++]=str[3*9+i] & 0xf;
	for(i=0;i<3;i++)
		temp[j++]=str[4*9+i] & 0xf;
	for(i=0;i<3;i++)
		temp[j++]=str[5*9+i] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
int check_s7(char str[])
{
	int i,j=0;
	int temp[9];
	for(i=0;i<3;i++)
		temp[j++]=str[6*9+i] & 0xf;
	for(i=0;i<3;i++)
		temp[j++]=str[7*9+i] & 0xf;
	for(i=0;i<3;i++)
		temp[j++]=str[8*9+i] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
int check_s2(char str[])
{
	int i,j=0;
	int temp[9];
	for(i=3;i<6;i++)
		temp[j++]=str[0*9+i] & 0xf;
	for(i=3;i<6;i++)
		temp[j++]=str[1*9+i] & 0xf;
	for(i=3;i<6;i++)
		temp[j++]=str[2*9+i] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
int check_s5(char str[])
{
	int i,j=0;
	int temp[9];
	for(i=3;i<6;i++)
		temp[j++]=str[3*9+i] & 0xf;
	for(i=3;i<6;i++)
		temp[j++]=str[4*9+i] & 0xf;
	for(i=3;i<6;i++)
		temp[j++]=str[5*9+i] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
int check_s8(char str[])
{
	int i,j=0;
	int temp[9];
	for(i=3;i<6;i++)
		temp[j++]=str[6*9+i] & 0xf;
	for(i=3;i<6;i++)
		temp[j++]=str[7*9+i] & 0xf;
	for(i=3;i<6;i++)
		temp[j++]=str[8*9+i] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
int check_s3(char str[])
{
	int i,j=0;
	int temp[9];
	for(i=6;i<9;i++)
		temp[j++]=str[0*9+i] & 0xf;
	for(i=6;i<9;i++)
		temp[j++]=str[1*9+i] & 0xf;
	for(i=6;i<9;i++)
		temp[j++]=str[2*9+i] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
int check_s6(char str[])
{
	int i,j=0;
	int temp[9];
	for(i=6;i<9;i++)
		temp[j++]=str[3*9+i] & 0xf;
	for(i=6;i<9;i++)
		temp[j++]=str[4*9+i] & 0xf;
	for(i=6;i<9;i++)
		temp[j++]=str[5*9+i] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
int check_s9(char str[])
{
	int i,j=0;
	int temp[9];
	for(i=6;i<9;i++)
		temp[j++]=str[6*9+i] & 0xf;
	for(i=6;i<9;i++)
		temp[j++]=str[7*9+i] & 0xf;
	for(i=6;i<9;i++)
		temp[j++]=str[8*9+i] & 0xf;
	if(sum(temp)==45)
		return 1;
	else
		return 0;
}
void getAnswer(char str[])
{
	int i,len;
	char check[10];
	char temp[20]={str[0],str[9],str[36],str[18],str[63],str[45],str[54],str[72],str[0],str[9],str[36],str[18],str[63],str[45],str[54],str[72]};
	strcpy(key,temp);
	unsigned char plaintext[42]={0x83,0x3a,0x59,0x3a,0x81,0x2e,0xb3,0x7f,0x27,0x77,0x50,0xc,0x43,0x36,0xa8,0xb8,0x61,0xf9,0x9b,0x63,0xe1,0xc2,0x3c,0x13,0xf,0xae,0xb7,0x60,0x6a,0x7c,0xc4,0x8d,0x16,0xf1,0xaa,0x47,0xf,0x6d,0xc4,0x18};
	ExtendKey();
	inv_key();	
	DIDEAEncrypt(plaintext);
	strncpy(check,plaintext,5);
	if(!strcmp(check,"JNCTF")
	{
	printf("you got it,here is your flag!\n%s\n",plaintext);
	}
	else
	{
		printf("try again!");
	}
}
int main(int argc,char *argv[])
{
	char str[88];
	strcpy(str,argv[1]); 
		if(check_s1(str))
		{
			while((str[1*9+1]=='7'&&str[2*9+0]=='4'))
			{
			if(check_s2(str))
			{
				while(str[2*9+5]=='3'&&str[2*9+3]=='9')
				{
				if(check_s3(str))
				{
					if(check_r(str,0))
					{
						if(check_r(str,1))
						{
							if(check_r(str,2))
							{
								while(str[0*9+8]=='2'&&str[1*9+7]=='5'&&str[1*9+8]=='6')
								{
								if(check_c(str,0))
								{
									if(check_c(str,1))
									{
										if(check_c(str,2))
										{
											while(str[3*9+0]=='9'&&str[4*9+1]=='2')
											{
											if(check_s4(str))
											{
												if(check_s5(str))
												{
													while(str[3*9+3]=='4'&&str[4*9+5]=='6')
													{
													if(check_s6(str))
													{
														if(check_r(str,3))
														{
															if(check_r(str,4))
															{
																if(check_r(str,5))
																{
																	while(str[4*9+8]=='5')
																	{
																	if(check_c(str,3))
																	{
																		if(check_c(str,4))
																		{
																			if(check_c(str,5))
																			{
																				while(str[6*9+1]=='6')
																				{
																				if(check_s7(str))
																				{
																					if(check_s8(str))
																					{
																						while(str[6*9+5]=='5'&&str[7*9+3]=='8')
																						{
																						
																						if(check_s9(str))
																						{
																							if(check_r(str,6))
																							{
																								if(check_r(str,7))
																								{
																									if(check_r(str,8))
																									{
																										while(str[7*9+6]=='1'&&str[7*9+7]=='4')
																										{
																										
																										if(check_c(str,6))
																										{
																											if(check_c(str,7))
																											{
																												if(check_c(str,8))
																												{
																													getAnswer(str);
																													return 0;
																												}
																											}
																										}
																									}
																									}
																								}
																							}
																						}
																					}
																					}
																				}
																			}
																			}
																		}
																	}
																}
																}
															}
														}
													}
												}
												}
											}
										}
										}
									}
								}
							}
							}
						}
					}
				}
			}
		}
		}
}
printf("try again!\n");
return 0;	
}
