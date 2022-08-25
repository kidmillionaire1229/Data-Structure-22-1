#include <iostream>
void divide(int num1, int num2,int* num3, int *num);
int main(void) {
	int num1, num2;
	int q,r;
	std::cout<<"제수와 피제수를 입력하세요"<<std::endl;
	std::cin>>num1>>num2;

	try
	{
	divide(num1,num2,&q,&r);
		if(num2!=0){
                	std::cout<<"나눗셈의 몫은" << q <<"입니다"<< std::endl;
                	std::cout<<"나눗셈의 나머지는"<< r<<"입니다" <<std::endl;
                	}
        }
	catch(int expn){
	std::cout<<expn<<"으로는 나눌 수 없습니다."<<std::endl;
	std::cout<<"프로그램을 다시 실행하세요."<<std::endl;
	}
return 0;
}
	
void divide(int n1, int n2,int* n3,int *n4) {
	
	if(n2 ==0)
		throw n2;
	else{
	*n3 = n1/n2;
	*n4 = n1%n2;
	}

}



