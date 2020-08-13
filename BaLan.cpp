#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdlib.h>
using namespace std;
//---------------------
struct Node{
	string data;
	Node *pNext;
};
typedef struct Node NODE;
//---------------------
struct Stack{
	Node *pTop;
};
typedef struct Stack STACK;
//---------------------
struct List{
	Node *pHead;
	Node *pTail;
};
typedef struct List LIST;
typedef struct List QUEUE;
//---------------------
void InitStack(STACK &s){
	s.pTop = NULL;
}
//---------------------
void InitList(LIST &l){
	l.pHead = NULL;
	l.pTail = NULL;
}
//---------------------

NODE *InitNode(string str){
	NODE *p = new NODE;
	p->data = str;
	p->pNext = NULL;
	return p;
}
//---------------------
bool PushStack(STACK &s, NODE *p){
	if (s.pTop == NULL){
		s.pTop = p;
		return true;
	}
	p->pNext = s.pTop;
	s.pTop = p;
	return true;
}
//---------------------
bool PopStack(Stack &s, string &result){
	if (s.pTop == NULL){
		return false;
	}
	NODE *temp = s.pTop;
	s.pTop = s.pTop->pNext;
	result = temp->data;
	delete(temp);
	return true;
}

void OutputStack(STACK s){
	if (s.pTop == NULL){
		return;
	}
//	printf ("\n\n\t\tdsakhdjksadhksa\n\n");
	for (NODE *k = s.pTop; k != NULL; k = k->pNext){
		cout << k->data << " ";
		
	}
}

bool PushQueue(QUEUE &q, NODE *p){
	if (q.pHead == NULL){
		q.pHead = q.pTail = p;
		return true;
	}
	q.pTail->pNext = p;
	q.pTail = p;
	return true;
}

bool PopQueue(QUEUE &q, string &result){
	if (q.pHead == NULL){
		return false;
	}
	NODE *temp = q.pHead;
	q.pHead = q.pHead->pNext;
	result = temp->data;
	delete(temp);
	return true;
}

void OutputQueue(QUEUE q){
	if (q.pHead == NULL){
		return;
	}
	for (NODE *k = q.pHead; k != NULL; k = k->pNext){
		cout << k->data << " ";
	}
}

int Check(char x){
	if ( x == '+' || x == '-' || x == '*' || x == '/' || x == '%' || x == '^' ){
		return 1;
	}else if ( x == '(' || x == ')' ){
		return 0;
	}else if ( x >= '0' && x <= '9'){
		return -1;
	}
}

int UuTien(char x){
	if ( x == '+' || x == '-' ){
		return 1;
	}else if ( x == '*' || x == '/' || x == '%' ){
		return 2;
	}else if ( x == '%' ){
		return 3;
	}
}

