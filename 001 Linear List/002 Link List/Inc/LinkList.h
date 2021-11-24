/*******************************************************************************
 * @file: LinkList.h
 * @author: sheer.rey
 * @date: Aug.16, 2021
 *
 * @attention In my version, the index of link list is beginning from 1,
 * rather than array(beginning from 0).
 *
 * @attention In this version, Link List has head node and the data field of
 * head node is the length of Link List (number of valid node, exclude head
 * node itself).
 *
 * @note
 * This pair of files, or, these series of file piars is my personal realization
 * of Data Structure in corresponding learning progress.
 *
 * So tip.1 I hope you know is there may be some slapdash mistake.
 *
 * Another thing is, the reason why I choose to use full english comment is I
 * want to improve my english level by this way.
 *
 * So tip.2 is if you find some grammatical error or others and tell me that
 * I will be very greatful to you! The style of these pair of files may be
 * variable, cause it's also in my C++ learning process, so the programme
 * style may transform C to C++ gradually.
 * ****************************************************************************/

#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include <string>

typedef int ElementType;

enum status
{
  llERROR,
  llCONFLICT,
  llFALSE,
  llTRUE,
  llOK
};

const std::string strSQErrorMessage[llOK + 1] = {
    "ERROR: Specific location is not in the Link List range!",
    "WARING: More than 1 identical element in Link List!",
    "",
    "",
    ""};

struct LinkList
{
  /* data */
  ElementType llData;
  LinkList *next;
};

status LinkList_Init(LinkList *L, int ilenth);
status LinkList_Delete(LinkList *L);
status LinkList_Empty(LinkList *L);
status LinkList_Clear(LinkList *L);
status LinkList_GetLenth(LinkList *L, int *LinkListLenth);
status LinkList_GetElement(LinkList *L, int i, ElementType *element);
status LinkList_LocateElement(LinkList *L, int *i, ElementType element);
status LinkList_InsertElement(LinkList *L, int i, ElementType element);
status LinkList_DeleteElement(LinkList *L, int i, ElementType *element);
void LinkList_print(LinkList *L);

#endif
