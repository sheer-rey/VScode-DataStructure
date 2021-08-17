/*******************************************************************************
 * @file: SQList.h
 * @author: sheer.rey
 * @date: Aug.14, 2021
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
#ifndef _SQLIST_H
#define _SQLIST_H
#include <string>

typedef int ElementType;

enum status
{
  sqERROR,
  sqCONFLICT,
  sqOVERFLOW,
  sqFALSE,
  sqTRUE,
  sqOK
};

const std::string strSQErrorMessage[sqOK + 1] = {
    "ERROR: Specific location is not in the Sequence List range!",
    "WARING: More than 1 identical element in Sequence List!",
    "ERROR: Sequence List overflow!",
    "",
    "",
    ""};

struct sqList
{
  /* data */
  ElementType *sqData; //sequence list, the max lenth is decided by initialization function
  int sqLenth;
  int sqMaxSize;
};

status SQList_Init(sqList *L, int iListMaxSize);
status SQList_Delete(sqList *L);
status SQList_IfEmpty(sqList *L);
status SQList_Clear(sqList *L);
status SQList_GetLenth(sqList *L, int *sqListLenth);
status SQList_GetElement(sqList *L, int i, ElementType *element);
status SQList_LocateElement(sqList *L, int *i, ElementType element);
status SQList_InsertElement(sqList *L, int i, ElementType element);
status SQList_DeleteElement(sqList *L, int i, ElementType *element);
void SQList_print(sqList *L);
void SQList_print_all(sqList *L);

#endif