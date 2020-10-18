#include<stdio.h>
#include<iostream>
using namespace std;
#include<string>
string s = "ocvv_zzpocjm_dn_zz_yyvvzzpodapg_bdmg";
string s2 = "abcdefghijklmnopqrstuvwxyzabcdefghij";
char sub_0400100(char a){
	char b;
	b = a;
	b = char(int(a) - 5);
	return b;
}
char sub_0400200(char a){
	char b;
	string cc = "abcde";
	for(int i=0;i< cc.length() ;i++)
	{
	   if(a == cc[i])
	   {
	   	b = char(int(a) + 25 - i*2);
	   	break;
	   }
    } 
    return b;
}
int main(){
	string s1; 
	cout<<"plz input sth.:";
	cin>>s1;
	int j = 0;
	for(int i=0;i< s1.length() ;i++)
	{
		if(s1[i]>= 'f' && s1[i]<= 'z')
		   s2[j] = sub_0400100(s1[i]);
		else if(s1[i]>= 'a' && s1[i]< 'f')
		{
			s2[j] = sub_0400200(s1[i]);
			s2[j+1] = s2[j];
			j++;
		}
		else  s2[j] = s1[i];
		j++; 
	}
	if(s2 == s) cout<<"you get it!"<<endl<<"your flag£ºJNCTF{your input}";
	else cout<<"fail!";
}
