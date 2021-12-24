/*******************************************************************************
 * @file linked_stack.hpp
 * @author sheer.rey
 * @date Dec.23, 2021
 *
 * @attention Head pointer of link list(stack) is stack top, and there's no head
 * node in linked stack while my link list datastructure has.
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

#ifndef _LINKED_STACK_HPP_
#define _LINKED_STACK_HPP_

#include <initializer_list>
#include <iostream>

/* my (sheer.rey) namespace */
namespace libofsheerrey
{
  // forward declaration of stack template
  template <typename T>
  class LinkedStack;

  /* template friend functions prototype to stack template */
  template <typename T>
  std::ostream &operator<<(std::ostream &os, LinkedStack<T> &stack);

  /* linked stack class template */
  template <typename T>
  class LinkedStack
  {
  private:
    /* node template of linked stack definition */
    struct Node
    {
      /* public data */
      T data;
      Node *next;
      /* Constructor and Destructor */
      Node(Node *next_in = nullptr) : next(next_in) {}
      Node(T data_in) : data(data_in), next(nullptr) {}
      Node(T data_in, Node *next_in) : data(data_in), next(next_in) {}
      ~Node() = default;

      /* forbidden functions */
      Node(const Node &node) = delete;
      Node(Node &&node) = delete;
      Node &operator=(const Node &Node) = delete;
      Node &operator=(Node &&Node) = delete;
    };

    /* private data member */
    unsigned m_size = 0;
    Node *m_stack_top = nullptr;
    static Node *m_temporary;

  public:
    /* Special member functions */
    // Default Constructor
    LinkedStack() = default;
    LinkedStack(const std::initializer_list<T> &stack);
    // Copy Constructor
    LinkedStack(const LinkedStack &stack);
    // Move Constructor
    LinkedStack(LinkedStack &&stack) = delete;
    // Destructor
    ~LinkedStack();
    // Copy Operator=
    LinkedStack &operator=(const LinkedStack &stack);
    // Move Operator=
    LinkedStack &operator=(LinkedStack &&stack) = delete;

    /* General member functions */
    // add
    void Push(const T &element);
    // delete
    bool Pop(T &element);
    // Clear
    void Clear();
    // query
    bool GetTop(T &element) const;

    /* Inline member functions */
    // query
    bool IsEmpty() const { return !m_size; }
    unsigned StackSize() const { return m_size; }

    /* friend function */
    // we must use <> to indicate it's a template instantiation
    friend std::ostream &operator<<<>(std::ostream &os, LinkedStack<T> &stack);
  };

  /* static class data member difinition */
  template <typename T>
  typename LinkedStack<T>::Node *LinkedStack<T>::m_temporary = nullptr;

  /* function definition of template class Stack */

  /* public member function */
  /*****************************************************************************
   * @name LinkedStack
   * @note Constructor
   * @param stack Initiative element list, bottom first
   * @brief Initialize Stack with initializer list
   * **************************************************************************/
  template <typename T>
  LinkedStack<T>::LinkedStack(const std::initializer_list<T> &stack)
  {
    m_size = stack.size();
    for (const T &x : stack)
    {
      m_temporary = m_stack_top;
      m_stack_top = new Node(x, m_temporary);
    }
  }

  /*****************************************************************************
   * @name LinkedStack
   * @note Cpoy constructor
   * @param stack Stack reference to be copy
   * @brief Initialize stack with given stack object
   * **************************************************************************/
  template <typename T>
  LinkedStack<T>::LinkedStack(const LinkedStack &stack)
  {
    m_size = stack.m_size;
    // top node
    m_stack_top = new Node(stack.m_stack_top->data);
    // other nodes
    Node *temporary = m_stack_top;
    stack.m_temporary = stack.m_stack_top;
    while (stack.m_temporary->next != nullptr)
    {
      temporary->next = new Node(stack.m_temporary->next->data);
      temporary = temporary->next;
      stack.m_temporary = stack.m_temporary->next;
    }
  }

