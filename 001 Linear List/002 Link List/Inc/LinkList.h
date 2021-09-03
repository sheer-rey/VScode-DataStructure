/*******************************************************************************
 * @file: LinkList.cpp
 * @author: sheer.rey
 * @date: Aug.16, 2021
 * @attention: In my version, the index of link list is beginning from 1, 
 * rather than array(beginning from 0).
 * 
 * @note:
 * This pair of files, or, these series of file piars is my personal realization
 * of Data Structure in corresponding learning progress. So tip.1 I hope you 
 * know is there may be some slapdash mistake.
 * Another thing is, the reason why I choose to use full english comment is I
 * want to improve my english level by this way. So tip.2 is if you find some
 * grammatical error or others and tell me that I will be very greatful to you!
 * The style of these pair of files may be variable, cause it's also in my C++
 * learning process, so the programme style may transform C to C++ gradually.
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

/*******************************************************************************
 * @name: LinkList_DeleteElement
 * @param: *L -- pointer to LinkList(return value)
 *         i -- location of list where element is going to be deleted
 *         *element -- the deleted element(return value)
 * @return: delete operation status(llOK or llERROR)
 * @brief: delete element in location given by i, and return deleted element
 * ****************************************************************************/
status LinkList_DeleteElement(LinkList *L, int i, ElementType *element);

/*******************************************************************************
 * @name: LinkList_print
 * @param: *L -- pointer to LinkList
 * @brief: print the elements of link list
 * ****************************************************************************/
void LinkList_print(LinkList *L);

/*******************************************************************************
 * @name: LinkList_print_all
 * @param: *L -- pointer to LinkList
 * @brief: print the whole memery value of link list, no matter how long
 * link lenth is
 * ****************************************************************************/
void LinkList_print_all(LinkList *L);

#endif