int TinhToan(int int1, char s2, int int3){
	switch(s2){
		case '+':{
			return int1 + int3;
			break;
		}
		case '-':{
			return int1 - int3;
			break;
		}
		case '*':{
			return int1 * int3;
			break;
		}
		case '/':{
			return int1 / int3;
			break;
		}
		case '%':{
			return int1 % int3;
			break;
		}
		case '^':{
			return pow(int1, int3);
			break;
		}
	}
}
//---------------------
int main(){
	STACK s;
	QUEUE q;
	InitStack(s);
	InitList(q);
	ifstream FileIn;
	string MainString;
	FileIn.open("input.txt", ios_base::in);

	getline(FileIn, MainString);
	cout << endl << MainString;	

/*
	toan tu 1
	ngoac 0
	so -1
*/
//(5+3*6-(9/3)+7)
	int choose;
	printf ("\n");
	for (int i = 0; i < MainString.length(); i++){
		choose = Check(MainString[i]);
		printf ("%d ", choose);	
		switch(choose){
			case 0:{
				if (MainString[i] == '('){
//					printf ("\n((((((((((\n");
					string temp = "(";
					NODE *p = InitNode(temp);
					PushStack(s,p);
					printf ("\nStack sau khi push (: ");
					OutputStack(s);
					printf ("\n-----------------------\n");
				}else if (MainString[i] == ')'){
					string temp;
					while(1){
						PopStack(s,temp);
//						cout << "\nGia tri vua pop khoi stack: " << temp;
						if (temp == "("){
							break;
						}else{
							NODE *p = InitNode(temp);
							PushQueue(q,p);
						}	
					}
				}
				break;
			}
			case -1:{
				int Start = i;
				int End;                            
//				cout << "\ni ngoai dong for: " << i << endl;                			
				for (int j = i+1; j < MainString.length(); j++){  
					int temp = Check(MainString[j]);
					if (temp != -1){
						End = j;
//						cout << "\ni trong dong for: " << i << endl;
						i = j-1;
						break;
					}	
				}
				string numbers = MainString.substr(Start, End-Start);
//				cout << "\nSo: " << numbers << endl;
				NODE *p = InitNode(numbers);
				PushQueue(q,p);
				break;
			}
			case 1:{
				system("pause");
				int Diem;
				Diem = UuTien(MainString[i]);
				string temp;
				switch(MainString[i]){
					case '+':{
						temp = "+";
						break;
					}
					case '-':{
						temp = "-";
						break;
					}
					case '*':{
						temp = "*";
						break;
					}
					case '/':{
						temp = "/";
						break;
					}
					case '%':{
						temp = "%";
						break;
					}
				}
				if (s.pTop == NULL){
					NODE *p = InitNode(temp);
					PushStack(s,p);
					cout << "\nSTACK sau khi push lan dau: ";
					OutputStack(s);
				}
				else{
					string stringg = s.pTop->data;
					char chr = stringg[0];
					cout << "KY TU: " << chr;
					if (stringg == "("){
						NODE *p = InitNode(temp);
						cout << "\nStack sau khi push truoc (: ";
						PushStack(s,p);
						OutputStack(s);
					}else{
						int CurrentPoint = Check(MainString[i]);
						char PointString = s.pTop->data[0];
						int TopPoint = Check(PointString);
						if (CurrentPoint > TopPoint){
							NODE *p = InitNode(temp);
							cout << "\nStack sau khi push >: ";
							PushStack(s,p);
							cout << "\n-----------------------------";
						}else{
							printf ("\nTRUONG HOP <=\n");
							string TempString;
							while(CurrentPoint <= TopPoint){
								printf ("\nVao dong while\n");
								PopStack(s,TempString);
								NODE *p = InitNode(TempString);
								PushQueue(q,p);
								PointString = s.pTop->data[0];
								TopPoint = Check(PointString);
							}
							NODE * p = InitNode(temp);
							PushStack(s,p);
						}
					}
				}
				break;
			}
		}
	}
		/*
	if no la ( PUSH STACK
	if no la number PUSH QUEUE
	if ) POP STACK toi khi gap ( trong STACK ra
	va PUSH QUEUE
	if TOAN TU if stack rong~ push STACK
	else if TOAN TU HIEN TAI <= TOAN TU TRONG STACK 
	thi POP toan tu trong STACK ra PUSH QUEUE den khi THOA DIEU KIEN
	thi NGUNG roi PUSH TOAN TU HIEN TAI vao trong STACK
	(55+3+554)
	(
*/
	FileIn.close();
	printf ("\nXUAT CUOI CUNG\n");
	OutputStack(s);
	printf ("\n");
	OutputQueue(q);
// PHAN TINH TOAN;
	string string1, string2, string3;
	while(q.pHead != NULL){
		/*
			if number POP QUEUE roi PUSH STACK
			if No la toan tu
			POP STACK 2 lan roi tinh voi cai TOAN TU do
		*/
		char chr = q.pHead->data[0];
		if ( chr != '+' && chr != '-' && chr != '*' && chr != '/' && chr != '%' && chr != '^' ){
			string temp;
			PopQueue(q,temp);
			NODE *p = InitNode(temp);
			PushStack(s,p);
			cout << "STACK sau khi push phan2: ";
			OutputStack(s);
			cout << "\n-----------------------------\n";
			cout << "QUEUE sau khi push phan2: ";
			OutputQueue(q);
			cout << "\n-----------------------------\n";
		}else{
			string s1, s3;
			int number1,number3;
			int total;
			string null;
			PopQueue(q,null);
			PopStack(s,s1);
			PopStack(s,s3);
			cout << "\nKi tu vua pop khoi stack: " << s1;
			cout << "\nKi tu vua pop khoi stack: " << s3;
			number1 = atoi(s1.c_str());
			number3 = atoi(s3.c_str());
			total = TinhToan(number3, chr, number1);
			cout << "\nSo1: " << number1;
			cout << "\nToan tu: " << chr;
			cout << "\nSo3: " << number3;
			cout << "\nTong: " << total;
			char chrr[20];
			itoa(total, chrr, 10);
			NODE *p = InitNode((string)chrr);
			PushStack(s,p);
			cout << "STACK sau khi push tinh toan phan2: ";
			OutputStack(s);
			cout << "\n-----------------------------\n";
			cout << "QUEUE sau khi push tinh toan phan2: ";
			OutputQueue(q);
			cout << "\n-----------------------------\n";
		
		}
	}
	cout << "\n\n\nSTACK con lai\n\n";
	OutputStack(s);
//	"5+3*6-(9/3)+7"
// 	scanf ("%s", MainString);
//	puts(MainString);
//  ----------------
//	string temp;
//	string str;
//	printf ("\nNhap gia tri: ");
//	getline(cin, str);
//	NODE *p = InitNode(str);
//	PushQueue(q,p);
//	OutputQueue(q);
//	
//	printf ("\nNhap gia tri: ");
//	getline(cin, str);
//	p = InitNode(str);
//	PushQueue(q,p);
//	OutputQueue(q);
//	system("pause");
//	PopQueue(q,temp);
//	cout << "\nXuat sau khu pop";
//	OutputQueue(q);
//	cout << "\nGia tri vua pop: " << temp;
	return 0;
}












