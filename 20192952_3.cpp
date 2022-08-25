#include <iostream>
#include <numeric>
using namespace std; 

template <typename T> class Chain;
//ChainNode 템플릿  
template <typename T> 
class ChainNode
{
friend class Chain<T>;
private:
	T* data;
	ChainNode<T> *link;
public:
	ChainNode(int element, ChainNode* next=0);//ChainNode 생성자
	~ChainNode();				//ChainNode 소멸자 		
	T* getData();				//T형 data 주소 반환 
};

//Chain 템플릿 
template <typename T>
class Chain
{
public:
	Chain();					//Chain 초기 생성자
	~Chain();					//Chain 소멸자 
	void InsertFront(ChainNode<T> *a);		//체인의 맨 앞에 원소 삽입
	void InsertLast(ChainNode<T> *a);		//체인의 맨 뒤에 삽입 삽입
	ChainNode<T>* Front();				//리스트의 첫 원소를 반환
        ChainNode<T>* Back();				//리스트의 마지막 원소를 반환
	ChainNode<T>* Get(int i);			//리스트의 i번째 원소를 반환
	void DeleteFront();				//체인의 맨 앞 원소 삭제
	void DeleteLast();				//체인의 맨 뒤 원소 삭제
	void InsertBack(int i,ChainNode<T> *a);		//i번째 원소 뒤에 삽입
	void Delete(int i);				//i번째 원소 삭제	
class ChainIterator //내부 공용 중첩 클래스 ChainIterator 
	{
	public:
		ChainIterator(ChainNode<T>* startNode=0);//ChainIterator 생성자
		T& operator*() ;		//*연산자//T데이터 자체 반환  
		T* operator->();		//->연산자//T데이터 주소반환 
		ChainIterator& operator++();	//전위연산자
		ChainIterator operator++(int);	//후위연산자
		bool operator!=(const ChainIterator right) const;	
		bool operator==(const ChainIterator right) const;	
		ChainNode<T>* getCurrent();
		void reset(ChainNode<T>* i);	//반복자 초기화 
	private:
		ChainNode<T>* current; 
	};
private:
	ChainNode<T>* first;		//체인에서 첫 원소를 가리키는 포인터 
};

//Number 클래스 
class Number 
{
private:
	int num;
public:
	Number(int n):num(n){}			//생성자
	void ShowData(){cout<<num<<endl;}	//num 출력 
	Number* operator->()			//->연산자 오버로딩
	{
		return this;
	}
	Number& operator*()			//*연산자 오버로딩
	{
		return *this;
	}	
	Number operator+(Number n)		//+연산자 오버로딩
	{
		return Number(num+n.num);
	}
};

//[ChainNode] 구현
//생성자 
template <typename T>
ChainNode<T>::ChainNode(int element, ChainNode<T>* next)
{
	data = new Number(element);
	link=next;
}
//ChainNode 소멸자 
template <typename T>
ChainNode<T>::~ChainNode()
{
delete data; 
};		 		

//getData함수 
template <typename T>
T* ChainNode<T>::getData()
{
	return data;
}

//[Chain]구현 
//생성자 구현 
template <typename T>
Chain<T>::Chain(){first=0;}

//소멸자 구현 
template <typename T>
Chain<T>::~Chain()
{
	ChainNode<T>* temp;
	while(first){
	temp=first;
	first=first->link;
	delete temp;
	}	
}

//InsertFront 구현 
template <typename T>
void Chain<T>::InsertFront(ChainNode<T> *a)
{
 	if(first)					//비어있지 않을 때 
	{
		a->link=first;	
		first=a;
	}
	else						//비어있을 때
		first=a;
}

//InsertLast 구현 
template <typename T>
void Chain<T>::InsertLast(ChainNode<T> *a)
{
Chain<T>::ChainIterator yi(Front());
if(first==0)				//비어있을 때
	first =a;
else					//비어있지 않을 때
	{
	while(true)	
	{	
		if(yi.getCurrent()->link==0)
			break;
		++yi;
	}
yi.getCurrent()->link=a;
a->link=0;
	}
}
//Front 구현
template <typename T>
ChainNode<T>* Chain<T>::Front()
{return first;}				

