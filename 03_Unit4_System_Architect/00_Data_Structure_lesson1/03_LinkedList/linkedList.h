/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 02_Linked_List
// File          : linkedList.h
// Date          : 28 Nov 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


typedef struct 
{
	uint32 ID;
	uint8 name[40];
	float64 height ;
}ST_studentData_t;

typedef struct linkedListNode   ST_linkedListNode_t;

struct linkedListNode
{
	ST_studentData_t ST_uddtStudentData;
	ST_linkedListNode_t *P_nextStudentNode;

};

typedef enum
{
	LINKED_LIST_NOK = 0,
	LINKED_LIST_OK,
	LINKED_LIST_IS_FULL,
	LINKED_LIST_IS_EMPTY,
	LINKED_LIST_IS_NULL,
	LINKED_LIST_PTR_NULL,
	LINKED_LIST_FOUND_LOOP,
	LINKED_LIST_INDEX_OUT_OF_RANGE
}EN_LINKEDLIST_status_t;

EN_LINKEDLIST_status_t  LINKEDLIST_uddtAddRecord(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t  LINKEDLIST_uddtFillRecord(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t  LINKEDLIST_uddtDeleteRecord(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t  LINKEDLIST_uddtViewRecords(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t  LINKEDLIST_uddtDeleteAllRecords(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t  LINKEDLIST_uddtGetNthNode(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t  LINKEDLIST_uddtGetNthNodeFromTheEnd(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t  LINKEDLIST_uddtGetLengthIterative(ST_linkedListNode_t *PS_copyUddtLinkedList);
uint32  				LINKEDLIST_u32GetLengthRecursive(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t  LINKEDLIST_uddtGetMiddleNode(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t  LINKEDLIST_uddtDetectLoop(ST_linkedListNode_t *PS_copyUddtLinkedList);
EN_LINKEDLIST_status_t LINKEDLIST_uddtReverseRecords(ST_linkedListNode_t* PS_copyUddtLinkedList);


#endif /* LINKEDLIST_H_ */
