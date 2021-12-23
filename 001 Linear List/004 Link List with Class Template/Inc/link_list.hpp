/*******************************************************************************
 * @file link_list.hpp
 * @author sheer.rey
 * @date Nov.24, 2021
 *
 * @attention In my version, the index of link list is beginning from 1,
 * rather than array(beginning from 0).
 *
 * @attention In this version, Link List has head node with empty data field.
 *
 * @attention In order to use the features of class template, I use the .hpp
 * file, which means header+cpp file, including both prototype declaration and
 * definition.
 * So DO NOT INCLUDE THIS FILE MULTIPLE TIMES IN DIFFERENT SOURCE FILES to avoid
 * multi-definition error.
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

#ifndef _LINK_LIST_HPP_
#define _LINK_LIST_HPP_

#include <initializer_list>
#include <iostream>
#include <vector>

/* my (sheer.rey) namespace */
namespace libofsheerrey
{
  /* forward declaration of link list class template */
  template <typename T>
  class LinkList;

  /* template friend functions prototype to link list class template */
  template <typename T>
  std::ostream &operator<<(std::ostream &os, LinkList<T> &list);

  /* link list class template */
  template <typename T>
  class LinkList
  {
  private:
    /* node template of link list definition */
    struct Node
    {
      /* public data */
      T data;
      Node *next;
      /* public constructor */
      Node(Node *next_in = nullptr) : next(next_in) {}
      Node(T data_in) : data(data_in), next(nullptr) {}
      Node(T data_in, Node *next_in) : data(data_in), next(next_in) {}

    private:
      /* forbidden functions */
      Node(const Node &node);
      Node &operator=(const Node &Node);
    };

    /* private member */
    Node *m_list_head;      // pointer to head node of link list
    static Node *m_current; // pointer to indicate current node (static member)
    unsigned m_list_size;

  public:
    /* constructor and destructor */
    LinkList();
    LinkList(const std::initializer_list<T> &list);
    LinkList(LinkList &list); // copy constructor
    virtual ~LinkList();

    /* operator overload */
    LinkList &operator=(LinkList &list);

    /* general member funtions */
    // add
    bool Insert(const unsigned location, const T element);
    // delete
    bool Delete(const unsigned location);
    bool Delete(const unsigned location, T &element);
    bool Clear();
    // query
    bool GetElement(const unsigned location, T &element) const;
    std::vector<unsigned> GetLocation(const T &element) const;
    // modify
    bool Replace(const unsigned location, const T &element);

    /* inline funtions */
    // query
    bool IsEmpty() const { return !m_list_size; }
    unsigned GetLenth() const { return m_list_size; }

    /* friend function declaration*/
    // we must use <> to indicate it's a template instantiation
    friend std::ostream &operator<<<>(std::ostream &os,
                                      LinkList<T> &list);
  };

  /* static class member difinition */
  template <typename T>
  typename LinkList<T>::Node *LinkList<T>::m_current = nullptr;

  /* function definition of template class LinkList */

  /* public member function */

  /*****************************************************************************
   * @name LinkList
   * @note Constructor
   * @brief Initialize a empty link list with head node
   * **************************************************************************/
  template <typename T>
  LinkList<T>::LinkList()
  {
    m_list_size = 0;
    m_list_head = new Node;
  }

  /*****************************************************************************
   * @name LinkList
   * @note Constructor
   * @param list Initiative element list
   * @brief Initialize link list with given initialization list
   * **************************************************************************/
  template <typename T>
  LinkList<T>::LinkList(const std::initializer_list<T> &list)
  {
    // list size
    m_list_size = list.size();
    // generate link list
    m_list_head = new Node;
    m_current = m_list_head;
    for (const T &x : list)
    {
      m_current->next = new Node(x);
      m_current = m_current->next;
    }
    // end node
    m_current->next = nullptr;
  }

  /*****************************************************************************
   * @name LinkList
   * @note Copy constructor
   * @param list LinkList reference to be copy
   * @brief Initialize link list with given link list object
   * **************************************************************************/
  template <typename T>
  LinkList<T>::LinkList(LinkList &list)
  {
    // list size
    m_list_size = list.m_list_size;
    // copy link list
    m_list_head = new Node;
    m_current = m_list_head;
    Node *list_current = list.m_list_head;
    for (unsigned i = 0; i < m_list_size; i++)
    {
      m_current->next = new Node(list_current->next->data);
      m_current = m_current->next;
      list_current = list_current->next;
    }
    // end node
    m_current->next = nullptr;
  }

  /*****************************************************************************
   * @name ~LinkList
   * @note Destructor
   * **************************************************************************/
  template <typename T>
  LinkList<T>::~LinkList()
  {
    // delete all memery allocated by operator new
    for (unsigned i = 0; i <= m_list_size; i++)
    {
      m_current = m_list_head->next;
      delete m_list_head;
      m_list_head = m_current;
    }
  }

  /*****************************************************************************
   * @name operator=
   * @note overload '=' operator
   * **************************************************************************/
  template <typename T>
  LinkList<T> &LinkList<T>::operator=(LinkList &list)
  {
    // self check
    if (this == &list)
      return *this;
    else
    {
      // clear origin link list
      for (unsigned i = 0; i <= m_list_size; i++)
      {
        m_current = m_list_head->next;
        delete m_list_head;
        m_list_head = m_current;
      }
      // redifinition list size
      m_list_size = list.m_list_size;
      // regenerate link list
      m_list_head = new Node;
      m_current = m_list_head;
      Node *list_current = list.m_list_head;
      for (unsigned i = 0; i < m_list_size; i++)
      {
        m_current->next = new Node(list_current->next->data);
        m_current = m_current->next;
        list_current = list_current->next;
      }
      // end node
      m_current->next = nullptr;
      return *this;
    }
  }

