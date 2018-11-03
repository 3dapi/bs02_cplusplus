
#include <Windows.h>
#include <stdio.h>


struct OBJECT
{
	int a;
	int b;
	int c;

	OBJECT():a(1), b(2), c(3){}
};

typedef OBJECT*	PDGE_OBJECT;


template<class T>
class TDGE_Node
{
protected:
	TDGE_Node<T>*	P;				// parent
	TDGE_Node<T>*	C;				// child
	TDGE_Node<T>*	B;				// previous
	TDGE_Node<T>*	N;				// next

	T*			A;				// attribute

public:
	TDGE_Node();
	TDGE_Node(TDGE_Node<T>*);
	virtual ~TDGE_Node();


	T*	 GetAttrib()		{	return A;	}
	void SetAttrib(const T& a){	A = (T*)&a;	}
	void SetAttrib(T* a)	{	A = (T*)a;	}
	void SetAttrib(int a)
	{
		A = (T*)a;
	}


	////////////////////////////////////////////////////////////////////////////
	// Node Iteration
	
	INT HasParent()		;				// Has parent?
	INT HasNotParent()	;				// Has no parent?
	INT HasChild()		;				// Has child?
	INT HasNotChild()	;				// Has no child?
	INT IsSiblingF()	;				// Am I first child?

	INT IsSiblingL()	;				// Am I last child?
	INT IsRoot()		;				// Am I root?
	INT IsChild()		;				// Am I Child?

	TDGE_Node<T>* GetSiblingF();		// find first node from sibling list
	TDGE_Node<T>* GetSiblingL();		// find last node from sibling list
	TDGE_Node<T>* FindRoot()	;		// find root node

	void AttachTo(TDGE_Node<T>* Prn);	// set the parent node. (I'm a child node)
	void Attach(TDGE_Node<T>* Ch);		// attach the child node. (I'm parent node)
	void Detach();						// detach
	INT CountNodes();					// count node
};

typedef TDGE_Node<PDGE_OBJECT >	VDGE_OBJECT;




////////////////////////////////////////////////////////////////////////////////
//Implementation of TDGE_NODE

template<class T> TDGE_Node<T>::TDGE_Node() : P(0), C(0), B(0), N(0){}


template<class T> TDGE_Node<T>::~TDGE_Node()
{
	Detach();									// detach from parent node
	if(0 == C) return;
	while(C) C->Detach();						// if has child
}


template<class T> INT TDGE_Node<T>::HasParent()	 {	return (0 != P);	}		// Has parent?

template<class T> INT TDGE_Node<T>::HasNotParent(){	return (0 == P);	}		// Has no parent?
template<class T> INT TDGE_Node<T>::HasChild()	 {	return (0 != C);	}		// Has child?
template<class T> INT TDGE_Node<T>::HasNotChild(){	return (0 == C);	}		// Has no child?
template<class T> INT TDGE_Node<T>::IsSiblingF() {	return (P&&P->C==this);}	// Am I first child?

template<class T> INT TDGE_Node<T>::IsSiblingL() {	return (P && 0 == N);	}	// Am I last child?
template<class T> INT TDGE_Node<T>::IsRoot()	 {	return (0 == P);		}	// Am I root?
template<class T> INT TDGE_Node<T>::IsChild()	 {	return (0 != P);		}	// Am I Child?

template<class T> TDGE_Node<T>* TDGE_Node<T>::GetSiblingF(){return (B)? B->GetSiblingF():this;}	// find first node from sibling list
template<class T> TDGE_Node<T>* TDGE_Node<T>::GetSiblingL(){return (N)? N->GetSiblingL():this;}	// find last node from sibling list
template<class T> TDGE_Node<T>* TDGE_Node<T>::FindRoot(){	return (P)? P->FindRoot():	 this;}	// find root node

template<class T> void TDGE_Node<T>::AttachTo(TDGE_Node<T>* pPrn)								// set the parent node. (I'm a child node)
{
	TDGE_Node<T>* pParentChild = NULL;
	TDGE_Node<T>* pSiblingLast = NULL;

	if(P)
		Detach();

	P = pPrn;													// set the parent node
	pParentChild =	P->C;

	if(!P->C)
	{
		P->C = this;
	}
	else
	{
		pSiblingLast = pParentChild->GetSiblingL();
		B = pSiblingLast;
		pSiblingLast->N = this;
	}
}

template<class T> void TDGE_Node<T>::Attach(TDGE_Node<T> *pCh)	// attach the child node. (I'm parent node)
{
	TDGE_Node<T>* pSiblingLast = NULL;

	if(pCh->HasParent())
		pCh->Detach();

	pCh->P = this;
	if(C)
	{
		pSiblingLast = C->GetSiblingL();
		pSiblingLast->N = pCh;
		pCh->B = pSiblingLast;
	}
	else
	{
		C = pCh;
	}
}

template<class T> void TDGE_Node<T>::Detach()
{
	if(P && P->C == this)
	{
		if(N)
		{
			P->C = N;	P->C->B = 0;
		}
		else
			P->C = 0;
	}

	if(B) B->N = N;
	if(N) N->B = B;

	P = 0; B = 0; N = 0;
}

template<class T> INT TDGE_Node<T>::CountNodes()
{
	return C? return C->CountNodes() + 1 : 1;
}





int main(int argc, char** argv)
{
	TDGE_Node<PDGE_OBJECT >	t1;
	TDGE_Node<PDGE_OBJECT >	t2;


	PDGE_OBJECT tttt= new OBJECT;

	t1.SetAttrib(tttt);



	t2.Attach(&t1);
	t1.AttachTo(&t2);
	t1.Detach();

	PDGE_OBJECT*	kk = t1.GetAttrib();

	//t1.SetAttrib( (OBJECT)NULL);

	t1.SetAttrib(NULL);

	return 0;
}
