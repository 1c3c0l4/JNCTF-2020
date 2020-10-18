#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
char name[0x200];
char key;
void *key_ptr = &key;
void init() {
	setvbuf(stdin, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
	setvbuf(stderr, 0LL, 2, 0LL);
}
void welcome(){
	puts("==================================");
	puts("||        Welcome to JNCTF!     ||");
	puts("|| Are you familiar with stack? ||");
	puts("||This is an easy encode system!||");
	puts("||       Have a good time!      ||");
	puts("==================================");
}
void encode(char *message,int len,int key){
	int i;
	for(i=0;i<len;i++){
		message[i] ^= key;
	}
}
void vuln(){
	char buf[0x28];
	memset(buf,0,0x28);
	key = rand() & 0xff;
	write(1,"your lucky key:",15);
	write(1,key_ptr,1);
	write(1,"\n",1);
	write(1, "leave your name:", 0x10);
	read(0,name,0x200);
	write(1, "message:", 8);
	encode(buf,read(0,buf,0x38),key);
	write(1, "OK!", 3);
	

}
int main(){
	init();
	welcome();
	srand((unsigned int)time(NULL));
	vuln();
	return 0;	
} 
