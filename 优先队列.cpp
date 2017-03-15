#include<iostream>
#include<stdlib.h>
#define MAX_PRI 100000
using namespace std;

//优先队列节点
typedef struct Node{
	//数字
	int num;
	//优先度
	int Pri;
	//指针
	Node*next;
}Node;
//优先队列结构体
typedef struct PriQue{
	//长度
	int len;
	//头结点
	Node*head;
	//尾节点
	Node*end;
}PriQue;
//进入队列
int insert_with_pripority(PriQue* que,int num,int Pri){
	Node*n = new Node;
	Node*Tmp = que->head;
//	cout << "输入元素：";
//	cin >> n->num;
//	cout << "输入优先度：";
//	cin >> n->Pri;
	n->num = num;
	n->Pri = Pri;
	//优先队列不为空时
	if (Tmp->next!=NULL && Tmp->next->Pri!=0){
		//向后查找到该插入的节点
		while (Tmp->next->Pri<n->Pri){
			Tmp = Tmp->next;
		}
	}
	n->next = Tmp->next;
	Tmp->next = n;
	if (n->next == NULL){
		que->end = n;
	}
	que->len++;
	return 1;
}
int Peak(PriQue*que){
	return que->end->num;
}
//出队列
Node* pull_highest_priority_element(PriQue*que){
	Node*Tmp = que->head;
	Node*End = que->end;
	if (que->len == 0){
		cout << "队列已空";
		return NULL;
	}
	if (Tmp->next != NULL){
		//找到尾节点前一个节点
		while (Tmp->next != que->end){
			Tmp = Tmp->next;
		}
	}
	que->end = Tmp;
	Tmp->next = que->end;
	que->len--;
	return End;
}
//建立优先队列
PriQue*createPriQue(){
	PriQue*que = new PriQue;
	que->len = 0;
	Node*head = new Node;
	head->next = NULL;
	head->num = NULL;
	head->Pri = 0;
	que->end = que->head = head;
	return que;
}
int main(){
	int num;
	PriQue* que = createPriQue();
	int n;
	int ai;
	int sum = 0;
	//输入堆数
	cin >> n;
	//输入每一堆量并入队，要求优先度和数量成反比
	for (int i = 0; i < n; i++){
		cin >> ai;
		insert_with_pripority(que, ai, MAX_PRI - ai);
	}
	Node*Tmp1,*Tmp2;
	//出队两次，将这两个数相加重新入队，并使sum增加两个数的和
	while (que->head->next->next!=NULL&&que->head->next->next->Pri!=0){
		Tmp1 = pull_highest_priority_element(que);
		Tmp2 = pull_highest_priority_element(que);
		num= Tmp1->num + Tmp2->num;
		sum += num;
		insert_with_pripority(que, num, MAX_PRI - num);
		delete Tmp1;
		delete Tmp2;
	}
	cout << sum;
	getchar();
	getchar();
}