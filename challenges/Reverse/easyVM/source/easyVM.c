#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
uint8_t memory[400] = {65, 108, 109, 111, 115, 116, 32, 104, 101, 97, 118, 101, 110, 32, 119, 101, 115, 116, 32, 118, 105, 114, 103, 105, 110, 105, 97, 44, 32, 98, 108, 117, 101, 32, 114, 105, 100, 103, 101, 32, 109, 111, 117, 110, 116, 97, 105, 110, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 93,179,142,218,101,131,33,190,246,152,152,14,157,0,99,67,229,43,154,218,48,19,233,142,9,124,0,25,197,133,199,142,254,125,248,0,51,231,107,12,131,95,2,112,88,45,83,13,214,102,182,103,61,122,192,6,11,255,60,241,241,69,196,208,196,255,81,241,136,81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int reg[8];
void* code;
int check()
{
	uint8_t* pc = code;
	unsigned char type;
	unsigned char op_type;
	int op0,op1;
	while(1)
	{
		if(*pc == 0x06)
		{
			pc+=1;
			type = *pc;
			pc +=1;
			op0 = *pc;
			pc+=1;
			if(type == 0x01)
			{
				op1 = *(int *)pc;
				pc +=4;	
			}
			else
			{
				op1 = * pc;
				pc+=1;
			}
			switch(type)
			{
				case 0x00:
					reg[op0] = reg[op1];
					break;
				case 0x01:
					reg[op0] = op1 ;
					break;
				case 0x20:
					memory[reg[op0]] = reg[op1];
					break;
				case 0x02:
					reg[op0] = memory[reg[op1]];
					break;
			 } 
		}
		if(*pc == 0xCC)
		{
			pc+=1;
			op_type = *pc;
			pc+=1;
			type = *pc;
			pc+=1;
			op0 = *pc;
			pc+=1;
			if(type == 0x01)
			{
				op1 = *(int*)pc;
				pc +=4;
			}
			else if(type == 0x00)
			{
				op1 = reg[*pc];
				pc+=1; 
			}
			switch(op_type)
			{
				case 0x0:
					reg[op0]+=op1;
					break;
				case 0x1:
					reg[op0]-=op1;
					break;
				case 0x2:
					reg[op0]*=op1;
					break;
				case 0x3:
					reg[op0]/=op1;
					break;
				case 0x4:
					reg[op0]%=op1;
					break;
				case 0x5:
					reg[op0]|=op1;
					break;
				case 0x6:
					reg[op0]&=op1;
					break;
				case 0x7:
					reg[op0]^=op1;
					break;
				case 0x8:
					reg[op0]<<=op1;
					break;
				case 0x9:
					reg[op0]>>=op1;
					break;
			}
		}
		if(*pc == 0x30)
		{
			pc+=1;
			type = *pc;
			pc+=1;
			op0 = *pc;
			pc+=1;
			if(type == 0x01)
			{
				op1 = *(int*)pc;
				pc+=4;
				reg[7] = reg[op0] - op1;
			}
			else if(type == 0x00)
			{
				op1 = *pc;
				pc+=1;
				reg[7] = reg[op0] - reg[op1];
			}
			
		}
		if(*pc == 0x09)
		{
			type = *(pc+2);
			int offset = *(int*)(pc+3);
			switch(type)
			{
				case 0x00:
					pc+=offset;
					break;
				case 0x01:
					if(reg[7]==0)
						pc+=offset;
					else
						pc+=7;
					break;
				case 0x02:
					if(reg[7]!=0)
						pc+=offset;
					else
						pc+=7;
					break;
				case 0x03:
		            if(reg[7]>0)
                        pc+=offset;
                    else
                        pc+=7;
                    break;
                case 0x04:
                    if(reg[7]>=0)
                        pc+=offset;
                    else
                        pc+=7;
                    break;
                case 0x05:
                    if(reg[7]<0)
                        pc+=offset;
                    else
                        pc+=7;
                    break;
                case 0x06:
                    if(reg[7]<=0)
                        pc+=offset;
                    else
                        pc+=7;
                    break;	 
			}
			
		}
		if(*pc == 0xC3)
		{
			return 0;
		 } 
		
	}
}
int main(int agrc , char** agrv)
{
	code = malloc(2000);
	FILE* f;
	if(agrc > 1)
	{
		f = fopen(agrv[1],"r");
		fread(code,1,1000,f);
		fclose(f);
	}
	else
	{
		printf("error!\n");
		return 0; 
	}
	int i;
    printf("Welcome to JNCTF!\n");
    printf("please input your flag:\n");
    scanf("%s",memory+0x32);
    check();
    if(reg[0])
    {
    	printf("Congratulations!\n");
	}
	else
	{
		printf("Try again!\n");
	}
	return 0;
}
	
