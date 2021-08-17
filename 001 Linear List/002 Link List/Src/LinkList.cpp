/*******************************************************************************
 * @file SQList.cpp
 * @author sheer.rey
 * @date Aug.16, 2021
 * @attention In my version, the index of sequence list is beginning from 1, 
 * rather than array(beginning from 0).
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
 * @param iLenth Initialization lenth of linklist
 * @return Initialization status(llOK)
 * @brief Initialize the linklist with random value of given lenth
 * *****************************************************************************/
status LinkList_Init(LinkList *L, int iLenth)
{
  LinkList *j = L;
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
 * @brief Delete the sequence list and free the memery space
 * ****************************************************************************/
status LinkList_Delete(LinkList *L)
{
}