//Back 구현 
template <typename T>
ChainNode<T>* Chain<T>::Back()
{
Chain<T>::ChainIterator yi(first);
	while(true)
	{
		if(yi.getCurrent()->link==0)
			break;
		++yi;
	}
return yi.getCurrent();					
}

//Get구현
template <typename T>
ChainNode<T>* Chain<T>::Get(int i)
{
Chain<T>::ChainIterator yi(first);
for(int k=0;k<i;k++)
{	
	++yi;
}
return yi.getCurrent(); 
}

//DeleteFront 구현 
template <typename T>
void Chain<T>::DeleteFront()
{
if(first)		//비어있지 않을 때
	first=first->link;
else 			//비어있을 때
	cout<<"빈 체인입니다"<<endl;
}

//DeleteLast 구현 
template <typename T>
void Chain<T>::DeleteLast()
{
Chain<T>::ChainIterator yi(first);
if(first)		//비어있지 않을 때 
	{
	while(true)
	{
		++yi;		
		if(yi.getCurrent()->link->link==0)
			break;
	}	
yi.getCurrent()->link=0; //끝에서 두번째 노드가 가리키는 link의 값이 0을 만들면 된다.
	}
else 
	cout<<"빈 노드입니다."<<endl;
}

//InsertBack 구현
template <typename T>
void Chain<T>::InsertBack(int i,ChainNode<T> *a)
{
Chain<T>::ChainIterator yi(first);
for(int k=0;k<i;k++)
{	
	++yi;
}
a->link=yi.getCurrent()->link;
yi.getCurrent()->link=a;
}

//Delete구현 
template <typename T>
void Chain<T>::Delete(int i)
{
Chain<T>::ChainIterator a(first);
Chain<T>::ChainIterator b(first);
if(first)	//비어있지 않을 때
{
	for(int count=0;count<i-1;count++)
	{
		++a;			//삭제 노드 전까지는 전위 연산자
	}
b=a++; 			//원본 주면 안됨//b에 현재 노드 복사본 주고 //a는 하나더 점프(삭제 노드) 가리킴// a는 삭제노드// b는 그 전꺼 가리킴 	
b.getCurrent()->link=a.getCurrent()->link;
}
else		//비어있을 때
	cout<<"빈노드입니다"<<endl;
}


//[Chain]::[ChainIterator] 
//ChainIterator 생성자
template <typename T>
Chain<T>::ChainIterator::ChainIterator(ChainNode<T>* startNode){current=startNode;};

template<typename T>
T& Chain<T>::ChainIterator::operator*() {return *(current->data);}			//*연산자 

template<typename T>
T* Chain<T>::ChainIterator::operator->() {return current->data;}			//->연산자

template <typename T>
typename Chain<T>::ChainIterator& Chain<T>::ChainIterator::operator++(){current=current->link; return *this;}					//전위연산자//ChainIterator의 참조자 반환

template <typename T>
typename Chain<T>::ChainIterator Chain<T>::ChainIterator::operator++(int){ChainIterator old=*this; current=current->link;return old;}				//후위연산자//ChainIterator의 복사본 전달

template <typename T>
bool Chain<T>::ChainIterator::operator!=(const ChainIterator right) const{return current!=right.current;}	

template <typename T>
bool Chain<T>::ChainIterator::operator==(const ChainIterator right) const{return current==right.current;}

template <typename T>
ChainNode<T>* Chain<T>::ChainIterator::getCurrent(){return current;}

template <typename T>
void Chain<T>::ChainIterator::reset(ChainNode<T>* i){current=i;}	

