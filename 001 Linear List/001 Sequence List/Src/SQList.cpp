/*******************************************************************************
 * @file SQList.cpp
 * @author sheer.rey
 * @date Aug.14, 2021
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
#include <iostream>
#include <cstdlib>
#include "SQList.h"

/*******************************************************************************
 * @name SQList_Init
 * @param L pointer to sqList(return value)
 * @param iListMaxSize the max size of sequence list
 * @return Initialization status(sqOK)
 * @brief Initialize the sequence list with the given size and return pointer
 * *****************************************************************************/
status SQList_Init(sqList *L, int iListMaxSize)
{
  L->sqData = new ElementType[iListMaxSize];
  L->sqLenth = 0;
  L->sqMaxSize = iListMaxSize;
  for (int i = 0; i < iListMaxSize; i++)
    L->sqData[i] = rand() % 100;
  return sqOK;
}

/*******************************************************************************
 * @name SQList_Delete
 * @param L pointer to sqList(return value)
 * @return Delete status(sqOK)
 * @brief Delete the sequence list and free the memery space
 * ****************************************************************************/
status SQList_Delete(sqList *L)
{
  delete[] L->sqData;
  return sqOK;
}

/*******************************************************************************
 * @name SQList_Empty
 * @param L pointer to sqList
 * @return Sequence list empty status(sqTRUE or sqFALSE)
 * @brief make sure if sequence list is empty
 * ****************************************************************************/
status SQList_IfEmpty(sqList *L)
{
  if (L->sqLenth)
    return sqFALSE;
  return sqTRUE;
}

/*******************************************************************************
 * @name SQList_Clear
 * @param L pointer to sqList(return value)
 * @return Sequence list clear status(sqOK)
 * @brief set the whole memery of sequence list to 0
 * ****************************************************************************/
status SQList_Clear(sqList *L)
{
  for (int i = 0; i < L->sqMaxSize; i++)
    L->sqData[i] = 0;
  L->sqLenth = 0;
  return sqOK;
}

/*******************************************************************************
 * @name SQList_GetLenth
 * @param L pointer to sqList
 * @param sqListLenth pointer to current lenth of Sequence List(return Value)
 * @return Get Sequence list lenth status(sqOK)
 * @brief Get the current lenth of Sequence List
 * ****************************************************************************/
status SQList_GetLenth(sqList *L, int *sqListLenth)
{
  *sqListLenth = L->sqLenth;
  return sqOK;
}

/*******************************************************************************
 * @name SQList_GetElement
 * @param L pointer to sqList
 * @param i location of element which is going to get
 * @param element the element be get of sequence list(return value)
 * @return get operation status(sqOK or sqERROR)
 * @brief get the element given by variable i
 * ****************************************************************************/
status SQList_GetElement(sqList *L, int i, ElementType *element)
{
  if (i < 1 || i > L->sqLenth)
    return sqERROR;
  *element = L->sqData[i - 1];
  return sqOK;
}

/*******************************************************************************
 * @name SQList_LocateElement
 * @param L pointer to sqList
 * @param i location of given element in sequence list(return value)
 * @param element the given element going to get of sequence list
 * @return locate operation status(sqOK, sqFALSE or sqCONFLICT)
 * @brief get the location of given element.
 * @note Status sqCONFLICT means there are more than 1 identical element in
 * sequence list. Status sqERROR means given element cannot be found in
 * sequence list.
 * ****************************************************************************/
status SQList_LocateElement(sqList *L, int *i, ElementType element)
{
  int j;
  bool bGetElementOK = false;
  for (j = 0; j < L->sqLenth; j++)
  {
    if (element == L->sqData[j])
    {
      if (bGetElementOK == false)
      {
        *i = j + 1;
        bGetElementOK = true;
      }
      else
        return sqCONFLICT;
    }
  }
  if (bGetElementOK == true)
    return sqOK;
  else
    return sqFALSE;
}

/*******************************************************************************
 * @name SQList_InsertElement
 * @param L pointer to sqList(return value)
 * @param i location of list where given element is going to be inserted
 * @param element the given element which is going to be inserted
 * @return insert operation status(sqOK, sqERROR or sqOVERFLOW)
 * @brief insert given element into specific location(given by i) of list
 * @note while sqLenth is 1, set the insert location to 2 means insert element
 * at the end of sequence list.
 * ****************************************************************************/
status SQList_InsertElement(sqList *L, int i, ElementType element)
{
  if (i < 1 || i > L->sqLenth + 1)
    return sqERROR;
  if (L->sqLenth == L->sqMaxSize)
    return sqOVERFLOW;
  int j;
  for (j = L->sqLenth - 1; j >= i - 1; j--)
    L->sqData[j + 1] = L->sqData[j];
  L->sqData[j + 1] = element;
  L->sqLenth++;
  return sqOK;
}

/*******************************************************************************
 * @name SQList_DeleteElement
 * @param L pointer to sqList(return value)
 * @param i location of list where element is going to be deleted
 * @param element the deleted element(return value)
 * @retval delete operation status(sqOK or sqERROR)
 * @brief delete element in location given by i, and return deleted element
 * ****************************************************************************/
status SQList_DeleteElement(sqList *L, int i, ElementType *element)
{
  if (i < 1 || i > L->sqLenth)
    return sqERROR;
  *element = L->sqData[i - 1];
  int j;
  for (j = i; j < L->sqLenth; j++)
    L->sqData[j - 1] = L->sqData[j];
  L->sqLenth--;
  return sqOK;
}

/*******************************************************************************
 * @name SQList_print
 * @param L pointer to sqList
 * @retval none
 * @brief print the elements of sequence list
 * ****************************************************************************/
void SQList_print(sqList *L)
{
  std::cout << "Sequence List element is: ";
  int i;
  for (i = 0; i < L->sqLenth - 1; i++)
    std::cout << L->sqData[i] << " ";
  if (L->sqLenth)
    std::cout << L->sqData[i] << std::endl;
}

/*******************************************************************************
 * @name SQList_print_all
 * @param L pointer to sqList
 * @retval none
 * @brief print the whole memery value of sequence list, no matter how long
 * sequence lenth is
 * ****************************************************************************/
void SQList_print_all(sqList *L)
{
  std::cout << "The whole memery value of Sequence List is: ";
  int i;
  for (i = 0; i < L->sqMaxSize - 1; i++)
    std::cout << L->sqData[i] << " ";
  std::cout << L->sqData[i] << std::endl;
}