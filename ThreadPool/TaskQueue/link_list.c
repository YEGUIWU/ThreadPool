#include "link_list.h"
#pragma region ͨ��
//-----------------------------------------------------
void ListError(const char* errMsg)
{
	perror(errMsg);
}
//-----------------------------------------------------
void ListFailError(const char* errMsg)
{
	perror(errMsg);
	exit(-1);
}
//-----------------------------------------------------
//�����ݷ�װ�ɽ��
inline PtrToListNode MakeListNode(ListElementType elem)
{
	PtrToListNode p = calloc(1, sizeof(ListNode));
	if (p)
	{
		p->ELement = elem;
	}
	else
	{
		ListFailError("Alloc Error!\n");
	}
	return p;
}
//-----------------------------------------------------
//�ж�ĳ��λ���Ƿ�λ������Ľ�β
_Bool PosInListIsLast(ListPosition P)
{
	return P->Next == NULL;
}
//-----------------------------------------------------
//����ĳ�����
void DestroyListNode(PtrToListNode p)
{
	//free(p->ELement);
	free(p);
}
//-----------------------------------------------------
//��ȡ����ĵ�һ���ڵ��λ��
ListElementType FirstOfList(List L)
{
	return RetrieveFromListPos(HeadOfList(L));
}
//��ȡ��������һ��Ԫ��
ListElementType FinalOfList(List L)
{
	return RetrieveFromListPos(TailOfList(L));
}
//-----------------------------------------------------
//�ӽڵ�λ��ȡ��Ԫ�ص�ֵ
ListElementType RetrieveFromListPos(ListPosition P)
{
	return P->ELement;
}
//-----------------------------------------------------
//��ӡ����
void DisplayList(List L, void(*pDisplayFunc)(ListPosition))
{
	for (ListPosition p = HeadOfList(L); p; p = p->Next)
		pDisplayFunc(p);
}
//-----------------------------------------------------
/*  �����������  */

//-----------------------------------------------------
static void SwapNode(void* p1, void* p2, size_t size)
{
	void* pt = malloc(size);
	if (pt)
	{
		memcpy(pt, p1, size);
		memcpy(p1, p2, size);
		memcpy(p2, pt, size);
	}
	free(pt);
}
//-----------------------------------------------------
void SortList(PtrToListNode pHead, PtrToListNode pEnd, int(*pCmp)(ListElementType, ListElementType))
{
	if (pHead)
	{
		if (pHead != pEnd)
		{
			PtrToListNode pIndex = pHead;
			for (PtrToListNode pGo = pIndex->Next; pGo != pEnd; pGo = pGo->Next)
			{
				if (pCmp(pGo->ELement, pHead->ELement) > 0)
				{
					pIndex = pIndex->Next;
					SwapNode(pGo, pIndex, sizeof(ListNode));
					SwapNode(&pGo->Next, &pIndex->Next, sizeof(PtrToListNode));
				}
			}
			SwapNode(pIndex, pHead, sizeof(ListNode));
			SwapNode(&pIndex->Next, &pHead->Next, sizeof(PtrToListNode));

			SortList(pHead, pIndex, pCmp);
			SortList(pIndex->Next, pEnd, pCmp);
		}
	}
}
#pragma endregion



