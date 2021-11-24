/*******************************************************************************
 * @file static_link_list.h
 * @author sheer.rey
 * @date Nov.15, 2021
 *
 * @attention In my version, the index of static link list is beginning from 1,
 * rather than array(beginning from 0).
 *
 * @attention In this version, Static Link List has head node at the end of list
 * array [m_max_list_size - 1], and the data field of head node is empty.
 *
 * Also, it has backup head node at the beginning of list array [0] to indicate
 * the location of first blank node to insert to static link list, the data
 * field of backup head node is empty.
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

#ifndef STATIC_LINKLIST_H_
#define STATIC_LINKLIST_H_

#include <initializer_list>
#include <iostream>
#include <vector>
#include <iomanip>

/* static link list's namespace */
namespace staticlinklist
{
  /* type definition */
  typedef int ElementType;

  /* static link list class */
  class StaticLinkList
  {
  private:
    /* const values */
    static const unsigned cDefaultMaxSize = 10;

    /* private type definition */
    typedef int Cursor;

    /* Node type definition */
    struct Node
    {
      ElementType data;
      Cursor cursor_next;
      // is_valid member indicates if the node is valid element in list
      // true means yes, false means no
      bool is_valid;
    };

    /* pointer to static link list */
    Node *m_list;

    /* static link list infomation */
    unsigned m_max_list_size;
    unsigned m_list_size;
    unsigned m_backup_size;
    Node *m_list_head;
    Node *m_backup_head;

    /* private functions */
    Cursor BackupStackPop();
    void BackupStackPush(Cursor cursor);

  public:
    /* menber function prototype */

    StaticLinkList(const unsigned max_list_size = cDefaultMaxSize);
    StaticLinkList(const std::initializer_list<ElementType> list,
                   const unsigned max_list_size = cDefaultMaxSize);
    StaticLinkList(const StaticLinkList &list);
    ~StaticLinkList();
    StaticLinkList &operator=(const StaticLinkList &list);
    int InsertElement(const unsigned location, const ElementType &element);
    bool DeleteElement(const unsigned location, ElementType &element);
    bool DeleteElement(const unsigned location);
    void ClearList();
    std::vector<unsigned> GetLocation(const ElementType &element);
    bool GetElement(const unsigned location, ElementType &element);
    bool ReplaceElement(const unsigned location, const ElementType &element);

    /* inline function */

    /***************************************************************************
     * @name IsListEmpty
     * @return true or false
     * @brief Check if static link list is empty
     * ************************************************************************/
    bool IsListEmpty()
    {
      return m_list_size ? false : true;
    }

    /***************************************************************************
     * @name ListSize
     * @brief Return the size of valid Node in static link list
     * ************************************************************************/
    unsigned ListSize() { return m_list_size; }

    /***************************************************************************
     * @name ListMaxSize
     * @brief Return the MAX size of Nodes static link list can hold
     * ************************************************************************/
    unsigned ListMaxSize() { return m_max_list_size - 2; }

    /***************************************************************************
     * @name ListBackupSize
     * @brief Return current size of backup stack
     * ************************************************************************/
    unsigned ListBackupSize() { return m_backup_size; }

    /* friend function */

    friend std::ostream &operator<<(std::ostream &os,
                                    const staticlinklist::StaticLinkList &list);
  };

}

#endif
