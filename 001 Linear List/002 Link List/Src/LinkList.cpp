/*******************************************************************************
 * @file SQList.cpp
 * @author sheer.rey
 * @date Aug.16, 2021
 * @attention In my version, the index of link list is beginning from 1, 
 * rather than array(beginning from 0).
 * @attention In this version, Link List has head node and the data field of
 * head node is the length of Link List (number of valid node, exclude head
 * node itself).
 * 
 * @note
 * This pair of files, or, these series of file piars is my personal realization
 * of Data Structure in corresponding learning progress. So tip.1 I hope you 
 * know is there may be some slapdash mistake.
 * Another thing is, the reason why I choose to use full english comment is I
 * want to improve my english level by this way. So tip.2 is if you find some
 * grammatical error or others and tell me that I will be very greatful to you!
 * The style of these pair of files may be variable, cause it's also in my C++
 * learning process, so the programme style may transform C to C++ gradually.
 * ****************************************************************************/
#include <cstdlib>
#include "LinkList.h"

/*******************************************************************************
 * @name LinkList_Init
 * @param L pointer to LinkList(return value)
 * @param iLenth Initiative lenth of linklist
 * @return Initialization status(llOK)
 * @brief Initialize the linklist with random value of given lenth
 * *****************************************************************************/
status LinkList_Init(LinkList *L, int iLenth)
{
  LinkList *j = L;
  /* Head Node */
  j->llData = iLenth;
  j->next = new LinkList;
  j = j->next;
  /* Valid Node */
  for (int i = 0; i < iLenth; i++)
  {
    j->next = new LinkList;
    j = j->next;
    j->llData = rand() % 100;
  }
  j->next = NULL;
  return llOK;
}

/*******************************************************************************
 * @name LinkList_Delete
 * @param L pointer to LinkList(return value)
 * @return Delete status(llOK)
 * @brief Delete the link list and free the memery space
 * ****************************************************************************/
status LinkList_Delete(LinkList *L)
{
  LinkList *i = L;
  while (L->next != NULL)
  {
    L = L->next;
    delete i;
    i = L;
  }
  delete i;
  return llOK;
}

/*******************************************************************************
 * @name LinkList_Empty
 * @param L pointer to LinkList
 * @return Link list empty status(llTRUE or llFALSE)
 * @brief make sure if link list is empty
 * ****************************************************************************/
status LinkList_Empty(LinkList *L)
{
  if (L->llData)
    return llFALSE;
  else
    return llTRUE;
}

/*******************************************************************************
 * @name LinkList_Clear
 * @param L pointer to LinkList(return value)
 * @return Link list clear status(llOK)
 * @brief clear whole link list but keep head node
 * ****************************************************************************/
status LinkList_Clear(LinkList *L)
{
  L->llData = 0;
  LinkList *i = L->next;
  L->next = NULL;
  L = i;
  while (i->next != NULL)
  {
    L = L->next;
    delete i;
    i = L;
  }
  delete i;
  return llOK;
}

/*******************************************************************************
 * @name LinkList_GetLenth
 * @param L pointer to LinkList
 * @param LinkListLenth pointer to current lenth of Link List(return Value)
 * @return Get Link list lenth status(llOK)
 * @brief Get the current lenth of Link List
 * ****************************************************************************/
status LinkList_GetLenth(LinkList *L, int *LinkListLenth)
{
  *LinkListLenth = L->llData;
  return llOK;
}

/*******************************************************************************
 * @name LinkList_GetElement
 * @param L pointer to LinkList
 * @param i location of element which is going to get
 * @param element the element be get of link list(return value)
 * @return get operation status(llOK or llERROR)
 * @brief get the element given by variable i
 * ****************************************************************************/
status LinkList_GetElement(LinkList *L, int i, ElementType *element)
{
  if (i > L->llData)
    return llERROR;
  do
  {
    L = L->next;
    i--;
  } while (i > 0);
  *element = L->llData;
  return llOK;
}

/*******************************************************************************
 * @name LinkList_LocateElement
 * @param L pointer to LinkList
 * @param i location of given element in link list(return value)
 * @param element the given element going to get of link list
 * @return locate operation status(llOK, llFALSE or llCONFLICT)
 * @brief get the location of given element
 * @note status CONFLICT means there are more than 1 identical element in link
 * list. In this case, return value \b i will always be the location of the
 * first matched element.
 * @note status ERROR means given element cannot be found in link list.
 * ****************************************************************************/
status LinkList_LocateElement(LinkList *L, int *i, ElementType element)
{
  int j = *i = 0;
  while (L->next != NULL)
  {
    j++;
    L = L->next;
    if (L->llData == element)
    {
      if (*i == 0)
        *i = j;
      else
        return llCONFLICT;
    }
  }
  if (*i == 0)
    return llFALSE;
  else
    return llOK;
}

/*******************************************************************************
 * @name LinkList_InsertElement
 * @param L pointer to LinkList(return value)
 * @param i -- location of list where given element is going to be inserted
 * @param element -- the given element which is going to be inserted
 * @return: insert operation status(llOK, llERROR)
 * @brief: insert given element into specific location(given by i) of list
 * @note: while llLenth is 1, set the insert location to 2 means insert element
 * at the end of link list. In other words, the operation is going to insert
 * element into the rear of the specific location.
 * ****************************************************************************/
status LinkList_InsertElement(LinkList *L, int i, ElementType element)
{
}