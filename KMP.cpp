#include<iostream>
#include<string>
#include<stdlib.h>

#define max(a,b) (a>b?a:b)

using namespace std;
string s1, s2;
int nex[200];

//获取跳转表
void getnext(){
	//初始化内存
	memset(nex, 0, sizeof(nex));
	//i为末尾，j为开头下标
	int i = -1, j = 0;
	nex[0] = -1;
	while (j < s2.size()){
		if (i == -1 || s2[i] == s2[j]){
			j++; i++;
			nex[j] = i;
		}
		else
			i = nex[i];
	}
	for (i = 0; i < s2.size(); i++){
		cout << nex[i];
	}
}
//KMP算法主函数
int KMP(){
	int i = 0, j = 0, len1 = s1.size(), len2 = s2.size();
	while ((i < len1) && (j < len2)){
		if (j == -1 || s1[i] == s2[j]){
			i++; j++;
		}
		else
			j = nex[j];
	}
	if (j == len2)
		return i - len2;
	else
		return -1;
}
//字符串处理，删去开头结尾的空格
string& trim(string& s){
	if (s.empty()){
		return s;
	}
	s.erase(0, s.find_first_not_of(' '));
	s.erase(s.find_last_not_of(' ')+1);
	return s;
}
int main(){
	getline(cin, s1);
	s1 = trim(s1);
	getline(cin, s2);
	s2 = trim(s2);
	getnext();
	printf("%d", KMP());
	getchar();
}
