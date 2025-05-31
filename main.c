/* (1) ���������ڽý�������, (2) 2310131, (3) �����, (4) main.c (5) 2025.05.31 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//1.��ť ����, �������: ���Ḯ��Ʈ ť
//ť ��� ����:�̸�����, ���ð����� 
typedef struct qNode{
	char name[30];
	struct qNode* next;
	int arrivalT; //�����ð�
	int key; //VIP���� 
}qNode; 
//������ ����
typedef struct hNode{
	qNode* front;
	qNode* rear;
	int length;
}hNode; 
//2.���� ���� 
//�Ϲݰ��߰� 
void enqueue(hNode* h, char person[], int arrivalT){ //�ڿ� �߰� 
	qNode* newNode;
	newNode=(qNode*)malloc(sizeof(qNode));
	strcpy(newNode->name, person);//�����Լ� 
	newNode->next = NULL; //���� ����
	newNode->key = 1;
	newNode->arrivalT = arrivalT;//���Ե� �ð� 
	if(h->length==0){
		h->front = h->rear = newNode;  
	} 
	else{
		h->rear->next = newNode; //���� 
		h->rear = newNode; //�� �ű�� 
	}
	h->length ++; //���� �� ���� ����
	 
}
//VIP�߰� 
void enqueue_front(hNode* h, char person[], int arrivalT){ //�տ� �߰� 
	qNode* newNode;
	newNode=(qNode*)malloc(sizeof(qNode));
	strcpy(newNode->name, person);//�����Լ� 
	newNode->key = 1;
	newNode->arrivalT = arrivalT;
	if(h->length==0){
		h->front = h->rear = newNode;
		newNode->next = NULL; //�ڿ� ��� ���� 
	} 
	else{
		newNode->next = h->front; //�տ� ���� 
		h->front = newNode; //�Ǿ� �ű�� 
	}
	h->length ++; //���� �� ���� ���� 
}
//�������� 
void dequeue(hNode* h){
	if(h->length==0){
		printf("���� ����ֽ��ϴ�.\n");
		exit(1);
	} 
	else{
		qNode* temp = h->front; //������ ���  
		printf("%s ����\n",temp->name); //��� ��û 
		h->front = h->front->next; //�Ǿ� �ű��
		free(temp); //�޸� �ݳ�
		h->length--;
	}
}
//������ٸ����ã��: ������ٸ� ��� �Ǿ����� �ű�� dequeue�����ϱ� 
void findleave(hNode* h, int clock){
	if(h->length==0) return; //�����ϋ� no
	qNode *before = NULL;
	qNode *temp = h->front;
	
	while(temp!=NULL){//��� �ѹ��� �˻�
		if(clock-temp->arrivalT > 2){//3����ٸ��� out 
			//�̹� �Ǿ�
			if(before==NULL){
				dequeue(h);
				return;
			} 
			before->next = temp->next; //��ĭ�̵�
			
			//�߰���� ���� 
			temp->next = h->front; //�Ǿ��� ��带 ����Ŵ 
			h->front = temp; //�Ǿ��� ���ݳ�� 
			
			//����� ���� 
			if(temp==h->rear){
				h->rear = before;
			} 
			printf("[00:%d]�ð��ʰ���",clock);
			dequeue(h);
			return; 
		}
		//��ĭ���̵� 
		before = temp;
		temp = temp->next;
	} 
	/*
	hNode* delN;
	delN=(hNode*)malloc(sizeof(hNode));
	delN->front = h->front;
	delN->rear = h->front; //����� 
	
	int i;
	for(i=0;i<h->length;i++){
		if(delN->front->arrivalT > clock+4){
			//����������
			delN->rear->next = delN->front->next;
		 
			//����	
			delN->length = 1; //dequeue����
			dequeue(delN); 
			
		}
		else {
			if(delN->rear!=delN->front){//���� ���x 
				delN->rear = delN->front; 
			}
			delN->front = delN->front->next; //���� ��� 
		}
	} */
}
//����Լ�
void qprint(hNode* h){
	int i;
	qNode* pp = h->front; //����Ʈ�Ұ� ������ 
	//pnode[h->length]; //����Ʈ�� �迭 ����
	printf("-> ť ����:"); 
	for(i=0;i<h->length-1;i++){ //�� ��� ������ ȭ��ǥ�ְ� 
		//if(pp->next!=NULL){
		printf("%s->",pp->name);
		//pNode[i]= pp->name
		pp=pp->next;//������� 
		//}
	}
	printf("%s\n",pp->name); //������ ��� 
	/*for(i=0;i<h->length;i++){
		printf("���� ť ����:%s\n",pp->name);
	}*/
	
} 

int main(int argc, char *argv[]) {
	//��鰡�� �ڵ� ���� �ý��� ����
	//0.����ť
	hNode *waiting;
	waiting=(hNode*)malloc(sizeof(hNode));
	waiting->length = 0;
	waiting->front = waiting->rear = NULL;
	//1.��û �ޱ�->�ó����� �ۼ�?
	
	//1.�ð� �ùķ��̼� ����
	int clock=0;
	int arrivalT=0; //�� �����ð� 
	int leaveT=2; //�� ������ �ð� //�ּ�2 
	int aTvip=0; // ó���� �ȿ� 
	int serverS; 
	//queue; 
	while(clock<11){ 
		clock=clock + 1;//�ð����� 
		
		
		//1-1.���� ����, �Ϲݰ������ð�����=1 
		if(clock>=arrivalT){//���� ����-> ������ 
			char person[30]={0};
			printf("���̸��Է�(������0):");
			scanf("%s",person);
			if(person[0]!='0'){
				enqueue(waiting, person,arrivalT);//�����ض� //���񽺴��
				printf("[00:%d]�Ϲݰ��߰�:%s\n",clock,person);
				
			}
			arrivalT=clock+1; //�����������ð�, �������ð�����(1�� ����)
		}
		//1-1-2.VIP ����, VIP���� ���� =2
		if(clock>=aTvip){//���� ����-> ������ 
			char vip[30]={0}; 
			printf("VIP�̸��Է�(������0):");
			scanf("%s",vip);
			if(vip[0]!='0'){
				enqueue_front(waiting,vip,aTvip);//�����ض� //���񽺴��
				printf("[00:%d]VIP���߰�:%s\n",clock,vip);
				
			} 
			aTvip=clock+1; //�����������ð�, �������ð�����(3 ����)
		}
		/*1-2.���̶��� 
		if(clock>=leaveT){//������, ���񽺿Ϸ� //ó������ ��转������ 
			serverS = 1; //���� �� 
		} 
		//1-3.������ ���� 
		if(serverS==1&&waiting->length!=0){
			dequeue(waiting);//�����ϱ� 
			serverS=0;
			leaveT=clock+2;//���� ���񽺹޴½ð�(2�ΰ���)
		}*/
		//1-4.�����ɷ��� ����
		 
		findleave(waiting,clock);
		qprint(waiting);
		printf("-------------------------\n");
	}
	
	return 0;
}
