#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char buf[0x140]={0,1};
long long int flag = 1;
void welcome(){
	puts("===========================");
	puts("||   Welcome to JNCTF!   ||");
	puts("|| There are three games!||");
	puts("||    only one shoot?!   ||");
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
	puts("||          menu         ||");
	puts("||         1,game1       ||");
	puts("||         2,game2       ||");
	puts("||         3,game3       ||");
	puts("===========================");
	puts("your choice:");
}

void function1(){
	char name[0x20];
	puts("==========game1==========");
	puts("your name?");
	read(0,name,0x20);
	printf("Your name:%s",name);
	puts("Leave your message:");
	read(0, buf,0x150);
	puts(buf);
	puts("nice game1...");
}
void function2(){ 
	char buf1[0x18];
	puts("==========game2==========");
	puts("Leave your message:");
	read(0,buf1,0x18);
	puts("after encoding...");
	printf(buf1);
	puts("nice game2...");
}
int function3(){
	char temp[0x100];
	puts("==========game3==========");
	puts("Leave your message:");
	read(0, temp, 0x100); 
	puts("after encoding...");
	puts(temp);
	puts("nice game3...");
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
