#include <iostream>
#include <utility>

using namespace std; 

template <typename K, typename E> class Tree; 

//TreeNode 선언 
template<typename K, typename E>
class TreeNode
{
	friend class Tree<K,E>;
private:
	pair<K,E>*  data;
	TreeNode<K,E> * leftChild;
	TreeNode<K,E> * rightChild;
public:
	TreeNode(pair<K,E> *p);
	~TreeNode();
};

//Tree 선언 
template<typename K, typename E>
class Tree
{
private:
	TreeNode<K,E> *root; 
public: 
	Tree();
	~Tree();
       	void Destruct(TreeNode<K,E> *P);	
	void Insert(pair<K,E> *pair);
	const pair<K,E>* Get(const K k);
	const pair<K,E>* Get(TreeNode<K,E>* t, const K k);
	void Inorder();
	void Inorder(TreeNode<K,E>* currentNode);
	bool Delete(const K k);
};

//TreeNode 구현 
//TreeNode 생성자
template<typename K,typename E>
TreeNode<K,E>::TreeNode(pair<K,E> *p)
{
	data = p;
	leftChild =0;
	rightChild=0;
}
//TreeNode 소멸자 
template<typename K,typename E>
TreeNode<K,E>::~TreeNode()
{
	delete data;
}

//Tree구현 
//Tree 생성자 
template<typename K,typename E>
Tree<K,E>::Tree()
{
	root =0;
}
//Tree 소멸자 
template<typename K, typename E>
Tree<K,E>::~Tree()
{
	Destruct(root); 
}
//Destruct 함수 (소멸자에서 호출)
template<typename K, typename E>
void Tree<K,E>::Destruct(TreeNode<K,E> *p)
{
	if(p)
	{
	Destruct(p->leftChild);
	Desturct(p->rightChild);
	delete p->data;
	delete p;
	}
}
//Insert 함수 
template<typename K,typename E>
void Tree<K,E>::Insert(pair<K,E> *pair)
{
 	TreeNode<K,E> *p = root; 
	TreeNode<K,E> *pp =0;
	bool is_left = true;
	while(p)
	{
		pp=p;
		if(pair->first<p->data->first)
		{
			p=p->leftChild;
			is_left = true;
		}
		else if(pair->first > p->data->first)
		{	
			p=p->rightChild;
			is_left = false; 
		}
		else
			{p->data->second = pair->second; return;}
	}

	p = new TreeNode<K,E>(pair);

	if(root==0)
		root =p;
	else 
	{
		if(is_left)
			pp->leftChild = p; 
		else 
			pp->rightChild =p; 	
	}
}

//Get 함수 
template<typename K, typename E>
const pair<K,E>* Tree<K,E>::Get(const K k)
{
	return Get(root,k);
}


template<typename K, typename E>
const pair<K,E>* Tree<K,E>::Get(TreeNode<K,E>* t, const K k)
{
	
	if(!t) 
		return 0;
	else if(k < t->data->first)
		return Get(t->leftChild, k);
	else if(k > t->data->first)
		return Get(t->rightChild, k);
	else 
		return t->data;
	
}

template<typename K, typename E>
void Tree<K,E>::Inorder()
{
	Inorder(root);
}

template<typename K, typename E>
void Tree<K,E>::Inorder(TreeNode<K,E> *currentNode)
{
	if(currentNode)
	{
	Inorder(currentNode->leftChild);
	cout<< "("<<currentNode->data->first<<","<<currentNode->data->second<<")"<<endl;
	Inorder(currentNode->rightChild);
	}
}