int main(void)
{

	Chain<Number> *ch = new Chain<Number>();
        
	ChainNode<Number>* n1 = new ChainNode<Number>(1,0);
	ch->InsertFront(n1);

	ChainNode<Number>* n2 = new ChainNode<Number>(2,0);
	ch->InsertLast(n2);

	ChainNode<Number>* n3 = new ChainNode<Number>(3,0);
	ch->InsertLast(n3);
		
	ChainNode<Number>* n4 = new ChainNode<Number>(4,0);
	ch->InsertLast(n4);

	ChainNode<Number>* n5 = new ChainNode<Number>(5,0);
	ch->InsertLast(n5);	
	
	ChainNode<Number>* n6 = new ChainNode<Number>(6,0);
	ch->InsertLast(n6);	
	
	ChainNode<Number>* n7 = new ChainNode<Number>(7,0);
	ch->InsertLast(n7);
	
	ChainNode<Number>* n8 = new ChainNode<Number>(8,0);
	ch->InsertLast(n8);	
	
	ChainNode<Number>* n9 = new ChainNode<Number>(9,0);
	ch->InsertLast(n9);	
	       		
	Chain<Number>::ChainIterator end(ch->Back());	//마지막 노드 가리키는 반복자
	Chain<Number>::ChainIterator start(ch->Front());//처음 노드 가리키는 반복자
	
	cout<<"<테스트 2번:초기데이터 출력>"<<endl;
	while(true){
		start->ShowData();
		if(start==end)
		{
			break;	
		}
		start++;
	}
		
	ChainNode<Number>* n0= new ChainNode<Number>(0,0);
	ch->InsertFront(n0);

	cout<<"테스트 4번:0노드 추가 후>"<<endl;
	start.reset(ch->Front());//start 반복자 처음 가리키게 초기화

	while(true){
		
		start->ShowData();
		if(start==end)
		{
			break;	
		}
		start++;
	}

	ChainNode<Number>* n10 = new ChainNode<Number>(10,0);
	ch->InsertLast(n10);
	
	end.reset(ch->Back());//end 반복자 마지막 가리키게 초기화
	start.reset(ch->Front());//start반복자 처음 가리키게 초기화

	cout<<"<테스트 6번: 10노드 추가후>"<<endl;	
	while(true){
		start->ShowData();
		if(start==end)
		{
			break;	
		}
		start++;
	}

	cout<<"<테스트 7번: Front()호출을 통해 처음노드 반환 후 값 출력>"<<endl;
	ch->Front()->getData()->ShowData();
	
	cout<<"<테스트 8번: Back()호출을 통해 마지막 노드 반환 후 값 출력>"<<endl;
	ch->Back()->getData()->ShowData();

	cout<<"테스트 9번 Get(2)호출을 통해 2번째 노드 반환 후 값 출력"<<endl;
	ch->Get(2)->getData()->ShowData();

	cout<<"<테스트 11번: 처음 노드 삭제후>"<<endl;

	ch->DeleteFront();
	start.reset(ch->Front());//start반복자 처음 가리키게 초기화
	while(true){
		start->ShowData();
		if(start==end)
		{
			break;	
		}
		start++;
	}

	cout<<"<테스트 12번 마지막 노드 삭제후>"<<endl;
	ch->DeleteLast();
	end.reset(ch->Back());//end 반복자 마지막 가리키게 초기화	
	start.reset(ch->Front());//start 반복자 처음 가리키게 초기화	
	while(true){
		start->ShowData();
		if(start==end)
		{
			break;	
		}
		start++;
	}
	
	cout<<"<테스트 15: 100노드 2번째 노드 다음 삽입 후>"<<endl;
	ChainNode<Number> *n100= new ChainNode<Number>(100,0);

	ch->InsertBack(2,n100);

	start.reset(ch->Front());//start 반복자 처음 가리키게 초기화
	end.reset(ch->Back());	//end 반복자 마지막 가리키게 초기화
	while(true){
		start->ShowData();
		if(start==end)
		{
			break;	
		}
		start++;
	}

	cout<<"<6번째 원소 삭제후>"<<endl;
	ch->Delete(6);
	

	start.reset(ch->Front());//start 반복자 처음 가리키게 초기화
	end.reset(ch->Back());//end 반복자 마지막 가리키게 초기화

	Number n(0);				//초기값 0인 Number객체 			
	cout<<"테스트 17번:전체 노드의 총합>"<<endl;		
	accumulate(start,++end,n).ShowData();   //accumulate는 끝 범위 포함 안하므로, ++end후 인자로 대입


return 0;
}