#ifdef SINGLE_LINK_LIST
//-----------------------------------------------------
//��ʼ������
void InitList(List* L)
{
	*L = NULL;
}
//-----------------------------------------------------
//�ж������Ƿ�Ϊ��
_Bool ListIsEmpty(List L)
{
	return L == NULL;
}
//-----------------------------------------------------
//����ĳ��Ԫ�ص�λ��
ListPosition FindInList(ListElementType X, List L)
{
	for (ListPosition P = L; P; P = P->Next)
	{
		if (P->ELement == X)
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
//����ĳ��Ԫ�ص�λ��
ListPosition FindIf(_Bool(*pFunc)(), List L)
{
	for (ListPosition P = L; P; P = P->Next)
	{
		if (pFunc(P->ELement))
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
//��������ɾ��ĳ��Ԫ��
void DeleteFromList(ListElementType X, List L)
{
	ListPosition P, TmpCell;
	P = FindPrePosFromList(X, L);
	if (!PosInListIsLast(P))
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}
//-----------------------------------------------------
//β����Ԫ��
List PushBack(ListElementType X, List L)
{
	if (!L)//�����
	{
		L = MakeListNode(X);
	}
	else
	{
		PtrToListNode p;
		for (p = L; p->Next; p = p->Next)
			;
		p->Next = MakeListNode(X);
	}
	return L;
}
//-----------------------------------------------------
//����ĳ��Ԫ�ص���һ��λ��
ListPosition FindPrePosFromList(ListElementType X, List L)
{
	for (ListPosition P = L; P->Next; P = P->Next)
	{
		if (P->Next->ELement == X)
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
//ͷ����Ԫ��
List PushFront(ListElementType X, List L)
{
	if (!L)
	{
		L = MakeListNode(X);

	}
	else
	{
		PtrToListNode p = MakeListNode(X);
		p->Next = L;
		L = p;
	}
	return L;
}
//-----------------------------------------------------
//ɾ��β��
List PopBack(List L)
{
	if (!L) //�ձ�
	{
		//do nothing
	}
	else if (!L->Next)//��1��Ԫ��
	{
		DestroyListNode(HeadOfList(L));
		L = NULL;
	}
	else //2������
	{
		PtrToListNode p;
		for (p = L; p->Next->Next; p = p->Next)
			;
		DestroyListNode(p->Next);
		p->Next = NULL;
	}
	return L;
}
//-----------------------------------------------------
//ɾ��ͷ��
List PopFront(List L)
{
	if (ListIsEmpty(L))
	{
		perror("List has nothing\n");
		return L;
	}
	PtrToListNode p = HeadOfList(L)->Next;
	DestroyListNode(HeadOfList(L));
	return p;
}
//-----------------------------------------------------
//��ĳ��λ�÷���ĳ��Ԫ��
void InsertToList(ListElementType X, ListPosition P)
{
	if (!P)
	{
		perror("Position is null!\n");
		return;
	}
	PtrToListNode TmpCell = MakeListNode(X);
	if (TmpCell)
	{
		TmpCell->ELement = X;
		TmpCell->Next = P->Next;
		P->Next = TmpCell;
	}
}
//-----------------------------------------------------
//�������
List DestroyList(List L)
{
	if (!ListIsEmpty(L))
	{
		for (ListPosition pcur = HeadOfList(L), pbark; pcur; pcur = pbark)
		{
			pbark = pcur->Next;
			free(pcur);
		}
	}

	return NULL;
}

//-----------------------------------------------------
//��ȡ����ͷ�ڵ�λ��
ListPosition HeadOfList(List L)
{
	return L;
}
//-----------------------------------------------------
//������һ��λ��
ListPosition AdvanceOfListPos(ListPosition P, List L)
{
	for (ListPosition pt = L; pt; pt = pt->Next)
	{
		if (P == pt->Next)
			return pt;
	}
	return NULL;
}
//��ȡ����β���λ��
ListPosition TailOfList(List L)
{
	ListPosition p = NULL;
	if (p)
	{
		for (; p->Next; p = p->Next)
			;//Do nothing
	}
	return p;

}
//-----------------------------------------------------
unsigned int ListSize(List L)
{
	ListPosition p = HeadOfList(L);
	unsigned int len = 0;
	while (p)
	{
		++len;
		p = p->Next;
	}
	return len;
}

#elif DOUBLE_LINK_LIST
//-----------------------------------------------------
//��ʼ������
void InitList(List* L)
{
	if (L != NULL);
	{
		L->Head = L->Tail = NULL;
		L->Length = 0;
	}
}
//-----------------------------------------------------
//�ж������Ƿ�Ϊ��
_Bool ListIsEmpty(List L)
{
	return L.Head == NULL;
}
//-----------------------------------------------------
//����ĳ��Ԫ�ص�λ��
ListPosition FindInList(ListElementType X, List L)
{
	for (ListPosition P = HeadOfList(L); P; P = P->Next)
	{
		if (P->ELement == X)
			return P;
	}
	return NULL;
}
ListPosition RFindInList(ListElementType X, List L)
{
	for (ListPosition P = TailOfList(L); P; P = P->Pre)
	{
		if (P->ELement == X)
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
//β����Ԫ��
List PushBack(ListElementType X, List L)
{
	if (ListIsEmpty(L))//�����
	{
		L.Head = MakeListNode(X);
		L.Tail = L.Head;
	}
	else
	{
		PtrToListNode NewNode = MakeListNode(X);
		TailOfList(L)->Next = NewNode;
		NewNode->Pre = TailOfList(L);
		L.Tail = NewNode;
	}
	++L.Length;
	return L;
}
//-----------------------------------------------------
//����ĳ��Ԫ�ص���һ��λ��
ListPosition FindPrePosFromList(ListElementType X, List L)
{
	for (ListPosition P = HeadOfList(L); P->Next; P = P->Next)
	{
		if (P->Next->ELement == X)
			return P;
	}
	return NULL;
}
//-----------------------------------------------------
//ͷ����Ԫ��
List PushFront(ListElementType X, List L)
{
	if (ListIsEmpty(L))//�����
	{
		L.Head = MakeListNode(X);
		L.Tail = L.Head;
	}
	else
	{
		PtrToListNode NewNode = MakeListNode(X);
		HeadOfList(L)->Pre = NewNode;
		NewNode->Next = HeadOfList(L);
		L.Head = NewNode;
	}
	++L.Length;
	return L;
}
//-----------------------------------------------------
//ɾ��β��
List PopBack(List L)
{
	if (!ListIsEmpty(L)) //�ձ�
	{
		//do nothing
	}
	else if (L.Head == L.Tail)//��1��Ԫ��
	{
		DestroyListNode(HeadOfList(L));
		L.Tail = L.Head = NULL;
		L.Length = 0;
	}
	else //2������
	{
		PtrToListNode Barkup = TailOfList(L)->Pre;
		DestroyListNode(TailOfList(L));
		L.Tail = Barkup;
		--L.Length;
	}
	return L;
}
//-----------------------------------------------------
//ɾ��ͷ��
List PopFront(List L)
{
	if (ListIsEmpty(L))
	{
		perror("List has nothing\n");
		return L;
	}
	PtrToListNode Barkup = HeadOfList(L)->Next;
	DestroyListNode(HeadOfList(L));
	L.Head = Barkup;
	--L.Length;
	return L;
}
//-----------------------------------------------------
//��ĳ��λ�÷���ĳ��Ԫ��
void InsertToList(ListElementType X, ListPosition P)
{
	if (!P)
	{
		perror("Position is null!\n");
		return;
	}
	PtrToListNode TmpCell = MakeListNode(X);
	if (TmpCell)
	{
		TmpCell->ELement = X;
		if (P->Next)//�������һ��λ��
		{
			P->Next->Pre = TmpCell;
			TmpCell->Next = P->Next;
			P->Next = TmpCell;
			TmpCell->Pre = P;
		}
		else
		{
			P->Next = TmpCell;
			TmpCell->Pre = P;
		}
		//TmpCell->Next = P->Next;
		//P->Pre->Next = TmpCell;
		//P->Pre = TmpCell;
	}
}

//-----------------------------------------------------
//��ȡ����ͷ�ڵ�λ��
ListPosition HeadOfList(List L)
{
	return L.Head;
}
//-----------------------------------------------------
//������һ��λ��
ListPosition AdvanceOfListPos(ListPosition P)
{
	return P->Pre;
}
//----------------------------------------------------
//��ȡ����β���λ��
ListPosition TailOfList(List L)
{
	return L.Tail;
}
//-----------------------------------------------------
unsigned int ListSize(List L)
{
	return L.Length;
}
//-----------------------------------------------------
//�������
List DestroyList(List L)
{
	if (!ListIsEmpty(L))
	{
		for (ListPosition pcur = HeadOfList(L), pbark; pcur; pcur = pbark)
		{
			pbark = pcur->Next;
			free(pcur);
		}
	}
	L.Head = L.Tail = NULL;
	L.Length = 0;
	return L;
}
#endif // SINGLE_LINKE_LIST