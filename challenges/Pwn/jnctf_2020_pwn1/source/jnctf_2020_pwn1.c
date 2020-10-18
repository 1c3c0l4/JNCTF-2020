#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
char buf1[0x30];
int flag;
void magic(){
	system("echo 'no flag!'");
}
void stdaffair(){
	setvbuf(stdin, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
	setvbuf(stderr, 0LL, 2, 0LL);

}

void welcome(){
	puts("==================================");
	puts("||        Welcome to JNCTF!     ||");
	puts("||         Just a babypwn.      ||");
	puts("||       Have a good time!      ||");
	puts("==================================");
}
void vuln(){
	char buf[0x20];
	puts(">>");
	read(0,buf1,0x40);
	if(flag==0x1000){
		puts("nice shoot!leave your name:");
		read(0,buf,0x40);
		return;
	}else{
		printf("Game over!");
		exit(1);
	}
}
int main(){
	stdaffair();
	flag = 1;
	welcome();
	vuln();
}
