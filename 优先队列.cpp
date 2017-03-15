#include<iostream>
#include<stdlib.h>
#define MAX_PRI 100000
using namespace std;

//���ȶ��нڵ�
typedef struct Node{
	//����
	int num;
	//���ȶ�
	int Pri;
	//ָ��
	Node*next;
}Node;
//���ȶ��нṹ��
typedef struct PriQue{
	//����
	int len;
	//ͷ���
	Node*head;
	//β�ڵ�
	Node*end;
}PriQue;
//�������
int insert_with_pripority(PriQue* que,int num,int Pri){
	Node*n = new Node;
	Node*Tmp = que->head;
//	cout << "����Ԫ�أ�";
//	cin >> n->num;
//	cout << "�������ȶȣ�";
//	cin >> n->Pri;
	n->num = num;
	n->Pri = Pri;
	//���ȶ��в�Ϊ��ʱ
	if (Tmp->next!=NULL && Tmp->next->Pri!=0){
		//�����ҵ��ò���Ľڵ�
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
//������
Node* pull_highest_priority_element(PriQue*que){
	Node*Tmp = que->head;
	Node*End = que->end;
	if (que->len == 0){
		cout << "�����ѿ�";
		return NULL;
	}
	if (Tmp->next != NULL){
		//�ҵ�β�ڵ�ǰһ���ڵ�
		while (Tmp->next != que->end){
			Tmp = Tmp->next;
		}
	}
	que->end = Tmp;
	Tmp->next = que->end;
	que->len--;
	return End;
}
//�������ȶ���
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
	//�������
	cin >> n;
	//����ÿһ��������ӣ�Ҫ�����ȶȺ������ɷ���
	for (int i = 0; i < n; i++){
		cin >> ai;
		insert_with_pripority(que, ai, MAX_PRI - ai);
	}
	Node*Tmp1,*Tmp2;
	//�������Σ��������������������ӣ���ʹsum�����������ĺ�
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