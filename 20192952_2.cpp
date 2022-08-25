#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
//클래스 Bizcard 
class Bizcard
{
private:
	char * name;
	char * address;
	long long int office_phone;
	long long int mobile_phone;
public:
	//생성자
	Bizcard()
	{
	name = new char[sizeof(name)+1];
	address = new char[sizeof(address)+1];
	office_phone=1000L;
	mobile_phone=10000L;
	}
	
	Bizcard(const char *n, const char*a,long long int temp1,long long int temp2):office_phone(temp1),mobile_phone(temp2)
	{
	name = new char[strlen(n)+1];
	strcpy(name,n);
	address = new char[strlen(a)+1];
	strcpy(address,a);
	} 
	
	//복사생성자
	Bizcard(const Bizcard& copy):office_phone(copy.office_phone),mobile_phone(copy.mobile_phone)
	{
	name = new char[strlen(copy.name)+1];
	strcpy(name,copy.name);
	address = new char[strlen(copy.address)+1];
	strcpy(address,copy.address);
	}
	
	//대입연산자 
	Bizcard& operator=(const Bizcard& ref)
	{
	mobile_phone=ref.mobile_phone;
	office_phone = ref.office_phone;
	name = new char[strlen(ref.name)+1];
	strcpy(name,ref.name);
	address = new char[strlen(ref.address)+1];
	strcpy(address,ref.address);	
	return *this;
	}

	//소멸자
	~Bizcard()
	{
	delete name;
	delete address;
	}
	
	//내용 출력 함수
	void ShowInfo()
	{
	cout<<"이름: "<<name<<endl;
	cout<<"주소: "<<address<<endl;
	cout<<"업무 번호: "<<office_phone<<endl;
	cout<<"개인 번호: "<<mobile_phone<<endl;
	}
};

//Bag 템플릿 
template <typename T>
class Bag 
{
public:
	Bag(int bagCapacity=3);
	~Bag();

	int Size() const;
	bool IsEmpty() const;
	T& Element() const;
	
	void Push(const T&);
	void Pop();
	void ChangeSize1D(T*&, const int, const int);
private:
	T* array;
	int capacity;
	int top;
};

//생성자 구현
template <typename T>
Bag<T>::Bag(int bagCapacity):capacity(bagCapacity)
{
if(capacity<1)	cout<< "capacity must be >0"<<endl;
array = new T[capacity];
top = -1;	
}

//소멸자 구현
template <typename T>
Bag<T>::~Bag()
{
delete[] array; 
}

//push 함수 구현
template <typename T>
void Bag<T>::Push(const T& x)
{
if(capacity==top+1)ChangeSize1D(array,capacity,capacity*2);
capacity *=2;
array[++top]=x;
}

//pop 함수 구현 
template <typename T>
void Bag<T>::Pop()
{
srand((unsigned int)time(NULL));
if (IsEmpty())	throw "Bag is empty,cannot delete";
int deletePos = rand()%(top+1);
copy(array+deletePos+1,array+top+1,array+deletePos);
array[top--].~T();
}

//Size 함수 구현
template <typename T>
int Bag<T>::Size() const
{
	return top+1; 
}

//IsEmpty 함수 구현 
template <typename T>
bool Bag<T>::IsEmpty() const
{
if(top==-1)
	return true;
else 
	return false;
}

//Element 함수 구현
template <typename T>
T& Bag<T>::Element() const
{
srand((unsigned int)time(NULL));
if(IsEmpty())throw "Bag is Empty";
return array[rand()%(top+1)];
}

//ChangeSize1D구현
template<typename T>
void Bag<T>::ChangeSize1D(T*&a, const int oldSize, const int newSize)
{
if(newSize<0)throw"new size must be >0";	
T* temp = new T[newSize];
int number = min(oldSize,newSize);
copy(a,a+number,temp);
delete[] a;
a=temp;
}

//main함수
int main(void)
{

Bag<Bizcard> b1; 

//빈 백
cout<<"<1>빈백"<<endl;
cout<<"크기: "<<b1.Size()<<endl;
if(b1.IsEmpty())
	cout<<"empty"<<endl;
else
	cout<<"not empty"<<endl;
try{
b1.Element().ShowInfo();
}
catch(const char *s)
{
cout<<s<<endl;
}

//3개 push후
cout<<"<2>3개 push"<<endl;
Bizcard n1("kanye","seoul",10000000000LL,10000000001LL);
Bizcard n2("kendrick","busan",10000000002LL,10000000003LL);
Bizcard n3("tyler","jeju",10000000004LL,10000000005LL);

b1.Push(n1);
b1.Push(n2);
b1.Push(n3);

cout<<"크기: "<<b1.Size()<<endl;

if(b1.IsEmpty())
	cout<<"empty"<<endl;
else
	cout<<"not empty"<<endl;

b1.Element().ShowInfo();

//4개 Push후
cout<<"<3>4개 push"<<endl;
Bizcard n4("asap","kangwon",10000000006LL,10000000007LL);
Bizcard n5("jayz","wanju",10000000008LL,10000000009LL);
Bizcard n6("snoop","daegu",10000000010LL,10000000011LL);
Bizcard n7("changmo","deokso",10000000012LL,10000000013LL);

b1.Push(n4);
b1.Push(n5);
b1.Push(n6);
b1.Push(n7);

cout<<"크기: "<<b1.Size()<<endl;
if(b1.IsEmpty())
	cout<<"empty"<<endl;
else
	cout<<"not empty"<<endl;
b1.Element().ShowInfo();

//2개 pop후
cout<<"<4>2개 pop"<<endl;
b1.Pop();
b1.Pop();

cout<<"크기: "<<b1.Size()<<endl;

if(b1.IsEmpty())
	cout<<"empty"<<endl;
else	
	cout<<"not empty"<<endl;

b1.Element().ShowInfo();
return 0;
}
















