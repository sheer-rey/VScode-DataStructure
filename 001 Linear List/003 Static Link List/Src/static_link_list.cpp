/*******************************************************************************
 * @file static_link_list.cpp
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

#include "static_link_list.h"

/* static link list's namespace */
namespace staticlinklist
{
  /* private member function definition */

  /*****************************************************************************
   * @name BackupStackPop
   * @return the location of static link list array to be insert
   * @brief Pop the first Node of backup stack for the next insert operation
   * **************************************************************************/
  StaticLinkList::Cursor StaticLinkList::BackupStackPop()
  {
    m_backup_size--;
    Cursor cursor = m_backup_head->cursor_next;
    if (m_backup_size)
      m_backup_head->cursor_next = m_list[cursor].cursor_next;
    else
      m_backup_head->cursor_next = Cursor(-1);
    return cursor;
  }

  /*****************************************************************************
   * @name BackupStackPush
   * @param cursor the location to push to backup stack
   * @brief push the deleted Node to backup stack after last delete operation
   * **************************************************************************/
  void StaticLinkList::BackupStackPush(const Cursor cursor)
  {
    m_backup_size++;
    m_list[cursor].cursor_next = m_backup_head->cursor_next;
    m_backup_head->cursor_next = cursor;
  }

  /* public member function definition */

  /*****************************************************************************
   * @name StaticLinkList
   * @note constructor
   * @param max_list_size the maximum array size of static link list
   * @brief Initialize a empty static link list with given size
   * **************************************************************************/
  StaticLinkList::StaticLinkList(const unsigned max_list_size)
  {
    /* max size error check */
    if (max_list_size <= 2)
      m_max_list_size = 2;
    else
      m_max_list_size = max_list_size;

    m_list = new Node[m_max_list_size];

    // last element of list array indicates the first static link list node
    m_list_head = &m_list[m_max_list_size - 1];

    // first element of list array indicates the first backup stack node
    m_backup_head = m_list;

    /* initialize backup stack */
    // first element of list array indicates the first backup node to be insert
    for (unsigned i = 0; i < m_max_list_size; i++)
    {
      m_list[i].cursor_next = Cursor(i + 1);
      // is_valid member indicates if the node is valid element in list
      // true means yes, false means no
      m_list[i].is_valid = false;
    }
    m_list_size = 0;
    // -1 means there's no valid node in static link list
    m_list_head->cursor_next = Cursor(-1);

    m_backup_size = m_max_list_size - 2;
    if (m_backup_size)
    {
      m_backup_head->cursor_next = Cursor(1);
      // this node is the last node of backup stack, so the next cursor is -1
      m_list[m_max_list_size - 2].cursor_next = Cursor(-1);
    }
    else
      m_backup_head->cursor_next = Cursor(-1);
  }

  /*****************************************************************************
   * @name StaticLinkList
   * @note constructor
   * @param max_list_size the maximum array size of static link list
   * @param list Initiative element list
   * @brief Initialize static link list with given size and initialization list
   * **************************************************************************/
  StaticLinkList::StaticLinkList(const std::initializer_list<ElementType> list,
                                 const unsigned max_list_size)
  {
    /* max size error check */
    if (list.size() > max_list_size - 2)
      m_max_list_size = list.size() + 2;
    else if (max_list_size <= 2)
      m_max_list_size = 2;
    else
      m_max_list_size = max_list_size;

    /* allocate memery */
    m_list = new Node[m_max_list_size];

    // last element of list array indicates the first static link list node
    m_list_head = &m_list[m_max_list_size - 1];

    // first element of list array indicates the first backup stack node
    m_backup_head = m_list;

    /* initialize backup stack */
    // first element of list array indicates the first backup node to be insert
    for (unsigned i = 0; i < m_max_list_size; i++)
    {
      m_list[i].cursor_next = Cursor(i + 1);
      // is_valid member indicates if the node is valid element in list
      // true means yes, false means no
      m_list[i].is_valid = false;
    }

    /* insert initialization list to static link list */
    if (list.size() != 0)
    {
      m_list_size = 0;
      int i = 1;
      for (ElementType x : list)
      {
        m_list_size++;
        m_list[i].data = x;
        // is_valid member indicates if the node is valid element in list
        // true means yes, false means no
        m_list[i].is_valid = true;
        i++;
      }
      // -1 means there's no valid node after
      m_list[i - 1].cursor_next = Cursor(-1);
      m_list_head->cursor_next = Cursor(1);

      m_backup_size = m_max_list_size - m_list_size - 2;
      if (m_backup_size)
      {
        m_backup_head->cursor_next = Cursor(i);
        // this node is the last node of backup stack, so the next cursor is -1
        m_list[m_max_list_size - 2].cursor_next = Cursor(-1);
      }
      else
        m_backup_head->cursor_next = Cursor(-1);
    }
    else
    // if initialization list is empty
    {
      m_list_size = 0;
      // -1 means there's no valid node in static link list
      m_list_head->cursor_next = Cursor(-1);

      m_backup_size = m_max_list_size - 2;
      if (m_backup_size)
      {
        m_backup_head->cursor_next = Cursor(1);
        // this node is the last node of backup stack, so the next cursor is -1
        m_list[m_max_list_size - 2].cursor_next = Cursor(-1);
      }
      else
        m_backup_head->cursor_next = Cursor(-1);
    }
  }

