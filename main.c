/* (1) 지능형전자시스템전공, (2) 2310131, (3) 김수안, (4) main.c (5) 2025.05.31 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//1.고객큐 구조, 노드정의: 연결리스트 큐
//큐 노드 구조:이름저장, 대기시간저장 
typedef struct qNode{
	char name[30];
	struct qNode* next;
	int arrivalT; //도착시간
	int key; //VIP여부 
}qNode; 
//헤더노드 정의
typedef struct hNode{
	qNode* front;
	qNode* rear;
	int length;
}hNode; 
//2.연산 정의 
//일반고객추가 
void enqueue(hNode* h, char person[], int arrivalT){ //뒤에 추가 
	qNode* newNode;
	newNode=(qNode*)malloc(sizeof(qNode));
	strcpy(newNode->name, person);//복사함수 
	newNode->next = NULL; //끝에 삽입
	newNode->key = 1;
	newNode->arrivalT = arrivalT;//삽입된 시간 
	if(h->length==0){
		h->front = h->rear = newNode;  
	} 
	else{
		h->rear->next = newNode; //삽입 
		h->rear = newNode; //끝 옮기기 
	}
	h->length ++; //삽입 후 길이 증가
	 
}
//VIP추가 
void enqueue_front(hNode* h, char person[], int arrivalT){ //앞에 추가 
	qNode* newNode;
	newNode=(qNode*)malloc(sizeof(qNode));
	strcpy(newNode->name, person);//복사함수 
	newNode->key = 1;
	newNode->arrivalT = arrivalT;
	if(h->length==0){
		h->front = h->rear = newNode;
		newNode->next = NULL; //뒤에 노드 없음 
	} 
	else{
		newNode->next = h->front; //앞에 삽입 
		h->front = newNode; //맨앞 옮기기 
	}
	h->length ++; //삽입 후 길이 증가 
}
//삭제연산 
void dequeue(hNode* h){
	if(h->length==0){
		printf("줄이 비어있습니다.\n");
		exit(1);
	} 
	else{
		qNode* temp = h->front; //삭제할 노드  
		printf("%s 제거\n",temp->name); //퇴소 요청 
		h->front = h->front->next; //맨앞 옮기기
		free(temp); //메모리 반납
		h->length--;
	}
}
//오래기다린사람찾기: 오래기다린 사람 맨앞으로 옮기고 dequeue연산하기 
void findleave(hNode* h, int clock){
	if(h->length==0) return; //공백일떈 no
	qNode *before = NULL;
	qNode *temp = h->front;
	
	while(temp!=NULL){//노드 한바퀴 검사
		if(clock-temp->arrivalT > 2){//3번기다리면 out 
			//이미 맨앞
			if(before==NULL){
				dequeue(h);
				return;
			} 
			before->next = temp->next; //한칸이동
			
			//중간노드 삭제 
			temp->next = h->front; //맨앞의 노드를 가리킴 
			h->front = temp; //맨앞이 지금노드 
			
			//끝노드 삭제 
			if(temp==h->rear){
				h->rear = before;
			} 
			printf("[00:%d]시간초과로",clock);
			dequeue(h);
			return; 
		}
		//한칸씩이동 
		before = temp;
		temp = temp->next;
	} 
	/*
	hNode* delN;
	delN=(hNode*)malloc(sizeof(hNode));
	delN->front = h->front;
	delN->rear = h->front; //전노드 
	
	int i;
	for(i=0;i<h->length;i++){
		if(delN->front->arrivalT > clock+4){
			//연결끊김방지
			delN->rear->next = delN->front->next;
		 
			//삭제	
			delN->length = 1; //dequeue위해
			dequeue(delN); 
			
		}
		else {
			if(delN->rear!=delN->front){//같은 노드x 
				delN->rear = delN->front; 
			}
			delN->front = delN->front->next; //다음 노드 
		}
	} */
}
//출력함수
void qprint(hNode* h){
	int i;
	qNode* pp = h->front; //프린트할거 포인터 
	//pnode[h->length]; //프린트할 배열 정의
	printf("-> 큐 상태:"); 
	for(i=0;i<h->length-1;i++){ //끝 노드 전까지 화살표있게 
		//if(pp->next!=NULL){
		printf("%s->",pp->name);
		//pNode[i]= pp->name
		pp=pp->next;//다음노드 
		//}
	}
	printf("%s\n",pp->name); //마지막 노드 
	/*for(i=0;i<h->length;i++){
		printf("현재 큐 상태:%s\n",pp->name);
	}*/
	
} 

int main(int argc, char *argv[]) {
	//라면가게 자동 서빙 시스템 구현
	//0.공백큐
	hNode *waiting;
	waiting=(hNode*)malloc(sizeof(hNode));
	waiting->length = 0;
	waiting->front = waiting->rear = NULL;
	//1.요청 받기->시나리오 작성?
	
	//1.시간 시뮬레이션 시작
	int clock=0;
	int arrivalT=0; //고객 도착시간 
	int leaveT=2; //고객 떠나는 시간 //최소2 
	int aTvip=0; // 처음엔 안옴 
	int serverS; 
	//queue; 
	while(clock<11){ 
		clock=clock + 1;//시간증가 
		
		
		//1-1.새고객 삽입, 일반고객도착시간간격=1 
		if(clock>=arrivalT){//새고객 도착-> 대기삽입 
			char person[30]={0};
			printf("고객이름입력(없으면0):");
			scanf("%s",person);
			if(person[0]!='0'){
				enqueue(waiting, person,arrivalT);//삽입해라 //서비스대기
				printf("[00:%d]일반고객추가:%s\n",clock,person);
				
			}
			arrivalT=clock+1; //다음고객도착시간, 고객도착시간간격(1로 정의)
		}
		//1-1-2.VIP 도착, VIP도착 간격 =2
		if(clock>=aTvip){//새고객 도착-> 대기삽입 
			char vip[30]={0}; 
			printf("VIP이름입력(없으면0):");
			scanf("%s",vip);
			if(vip[0]!='0'){
				enqueue_front(waiting,vip,aTvip);//삽입해라 //서비스대기
				printf("[00:%d]VIP고객추가:%s\n",clock,vip);
				
			} 
			aTvip=clock+1; //다음고객도착시간, 고객도착시간간격(3 정의)
		}
		/*1-2.고객이떠남 
		if(clock>=leaveT){//고객떠남, 서비스완료 //처음에는 기계쉬고있음 
			serverS = 1; //서버 쉼 
		} 
		//1-3.고객한테 서비스 
		if(serverS==1&&waiting->length!=0){
			dequeue(waiting);//서비스하기 
			serverS=0;
			leaveT=clock+2;//고객의 서비스받는시간(2로가정)
		}*/
		//1-4.오래걸려서 떠남
		 
		findleave(waiting,clock);
		qprint(waiting);
		printf("-------------------------\n");
	}
	
	return 0;
}
