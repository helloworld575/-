#include<iostream>
#include<stdlib.h>
#include<time.h>
#define MAX_LEVEL 10

using namespace std;
//节点结构
typedef struct Node{
	int key;
	//值，在这里key和value表示同一个东西
	float value;
	//向前指针、、、、
	struct Node *forward[1];
}Node;

//跳表结构
typedef struct skipList{
	//最大层数
	int level;
	//表头指针，永远指向左上角的节点
	Node *Head;
}skipList;

//创建节点
Node* createNode(int level, int key, float value){
	//申请空间：Node本身和他所需要的指针数组的空间
	Node *Tmp = (Node*)malloc(sizeof(Node) + level*sizeof(Node*));
	Tmp->key = key;
	Tmp->value = value;
	return Tmp;
}

//创建初始化跳表
skipList* createskipList(){
	//申请跳表空间
	skipList*sl = (skipList*)malloc(sizeof(skipList));
	sl->level = 0;
	//创建头结点（高度为最大值，value和key均为0）
	sl->Head = createNode(MAX_LEVEL - 1, 0, 0);
	for (int i = 0; i < MAX_LEVEL; i++){
		sl->Head->forward[i] = NULL;
	}
	return sl;
}

//插入元素，插入元素的时候元素所占有的层数完全是随机的，通过随机算法产生
int randomLevel(){
	int k = 1;
	//设置种子
	srand((unsigned int)time(0));
	//构造随机数：产生一随机数，若是二的倍数则k加1直到基数出现
	while (rand() % 2)
		k++;
	//禁止大于最大层数
	k = (k < MAX_LEVEL) ? k : MAX_LEVEL;
	return k;
}

//插入算法函数，插入成功返回真否则返回假，直接插入内容
bool insert(skipList*sl, int key, float value){
	//update 存放需要插入前一节点的全部指针
	Node*update[MAX_LEVEL] = { 0 };
	Node *p, *q = NULL;

	p = sl->Head;
	int k = sl->level;
	//从最高层往下查找需要插入的位置，填充update
	for (int i = k - 1; i >= 0; i--){
		while ((q = p->forward[i]) && (q->key < key))
			p = q;
		update[i] = p;
	}
	//不能插入相同的值
	if (q&&q->key == key)
		return false;
		//产生一个随机层数k，新建一个待插入节点q，一层一层插入
	k = randomLevel();
	//若k变大的话更新跳表的LEVEL
	if (k > (sl->level)){
		for (int i = sl->level; i < k; i++){
			update[i] = sl->Head;
		}
		sl->level = k;
	}
	//创建节点
	q = createNode(k, key, value);
	//更新跳表数据
	for (int i = 0; i < k; i++){
		q->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = q;
	}
	return true;
}

//删除函数
bool deleteSL(skipList*sl, int key){
	//同样存放指针
	Node*update[MAX_LEVEL];
	Node*p, *q = NULL;
	p = sl->Head;
	int k = sl->level;
	//从最高层往下查找需要插入的位置，填充update
	for (int i = k - 1; i >= 0; i--){
		while ((q = p->forward[i]) && (q->key < key))
			p = q;
		update[i] = p;
	}
	//查找到时开始删除数据，否则删除失败
	if (q&&q->key == key){
		//将节点从跳表中删除
		for (int i = 0; i < sl->level; i++){
			if (update[i]->forward[i]==q)
				update[i]->forward[i] = q->forward[i];
		}
		//彻底删除节点
		free(q);
		//重新设置level
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

//查找函数
int searh(skipList*sl, int key){
	Node *p, *q = NULL;
	p = sl->Head;
	int k = sl->level;
	//大循环按照层数向下找，小循环在一层中向右找
	cout << "查询过程：" << endl;
	int i;
	for (i = k - 1; i >= 0; i--){
		cout << "层数为：" << i << ' ' << "值为：" << p->value << endl;
		while ((q = p->forward[i]) && (q->key <= key)){
			if (q->key == key)
				return i+1;
			p = q;
			cout << "层数为："<< i << ' ' <<"值为："<< p->value << endl;
		}
		
	}
	return false;
}

//输出函数
void printSL(skipList*sl){
	Node *p, *q = NULL;
	int k = sl->level;
	for (int i = k - 1; i >= 0; i--){
		cout << "第" << i << "层：";
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

//插入驱动函数
void in_insert(skipList*sl){
	while (true){
		float num = -1;
		//printf("请输入要插入的内容，-1结束：");
		cout << "请输入要插入的内容，-1结束：";
		cin >> num;
		if (num == -1)
			break;
		if (insert(sl, num, num)){
			//printf("插入后的跳表：\n");
			cout << "插入后的跳表：" << endl;
			printSL(sl);
		}
		else{
			cout << "无法插入！" << endl;
		}
	}
}

//查找驱动函数
void in_search(skipList*sl){
	//printf("请输入要查找的内容，-1结束：");
	while (true){
		cout << "请输入要查找的内容，-1结束：";
		float sea1;
		int sea2;
		cin >> sea1;
		if (sea1 == -1)
			return;
		if ((sea2 = sea1) != sea1){
			cout << "请输入整数！" << endl;
			continue;
		}
			
		int i = searh(sl, sea1);
		//printf("i=%d\n", i);
		if (i){
			cout << "查询结果： 所有层：" << i << endl;
			printSL(sl);
		}
		else
			cout << "没有查找到！";
	}
}
//删除驱动函数
void in_delete(skipList*sl){
	//printf("请输入要删除的内容，-1结束：");
	cout << "删除前跳表：" << endl;
	printSL(sl);
	cout << "请输入要删除的内容，-1结束：";
	while (true){
		int num = -1;
		cin >> num;
		if (num == -1)
			return;
		bool b = deleteSL(sl, num);
		if (b)
			printf("删除成功!\n");
		else
			cout << "删除失败!";
		printSL(sl);
	}
}

int main(){
	skipList *sl = createskipList();
	int Order;
	//printf("请输入命令（1：插入，2：查找，3：删除，4：退出）：");
	while (true){
		cout << "请输入命令（1：插入，2：查找，3：删除，4：退出）：";
		cin >> Order;
		if (Order == 1)
			in_insert(sl);
		else if (Order == 2)
			in_search(sl);
		else if (Order == 3)
			in_delete(sl);
		else if (Order == 4){
			printf("退出\n");
			return 0;
		}
		else
			continue;
	}
}