  /*****************************************************************************
   * @name StaticLinkList
   * @note copy constructor
   * @param list StaticLinkList object to be copy
   * @brief Initialize static link list with given StaticLinkList object
   * **************************************************************************/
  StaticLinkList::StaticLinkList(const StaticLinkList &list)
  {
    // shallow copy
    m_max_list_size = list.m_max_list_size;
    m_list_size = list.m_list_size;
    m_backup_size = list.m_backup_size;

    // deep copy
    m_list = new Node[m_max_list_size];
    for (unsigned i = 0; i < m_max_list_size; i++)
      m_list[i] = list.m_list[i];

    // last element of list array indicates the first static link list node
    m_list_head = &m_list[m_max_list_size - 1];

    // first element of list array indicates the first backup node to be insert
    m_backup_head = &m_list[0];
  }

  /*****************************************************************************
   * @name StaticLinkList
   * @note destructor
   * **************************************************************************/
  StaticLinkList::~StaticLinkList()
  {
    delete[] m_list;
  }

  /*****************************************************************************
   * @name operator=
   * @note overload '=' operator
   * **************************************************************************/
  StaticLinkList &StaticLinkList::operator=(const StaticLinkList &list)
  {
    // self check
    if (this == &list)
      return *this;
    else
    {
      // clear origin memery by new
      delete[] m_list;

      // shallow copy
      m_max_list_size = list.m_max_list_size;
      m_list_size = list.m_list_size;
      m_backup_size = list.m_backup_size;

      // deep copy
      m_list = new Node[m_max_list_size];
      for (unsigned i = 0; i < m_max_list_size; i++)
        m_list[i] = list.m_list[i];

      // last element of list array indicates the first static link list node
      m_list_head = &m_list[m_max_list_size - 1];

      // first element of list array indicates the first backup node to be insert
      m_backup_head = &m_list[0];

      return *this;
    }
  }

  /*****************************************************************************
   * @name InsertElement
   * @param location where element will be inserted to (beginning from 1) in
   *                 static link list
   * @param element which will be inserted
   * @retval 0 : insert successful, others means error code
   * @retval -1 : insert failed (specified location error)
   * @retval -2 : insert failed (static link list overfull)
   * @brief Insert specify element to specified location, and origin element
   * in the specified location will move backward
   * **************************************************************************/
  int StaticLinkList::InsertElement(const unsigned location,
                                    const ElementType &element)
  {
    /* error check */
    if (location < 1 || location > m_list_size + 1)
      return -1;
    else if (m_list_size >= m_max_list_size - 2 || m_backup_size <= 0)
      return -2;
    else
    {
      // traverse to the node before specified location
      Node *node_before = m_list_head;
      for (unsigned i = 1; i < location; i++)
        node_before = &m_list[node_before->cursor_next];
      // get the cursor where new element will put in
      Cursor cursor_insert = BackupStackPop();
      // insert element
      m_list[cursor_insert].is_valid = true;
      m_list[cursor_insert].data = element;
      m_list[cursor_insert].cursor_next = node_before->cursor_next;
      node_before->cursor_next = cursor_insert;
      m_list_size++;
      return 0;
    }
  }

  /*****************************************************************************
   * @name DeleteElement
   * @param location where element will be deleted (beginning from 1) in static
   *                 link list
   * @param element return value (element be deleted from static link list)
   * @retval true : delete successful
   * @retval false: specified location error
   * @brief Delete element by specify location and return it
   * **************************************************************************/
  bool StaticLinkList::DeleteElement(const unsigned location,
                                     ElementType &element)
  {
    /* error check */
    if (location < 1 || location > m_list_size)
      return false;
    else
    {
      // traverse to the node before specified location
      Node *node_before = m_list_head;
      for (unsigned i = 1; i < location; i++)
        node_before = &m_list[node_before->cursor_next];
      // copy node data to element
      element = m_list[node_before->cursor_next].data;
      // delete element
      m_list[node_before->cursor_next].is_valid = false;
      Cursor cursor = node_before->cursor_next;
      node_before->cursor_next = m_list[node_before->cursor_next].cursor_next;
      BackupStackPush(cursor);
      m_list_size--;
      return true;
    }
  }

  /*****************************************************************************
   * @name DeleteElement
   * @param location where element will be deleted (beginning from 1) in static
   *                 link list
   * @retval true : delete successful
   * @retval false: specified location error
   * @brief Delete element by specify location without return it
   * **************************************************************************/
  bool StaticLinkList::DeleteElement(const unsigned location)
  {
    /* error check */
    if (location < 1 || location > m_list_size)
      return false;
    else
    {
      // traverse to the node before specified location
      Node *node_before = m_list_head;
      for (unsigned i = 1; i < location; i++)
        node_before = &m_list[node_before->cursor_next];
      // delete element
      m_list[node_before->cursor_next].is_valid = false;
      Cursor cursor = node_before->cursor_next;
      node_before->cursor_next = m_list[node_before->cursor_next].cursor_next;
      BackupStackPush(cursor);
      m_list_size--;
      return true;
    }
  }

