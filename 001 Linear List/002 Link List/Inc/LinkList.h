/*******************************************************************************
 * @file: LinkList.cpp
 * @author: sheer.rey
 * @date: Aug.16, 2021
 * @attention: In my version, the index of sequence list is beginning from 1, 
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
  llOVERFLOW,
  llFALSE,
  llTRUE,
  llOK
};

const std::string strSQErrorMessage[llOK + 1] = {
    "ERROR: Specific location is not in the Sequence List range!",
    "WARING: More than 1 identical element in Sequence List!",
    "ERROR: Sequence List overflow!",
    "",
    "",
    ""};

struct LinkList
{
  /* data */
  ElementType llData;
  LinkList *next;
};

status LinkList_Init(LinkList *L,int ilenth);
status LinkList_Delete(LinkList *L);

/*******************************************************************************
 * @name: LinkList_Empty
 * @param: *L -- pointer to LinkList
 * @return: Sequence list empty status(llTRUE or llFALSE)
 * @brief: make sure if sequence list is empty
 * ****************************************************************************/
status LinkList_Empty(LinkList *L);

/*******************************************************************************
 * @name: LinkList_Clear
 * @param: *L -- pointer to LinkList(return value)
 * @return: Sequence list clear status(llOK)
 * @brief: clear whole sequence list
 * ****************************************************************************/
status LinkList_Clear(LinkList *L);

/*******************************************************************************
 * @name: LinkList_GetLenth
 * @param: *L -- pointer to LinkList
 *         *LinkListLenth -- pointer to current lenth of Sequence List(return Value)
 * @return: Get Sequence list lenth status(llOK)
 * @brief: Get the current lenth of Sequence List
 * ****************************************************************************/
status LinkList_GetLenth(LinkList *L, int *LinkListLenth);

/*******************************************************************************
 * @name: LinkList_GetElement
 * @param: *L -- pointer to LinkList
 *         i -- location of element which is going to get
 *         *element -- the element be get of sequence list(return value)
 * @return: get operation status(llOK or llERROR)
 * @brief: get the element given by variable i
 * ****************************************************************************/
status LinkList_GetElement(LinkList *L, int i, ElementType *element);

/*******************************************************************************
 * @name: LinkList_LocateElement
 * @param: *L -- pointer to LinkList
 *         *i -- location of given element in sequence list(return value)
 *         element -- the given element going to get of sequence list
 * @return: locate operation status(llOK, llFALSE or llCONFLICT)
 * @brief: get the location of given element
 * @note: status CONFLICT means there are more than 1 identical element in 
 * sequence list.
 *        status ERROR means given element cannot be found in sequence list.
 * ****************************************************************************/
status LinkList_LocateElement(LinkList *L, int *i, ElementType element);

/*******************************************************************************
 * @name: LinkList_InsertElement
 * @param: *L -- pointer to LinkList(return value)
 *         i -- location of list where given element is going to be inserted
 *         element -- the given element which is going to be inserted
 * @return: insert operation status(llOK, llsERROR or llOVERFLOW)
 * @brief: insert given element into specific location(given by i) of list
 * @note: while llLenth is 1, set the insert location to 2 means insert element at the end of sequence list.
 * ****************************************************************************/
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
 * @brief: print the elements of sequence list
 * ****************************************************************************/
void LinkList_print(LinkList *L);

/*******************************************************************************
 * @name: LinkList_print_all
 * @param: *L -- pointer to LinkList
 * @brief: print the whole memery value of sequence list, no matter how long
 * sequence lenth is
 * ****************************************************************************/
void LinkList_print_all(LinkList *L);

#endif
