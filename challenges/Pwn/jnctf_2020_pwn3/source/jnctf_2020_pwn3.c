#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char buf[0x140]={0,1};
long long int flag = 1;
char buf1[0x18];
void welcome(){
	puts("===========================");
	puts("||   Welcome to jnctf!   ||");
	puts("||This is a encode system||");
	puts("||   Have a good time!   ||");
	puts("===========================");
}
void init() {
	setvbuf(stdin, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
	setvbuf(stderr, 0LL, 2, 0LL);
}
void menu(){
	puts("===========================");
	puts("||         menu          ||");
	puts("||       1,encode1       ||");
	puts("||       2,encode2       ||");
	puts("||       3,encode3       ||");
	puts("===========================");
	puts("your choice:");
}
void encode1(char *keys,char *target,int len1,int len2){
	int i = 0;
	char key = 0;
	for(;i<len1;i++){
		key ^= keys[i]; 
	}
	for(i=0;i<len2;i++){
		target[i] ^= key;
	}
}
void encode2(char *target,int len){
	int i =0;
	for(;i<len;i++){
		target[i] = ((target[i]&0xc0)>>6) + ((target[i]&0x30)<<2) + ((target[i]&0xc)<<2) +((target[i]&0x3)<<2);
	}
}
void encode3(char *target,int len){
	int i =0;
	for(;i<len;i++){
		target[i] = ((target[i]&0xc0)>>2) + ((target[i]&0x30)>>2) + ((target[i]&0xc)>>2) +((target[i]&0x3)<<6);
	}
}
void function1(){
	char keys[0x20];
	int len1,len2;
	puts("==========encode1==========");
	puts("keys?");
	len1 = read(0,keys,0x20);
	printf("Your key:%s",keys);
	puts("your message to encode:");
	len2 = read(0, buf,0x150);
	encode1(keys,buf,len1,len2);
	puts("after encoding...");
	puts(buf);
	puts("nice encoding...");
}
void function2(){ 
	char a[0x150]; 
	int len;
	puts("==========encode2==========");
	puts("your message to encode:");
	len = read(0,buf1,0x18);
	puts("after encoding...");
	encode2(buf1,len);
	printf(buf1);
	puts("nice encoding...");
}
int function3(){
	char temp[0x100];
	int len;
	puts("==========encode3==========");
	puts("your message to encode:");
	len = read(0, temp, 0x100); 
	puts("after encoding...");
	encode3(temp,len);
	puts(temp);
	puts("nice encoding...");
	strcpy( temp,buf );
	return 0;
}


int main() {
	init();
	welcome(); 
	int choice = 0;
	
	while( 1 ){
		menu();
		scanf("%d",&choice);
		switch(choice){
			case 1:
				function1();
				break;
			case 2:
				function2();
				break;
			case 3:
				function3();
				break;	
		} 
		flag--;
		if( flag <= 0){
			exit(0);
		}
		
	}
	return 0;
}