  /*****************************************************************************
   * @name ClearList
   * @brief Dlete all vaild elements in static link list but keep memery
   * **************************************************************************/
  void StaticLinkList::ClearList()
  {
    /* reset backup stack */
    // first element of list array indicates the first backup node to be insert
    for (unsigned i = 0; i < m_max_list_size; i++)
    {
      m_list[i].cursor_next = Cursor(i + 1);
      // is_valid member indicates if the node is valid element in list
      // true means yes, false means no
      m_list[i].is_valid = false;
    }
    m_list_size = 0;
    // -1 means there's no valid node in static link list
    m_list_head->cursor_next = Cursor(-1);

    m_backup_size = m_max_list_size - 2;
    if (m_backup_size)
    {
      m_backup_head->cursor_next = Cursor(1);
      // this node is the last node of backup stack, so the next cursor is -1
      m_list[m_max_list_size - 2].cursor_next = Cursor(-1);
    }
    else
      m_backup_head->cursor_next = Cursor(-1);
  }

  /*****************************************************************************
   * @name GetLocation
   * @param element specified element to query
   * @return locations matched specified element
   *         if nothing match the specified element in list, return empty vector
   * @brief traverse list and return the location of specified element
   *        in link list sequence
   * **************************************************************************/
  std::vector<unsigned> StaticLinkList::GetLocation(const ElementType &element)
  {
    using std::vector;
    vector<unsigned> locations;
    // traverse list
    Node *node = &m_list[m_list_head->cursor_next];
    for (unsigned i = 1; i <= m_list_size; i++)
    {
      if (node->data == element)
        locations.push_back(i);
      node = &m_list[node->cursor_next];
    }
    return locations;
  }

  /*****************************************************************************
   * @name GetElement
   * @param location specified location to query
   * @param element return value (element in specified location)
   * @retval true : query successful
   * @retval false: specified location error
   * @brief traverse list and return the element of specified location in list
   * **************************************************************************/
  bool StaticLinkList::GetElement(const unsigned location, ElementType &element)
  {
    /* error check */
    if (location < 1 || location > m_list_size)
      return false;
    else
    {
      // traverse to the node in specified location
      Node *node = m_list_head;
      for (unsigned i = 1; i <= location; i++)
        node = &m_list[node->cursor_next];
      element = node->data;
      return true;
    }
  }

  /*****************************************************************************
   * @name ReplaceElement
   * @param location specified location to replace
   * @param element element to be replace by
   * @retval true : replace successful
   * @retval false: specified location error
   * @brief replace element in spicified location by spicified element
   * **************************************************************************/
  bool StaticLinkList::ReplaceElement(const unsigned location,
                                      const ElementType &element)
  {
    /* error check */
    if (location < 1 || location > m_list_size)
      return false;
    else
    {
      // traverse to the node in specified location
      Node *node = m_list_head;
      for (unsigned i = 1; i <= location; i++)
        node = &m_list[node->cursor_next];
      node->data = element;
      return true;
    }
  }

  /* friend function */

  /*****************************************************************************
   * @name operator<<
   * @note overload '<<' operator
   * **************************************************************************/
  std::ostream &operator<<(std::ostream &os,
                           const staticlinklist::StaticLinkList &list)
  {
    using namespace std;
    os << "\nStatic Link List Information" << endl;
    os << "\nMax size: " << list.m_max_list_size << "\tList size: "
       << list.m_list_size << "\tBackup size: " << list.m_backup_size
       << endl;

    /* memory value of static link list */
    os << "\nList memory value: " << endl;
    os.flags(ios::left);
    // cursor
    os << setw(14) << "cursor";
    for (unsigned i = 0; i < list.m_max_list_size; i++)
      os << setw(10) << i;
    os << endl;
    os << setfill('-') << setw(14 + 10 * list.m_max_list_size) << '-';
    os << setfill(' ') << endl;
    // data
    os << setw(14) << "data";
    for (unsigned i = 0; i < list.m_max_list_size; i++)
    {
      if (list.m_list[i].is_valid == true)
        os << setw(10) << list.m_list[i].data;
      else
        os << setw(10) << "null";
    }
    os << endl;
    // next cursor
    os << setw(14) << "next cursor";
    for (unsigned i = 0; i < list.m_max_list_size; i++)
    {
      if (list.m_list[i].cursor_next != -1)
        os << setw(10) << list.m_list[i].cursor_next;
      else
        os << setw(10) << "null";
    }
    os << endl;

    /* static link list value */
    os << setw(28) << "\nStatic link list value: ";
    StaticLinkList::Cursor cursor = list.m_list_head->cursor_next;
    for (unsigned i = 0; i < list.m_list_size; i++)
    {
      os << setw(5) << list.m_list[cursor].data;
      cursor = list.m_list[cursor].cursor_next;
    }

    /* reset os object to default */
    os << endl;
    os.unsetf(ios_base::floatfield);
    return os;
  }
}
