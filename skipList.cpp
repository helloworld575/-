#include<iostream>
#include<stdlib.h>
#include<time.h>
#define MAX_LEVEL 10

using namespace std;
//�ڵ�ṹ
typedef struct Node{
	int key;
	//ֵ��������key��value��ʾͬһ������
	float value;
	//��ǰָ�롢������
	struct Node *forward[1];
}Node;

//����ṹ
typedef struct skipList{
	//������
	int level;
	//��ͷָ�룬��Զָ�����ϽǵĽڵ�
	Node *Head;
}skipList;

//�����ڵ�
Node* createNode(int level, int key, float value){
	//����ռ䣺Node�����������Ҫ��ָ������Ŀռ�
	Node *Tmp = (Node*)malloc(sizeof(Node) + level*sizeof(Node*));
	Tmp->key = key;
	Tmp->value = value;
	return Tmp;
}

//������ʼ������
skipList* createskipList(){
	//��������ռ�
	skipList*sl = (skipList*)malloc(sizeof(skipList));
	sl->level = 0;
	//����ͷ��㣨�߶�Ϊ���ֵ��value��key��Ϊ0��
	sl->Head = createNode(MAX_LEVEL - 1, 0, 0);
	for (int i = 0; i < MAX_LEVEL; i++){
		sl->Head->forward[i] = NULL;
	}
	return sl;
}

//����Ԫ�أ�����Ԫ�ص�ʱ��Ԫ����ռ�еĲ�����ȫ������ģ�ͨ������㷨����
int randomLevel(){
	int k = 1;
	//��������
	srand((unsigned int)time(0));
	//���������������һ����������Ƕ��ı�����k��1ֱ����������
	while (rand() % 2)
		k++;
	//��ֹ����������
	k = (k < MAX_LEVEL) ? k : MAX_LEVEL;
	return k;
}

//�����㷨����������ɹ���������򷵻ؼ٣�ֱ�Ӳ�������
bool insert(skipList*sl, int key, float value){
	//update �����Ҫ����ǰһ�ڵ��ȫ��ָ��
	Node*update[MAX_LEVEL] = { 0 };
	Node *p, *q = NULL;

	p = sl->Head;
	int k = sl->level;
	//����߲����²�����Ҫ�����λ�ã����update
	for (int i = k - 1; i >= 0; i--){
		while ((q = p->forward[i]) && (q->key < key))
			p = q;
		update[i] = p;
	}
	//���ܲ�����ͬ��ֵ
	if (q&&q->key == key)
		return false;
		//����һ���������k���½�һ��������ڵ�q��һ��һ�����
	k = randomLevel();
	//��k���Ļ����������LEVEL
	if (k > (sl->level)){
		for (int i = sl->level; i < k; i++){
			update[i] = sl->Head;
		}
		sl->level = k;
	}
	//�����ڵ�
	q = createNode(k, key, value);
	//������������
	for (int i = 0; i < k; i++){
		q->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = q;
	}
	return true;
}

//ɾ������
bool deleteSL(skipList*sl, int key){
	//ͬ�����ָ��
	Node*update[MAX_LEVEL];
	Node*p, *q = NULL;
	p = sl->Head;
	int k = sl->level;
	//����߲����²�����Ҫ�����λ�ã����update
	for (int i = k - 1; i >= 0; i--){
		while ((q = p->forward[i]) && (q->key < key))
			p = q;
		update[i] = p;
	}
	//���ҵ�ʱ��ʼɾ�����ݣ�����ɾ��ʧ��
	if (q&&q->key == key){
		//���ڵ��������ɾ��
		for (int i = 0; i < sl->level; i++){
			if (update[i]->forward[i]==q)
				update[i]->forward[i] = q->forward[i];
		}
		//����ɾ���ڵ�
		free(q);
		//��������level
		for (int i = sl->level - 1; i >= 0; i--){
			if (sl->Head->forward[i] == NULL){
				sl->level--;
			}
		}
		return true;
	}
	else
		return false;
}

//���Һ���
int searh(skipList*sl, int key){
	Node *p, *q = NULL;
	p = sl->Head;
	int k = sl->level;
	//��ѭ�����ղ��������ң�Сѭ����һ����������
	cout << "��ѯ���̣�" << endl;
	int i;
	for (i = k - 1; i >= 0; i--){
		cout << "����Ϊ��" << i << ' ' << "ֵΪ��" << p->value << endl;
		while ((q = p->forward[i]) && (q->key <= key)){
			if (q->key == key)
				return i+1;
			p = q;
			cout << "����Ϊ��"<< i << ' ' <<"ֵΪ��"<< p->value << endl;
		}
		
	}
	return false;
}

//�������
void printSL(skipList*sl){
	Node *p, *q = NULL;
	int k = sl->level;
	for (int i = k - 1; i >= 0; i--){
		cout << "��" << i << "�㣺";
		p = sl->Head;
		while (q = p->forward[i]){
			//printf("%d -> ", p->value);
			cout << p->value << " -> ";
			p = q;
		}
		cout << p->value;
		cout << endl;
	}
	cout << endl;
}

//������������
void in_insert(skipList*sl){
	while (true){
		float num = -1;
		//printf("������Ҫ��������ݣ�-1������");
		cout << "������Ҫ��������ݣ�-1������";
		cin >> num;
		if (num == -1)
			break;
		if (insert(sl, num, num)){
			//printf("����������\n");
			cout << "����������" << endl;
			printSL(sl);
		}
		else{
			cout << "�޷����룡" << endl;
		}
	}
}

//������������
void in_search(skipList*sl){
	//printf("������Ҫ���ҵ����ݣ�-1������");
	while (true){
		cout << "������Ҫ���ҵ����ݣ�-1������";
		float sea1;
		int sea2;
		cin >> sea1;
		if (sea1 == -1)
			return;
		if ((sea2 = sea1) != sea1){
			cout << "������������" << endl;
			continue;
		}
			
		int i = searh(sl, sea1);
		//printf("i=%d\n", i);
		if (i){
			cout << "��ѯ����� ���в㣺" << i << endl;
			printSL(sl);
		}
		else
			cout << "û�в��ҵ���";
	}
}
//ɾ����������
void in_delete(skipList*sl){
	//printf("������Ҫɾ�������ݣ�-1������");
	cout << "ɾ��ǰ����" << endl;
	printSL(sl);
	cout << "������Ҫɾ�������ݣ�-1������";
	while (true){
		int num = -1;
		cin >> num;
		if (num == -1)
			return;
		bool b = deleteSL(sl, num);
		if (b)
			printf("ɾ���ɹ�!\n");
		else
			cout << "ɾ��ʧ��!";
		printSL(sl);
	}
}

int main(){
	skipList *sl = createskipList();
	int Order;
	//printf("���������1�����룬2�����ң�3��ɾ����4���˳�����");
	while (true){
		cout << "���������1�����룬2�����ң�3��ɾ����4���˳�����";
		cin >> Order;
		if (Order == 1)
			in_insert(sl);
		else if (Order == 2)
			in_search(sl);
		else if (Order == 3)
			in_delete(sl);
		else if (Order == 4){
			printf("�˳�\n");
			return 0;
		}
		else
			continue;
	}
}