  /*****************************************************************************
   * @name Insert
   * @param location where given element is going to be inserted
   * @param element which is going to be inserted
   * @retval true : insert successful
   * @retval false: specified location error
   * @brief insert given element into specific location of list
   * @note the operation is going to insert element into the specific location,
   *       and the other elements are shifted backwards in turn.
   * @example set the insert location to 1, what means insert element at the
   *          begining of link list.
   * @example while list lenth is 1, set the insert location to 2 means insert
   *          element at the end of link list.
   * **************************************************************************/
  template <typename T>
  bool LinkList<T>::Insert(const unsigned location, const T element)
  {
    // error check
    if (location < 1 || location > m_list_size + 1)
      return false;
    else
    {
      // traverse to the node before specify location
      m_current = m_list_head;
      for (unsigned i = 0; i < location - 1; i++)
        m_current = m_current->next;
      // insert new node
      m_current->next = new Node(element, m_current->next);
      m_list_size++;
      return true;
    }
  }

  /*****************************************************************************
   * @name Delete
   * @param location where element will be deleted (beginning from 1)
   * @retval true : delete successful
   * @retval false: specified location error
   * @brief Delete element by specify location without return it
   * **************************************************************************/
  template <typename T>
  bool LinkList<T>::Delete(const unsigned location)
  {
    // error check
    if (location < 1 || location > m_list_size)
      return false;
    else
    {
      // traverse to the node before specify location
      m_current = m_list_head;
      for (unsigned i = 0; i < location - 1; i++)
        m_current = m_current->next;
      // delete node
      Node *temp = m_current->next;
      m_current->next = m_current->next->next;
      delete temp;
      m_list_size--;
      return true;
    }
  }

  /*****************************************************************************
   * @name Delete
   * @param location where element will be deleted (beginning from 1)
   * @param element return value (element be deleted from link list)
   * @retval true : delete successful
   * @retval false: specified location error
   * @brief Delete element by specify location and return it
   * **************************************************************************/
  template <typename T>
  bool LinkList<T>::Delete(const unsigned location, T &element)
  {
    // error check
    if (location < 1 || location > m_list_size)
      return false;
    else
    {
      // traverse to the node before specify location
      m_current = m_list_head;
      for (unsigned i = 0; i < location - 1; i++)
        m_current = m_current->next;
      // delete node and return value of delete element
      Node *temp = m_current->next;
      element = temp->data;
      m_current->next = m_current->next->next;
      delete temp;
      m_list_size--;
      return true;
    }
  }

  /*****************************************************************************
   * @name Clear
   * @brief Dlete all vaild elements in link list but keep head node
   * **************************************************************************/
  template <typename T>
  bool LinkList<T>::Clear()
  {
    // save head node
    m_current = m_list_head->next;
    m_list_head->next = nullptr;
    // delete all valid nodes
    Node *temp = m_current;
    while (m_list_size)
    {
      m_current = temp->next;
      delete temp;
      temp = m_current;
      m_list_size--;
    }
    return true;
  }

  /*****************************************************************************
   * @name GetElement
   * @param location specified location to query
   * @param element return value (element in specified location)
   * @retval true : query successful
   * @retval false: specified location error
   * @brief traverse list and return the element of specified location in list
   * **************************************************************************/
  template <typename T>
  bool LinkList<T>::GetElement(const unsigned location, T &element) const
  {
    // error check
    if (location < 1 || location > m_list_size)
      return false;
    else
    {
      // traverse to the specify location
      m_current = m_list_head;
      for (unsigned i = 0; i < location; i++)
        m_current = m_current->next;
      // record element
      element = m_current->data;
      return true;
    }
  }

  /*****************************************************************************
   * @name GetLocation
   * @param element specified element to query
   * @return locations matched specified element
   *         if nothing match the specified element in list, return empty vector
   * @brief traverse list and return the location of specified element
   *        in link list sequence
   * **************************************************************************/
  template <typename T>
  std::vector<unsigned> LinkList<T>::GetLocation(const T &element) const
  {
    using std::vector;
    vector<unsigned> locations;
    // traverse whole list
    m_current = m_list_head;
    for (unsigned i = 0; i < m_list_size; i++)
    {
      m_current = m_current->next;
      // record location
      if (m_current->data == element)
        locations.push_back(i + 1);
    }
    return locations;
  }

  /*****************************************************************************
   * @name Replace
   * @param location specified location to replace
   * @param element element to be replace by
   * @retval true : replace successful
   * @retval false: specified location error
   * @brief replace element in spicified location by spicified element
   * **************************************************************************/
  template <typename T>
  bool LinkList<T>::Replace(const unsigned location, const T &element)
  {
    // error check
    if (location < 1 || location > m_list_size)
      return false;
    else
    {
      // traverse to the specify location
      m_current = m_list_head;
      for (unsigned i = 0; i < location; i++)
        m_current = m_current->next;
      // replace element
      m_current->data = element;
      return true;
    }
  }

  /* friend function */
  /*****************************************************************************
   * @name operator<<
   * @note overload '<<' operator
   * **************************************************************************/
  template <typename T>
  std::ostream &operator<<(std::ostream &os, LinkList<T> &list)
  {
    using namespace std;
    os << "\nInfomation of link list" << endl;
    os << "list size: " << list.m_list_size << endl;
    os << "List value: ";
    list.m_current = list.m_list_head;
    for (unsigned i = 0; i < list.m_list_size; i++)
    {
      list.m_current = list.m_current->next;
      os << list.m_current->data << "  ";
    }
    os << endl;
    return os;
  }

}

#endif