template<typename K, typename E>
bool Tree<K,E>::Delete(const K k)
{
	TreeNode<K,E> *p = root;
	TreeNode<K,E> *pp=0;
	bool is_left_child = false;
while(true) //true값 찾는 과정
{
	if(p==0)
		return false; // key값 못 찾음// 삭제 불가
	
	
	if(p->data->first == k)	//key값 찾음// while문 탈출
		break;	
	else
	{		//못 찾았으니 내려감
		pp=p;
		if(p->data->first > k)
		{
			p=p->leftChild;
			is_left_child = true;
		}
		else if(p->data->first <k)
		{
			p = p->rightChild;
			is_left_child = false;
		}	
	}	
}//While문 끝 // 삭제하려는 key찾음 


if(p->leftChild==0) //오른쪽 자식만 있을 때
{
	if(p==root)
		root = p->rightChild;
	else if(is_left_child)
		pp->leftChild = p->rightChild;
	else 
		pp->rightChild = p->rightChild;
}
else if(p->rightChild==0)  //왼쪽 자식만 있을 때
{
	if(p==root)
		root = p->leftChild; 
	else if(is_left_child)
		pp->leftChild = p->leftChild;
	else 
		pp->rightChild = p->leftChild;
}
else		//왼쪽, 오른쪽 자식 둘 다 있는 경우
{
	pp=p;
	TreeNode<K,E>* right = p->rightChild;	//삭제해야 할 노드 탐색용
	is_left_child = false; 			//삭제해야 할 노드의 방향 
	while(right->leftChild!=0)
	{
		pp=right;
		right=right->leftChild;
		is_left_child = true;
	}

	p->data->first= right->data->first;
	p->data->second = right->data->second;

	if(is_left_child)		//while문 탈출 한 후, right의 왼쪽 노드는 존재하지 않는다. 
		pp->leftChild = right->rightChild;
	else 
		pp->rightChild = right->rightChild;
}
	return true;
}

int main(void) 
{
	Tree<int,int>* tree = new Tree<int,int>();
	
	tree->Insert(new pair<int,int>(20220033,90));
	tree->Insert(new pair<int,int>(20220050,73));
	tree->Insert(new pair<int,int>(20220043,99));
	tree->Insert(new pair<int,int>(20220011,82));
	tree->Insert(new pair<int,int>(20220024,78));
	tree->Insert(new pair<int,int>(20220046,96));
	tree->Insert(new pair<int,int>(20220001,72));
	tree->Insert(new pair<int,int>(20220008,88));
	tree->Insert(new pair<int,int>(20220036,77));
	tree->Insert(new pair<int,int>(20220056,93));
	tree->Insert(new pair<int,int>(20220053,82));
	tree->Insert(new pair<int,int>(20220059,100));

	cout<<"초기값"<<endl;	
	tree->Inorder();
	
	cout<<"20220050 삭제후"<<endl;
	if((tree->Delete(20220050))==false)
			cout<<"삭제할 원소가 존재 하지 않습니다"<<endl;
	else
			tree->Delete(20220050);

	tree->Inorder();

	cout<<"20220008번 삭제"<<endl;
	if((tree->Delete(20220008))==false)
		cout<<"삭제할 원소가 존재 하지 않습니다."<<endl;
	else	
		tree->Delete(20220008);
	
	tree->Inorder();


	cout<<"20220056번 삭제"<<endl;
	if((tree->Delete(20220056))==false)
		cout<<"삭제할 원소가 존재 하지 않습니다."<<endl;
	else	
		tree->Delete(20220056);

	tree->Inorder();

	cout<<"20220056번 노드가 있는 지 확인 후 출력: ";
	if(tree->Get(2022056)==0)
		cout<<"해당 키의 원소가 존재 하지 않습니다"<<endl;
	else	
		cout<< "("<<tree->Get(20220056)->first<<","<<tree->Get(20220056)->second<<")"<<endl;
	
	cout<<"20220043번 노드가 있는 지 확인 후 출력: ";
	if(tree->Get(20220043)==0)
			cout<<"해당 키의 원소가 존재하지 않습니다"<<endl;
	else
			cout<< "("<<tree->Get(20220043)->first<<","<<tree->Get(20220043)->second<<")"<<endl;

}