  /*****************************************************************************
   * @name ~LinkedStack
   * @note Destructor
   * **************************************************************************/
  template <typename T>
  LinkedStack<T>::~LinkedStack()
  {
    if (m_size)
    {
      // destroy all used memory space
      m_temporary = m_stack_top->next;
      while (m_stack_top->next != nullptr)
      {
        delete m_stack_top;
        m_stack_top = m_temporary;
        m_temporary = m_stack_top->next;
      }
      delete m_stack_top;
    }
  }

  /*****************************************************************************
   * @name operator=
   * @note overload '=' operator
   * **************************************************************************/
  template <typename T>
  LinkedStack<T> &LinkedStack<T>::operator=(const LinkedStack &stack)
  {
    // self check
    if (this == &stack)
      return *this;
    else
    {
      if (m_size)
      {
        // destroy all used memory space
        m_temporary = m_stack_top->next;
        while (m_stack_top->next != nullptr)
        {
          delete m_stack_top;
          m_stack_top = m_temporary;
          m_temporary = m_stack_top->next;
        }
        delete m_stack_top;
      }
      // generate new stack
      m_size = stack.m_size;
      // top node
      m_stack_top = new Node(stack.m_stack_top->data);
      // other nodes
      Node *temporary = m_stack_top;
      stack.m_temporary = stack.m_stack_top;
      while (stack.m_temporary->next != nullptr)
      {
        temporary->next = new Node(stack.m_temporary->next->data);
        temporary = temporary->next;
        stack.m_temporary = stack.m_temporary->next;
      }
      return *this;
    }
  }

  /*****************************************************************************
   * @name Push
   * @param element Given element to be push
   * @brief Push given element to stack
   * **************************************************************************/
  template <typename T>
  void LinkedStack<T>::Push(const T &element)
  {
    m_size++;
    m_stack_top = new Node(element, m_stack_top);
  }

  /*****************************************************************************
   * @name Pop
   * @param element Element be poped out
   * @retval true:  pop success
   * @retval false: stack is empty
   * @brief Pop top element from stack and store it
   * **************************************************************************/
  template <typename T>
  bool LinkedStack<T>::Pop(T &element)
  {
    if (m_size)
    {
      m_size--;
      element = m_stack_top->data;
      m_temporary = m_stack_top->next;
      delete m_stack_top;
      m_stack_top = m_temporary;
      return true;
    }
    else
      return false;
  }

  /*****************************************************************************
   * @name Clear
   * @brief Clear stack
   * **************************************************************************/
  template <typename T>
  void LinkedStack<T>::Clear()
  {
    if (m_size)
    {
      // destroy all used memory space
      m_temporary = m_stack_top->next;
      while (m_stack_top->next != nullptr)
      {
        delete m_stack_top;
        m_stack_top = m_temporary;
        m_temporary = m_stack_top->next;
      }
      delete m_stack_top;
      m_size = 0;
      m_stack_top = nullptr;
    }
  }

  /*****************************************************************************
   * @name GetTop
   * @param element Element on stack top
   * @retval true:  get top success
   * @retval false: stack is empty
   * @brief Get element on stack top
   * **************************************************************************/
  template <typename T>
  bool LinkedStack<T>::GetTop(T &element) const
  {
    if (m_size)
    {
      element = m_stack_top->data;
      return true;
    }
    else
      return false;
  }

  /* friend function */
  /*****************************************************************************
   * @name operator<<
   * @note overload '<<' operator
   * **************************************************************************/
  template <typename T>
  std::ostream &operator<<(std::ostream &os, LinkedStack<T> &stack)
  {
    using namespace std;
    os << "\nInfomation of stack" << endl;
    os << "stack size: " << stack.m_size << endl;
    if (stack.m_size > 0)
    {
      stack.m_temporary = stack.m_stack_top;
      os << "stack elements are as follow: " << endl;
      os << "   top -> " << stack.m_temporary->data << endl;
      while (stack.m_temporary->next != nullptr)
      {
        stack.m_temporary = stack.m_temporary->next;
        if (stack.m_temporary->next != nullptr)
          os << "          " << stack.m_temporary->data << endl;
        else
          os << "bottom -> " << stack.m_temporary->data << endl;
      }
    }
    return os;
  }
}

#endif