/*******************************************************************************
 * @file sequential_stack.hpp
 * @author sheer.rey
 * @date Dec.21, 2021
 *
 * @attention Subscript 0 of stack array is bottom.
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

#ifndef _SEQUENTIAL_STACK_HPP_
#define _SEQUENTIAL_STACK_HPP_

#include <initializer_list>
#include <iostream>

/* my (sheer.rey) namespace */
namespace libofsheerrey {
  // forward declaration of stack template
  template <typename T>
  class Stack;

  /* template friend functions prototype to stack template */
  template <typename T>
  std::ostream& operator<<(std::ostream& os, Stack<T>& stack);

  /* stack class template */
  template <typename T>
  class Stack {
   private:
    // use to expand stack size while
    static const unsigned cExpansionFactor = 2;
    unsigned m_max_size = 10;
    unsigned m_size;
    T* m_stack_bottom;
    T* m_stack_top;

   public:
    /* Special member functions */
    // Default Constructor
    Stack();
    // Constructor
    Stack(const unsigned max_size);
    Stack(const std::initializer_list<T>& stack, const unsigned max_size = 0);
    // Copy Constructor
    Stack(const Stack& stack);
    // Move Constructor
    Stack(Stack&& stack) = delete;
    // Destructor
    ~Stack() { delete[] m_stack_bottom; }
    // Copy Operator=
    Stack& operator=(const Stack& stack);
    // Move Operator=
    Stack& operator=(Stack&& stack) = delete;

    /* General member functions */
    // add
    void Push(const T& element);
    // delete
    bool Pop(T& element);
    // Clear
    void Clear();
    // query
    bool GetTop(T& element) const;
    // Shrink
    void ShrinktoFit();
    // Expansion
    void Expansion();

    /* Inline member functions */
    // query
    bool IsEmpty() const { return !m_size; }
    bool IsFull() const { return m_size == m_max_size ? true : false; }
    unsigned StackSize() const { return m_size; }
    unsigned StackMaxSize() const { return m_max_size; }

    /* friend function */
    // we must use <> to indicate it's a template instantiation
    friend std::ostream& operator<< <>(std::ostream& os, Stack<T>& stack);
  };

  /* function definition of template class Stack */

  /* public member function */

  /*****************************************************************************
   * @name Stack
   * @note Constructor
   * @brief Initialize an empty Stack
   * **************************************************************************/
  template <typename T>
  Stack<T>::Stack() {
    m_size = 0;
    m_stack_bottom = new T[m_max_size];
    m_stack_top = m_stack_bottom;
  }

  /*****************************************************************************
   * @name Stack
   * @note Constructor
   * @param max_size The max stack capacity given by
   * @brief Initialize a empty Stack with given stack capacity
   * **************************************************************************/
  template <typename T>
  Stack<T>::Stack(const unsigned max_size) {
    m_size = 0;
    m_max_size = max_size;
    m_stack_bottom = new T[m_max_size];
    m_stack_top = m_stack_bottom;
  }

  /*****************************************************************************
   * @name Stack
   * @note Constructor
   * @param stack Initiative element list, bottom first
   * @param max_size The max stack capacity given by
   * @brief Initialize stack with given initialization list and capacity
   * @attention If the given max_size parameter is less than initializer list
   * size, the capacity of stack will expand to fit list size
   * **************************************************************************/
  template <typename T>
  Stack<T>::Stack(const std::initializer_list<T>& stack,
                  const unsigned max_size) {
    m_size = stack.size();
    // max size check
    if (max_size < m_size) m_max_size = m_size;
    else m_max_size = max_size;
    // generate stack with initializer list
    m_stack_bottom = new T[m_max_size];
    m_stack_top = m_stack_bottom - 1;
    for (const T& x : stack) {
      m_stack_top++;
      *m_stack_top = x;
    }
  }

  /*****************************************************************************
   * @name Stack
   * @note Copy constructor
   * @param stack Stack reference to be copy
   * @brief Initialize stack with given stack object
   * **************************************************************************/
  template <typename T>
  Stack<T>::Stack(const Stack& stack) {
    m_size = stack.m_size;
    m_max_size = stack.m_max_size;
    m_stack_bottom = new T[m_max_size];
    // deep copy stack
    for (unsigned i = 0; i < m_max_size; i++) {
      m_stack_bottom[i] = stack.m_stack_bottom[i];
      if (stack.m_stack_top == &stack.m_stack_bottom[i])
        m_stack_top = &m_stack_bottom[i];
    }
  }

  /*****************************************************************************
   * @name operator=
   * @note overload '=' operator
   * **************************************************************************/
  template <typename T>
  Stack<T>& Stack<T>::operator=(const Stack& stack) {
    // self check
    if (this == &stack) return *this;
    else {
      // clear origin stack
      delete[] m_stack_bottom;
      // generate new stack
      m_size = stack.m_size;
      m_max_size = stack.m_max_size;
      m_stack_bottom = new T[m_max_size];
      // deep copy stack
      for (unsigned i = 0; i < m_max_size; i++) {
        m_stack_bottom[i] = stack.m_stack_bottom[i];
        if (stack.m_stack_top == &stack.m_stack_bottom[i])
          m_stack_top = &m_stack_bottom[i];
      }
    }
  }

  /*****************************************************************************
   * @name Push
   * @param element Given element to be push
   * @brief Push given element to stack
   * @attention if stack is full, trigger capacity expansion
   * **************************************************************************/
  template <typename T>
  void Stack<T>::Push(const T& element) {
    // full check
    if (m_size == m_max_size) Expansion();
    // push
    *++m_stack_top = element;
    m_size++;
  }

  /*****************************************************************************
   * @name Pop
   * @param element Element be poped out
   * @retval true:  pop success
   * @retval false: stack is empty
   * @brief Pop top element from stack and store it
   * **************************************************************************/
  template <typename T>
  bool Stack<T>::Pop(T& element) {
    if (!m_size) return false;
    else {
      element = *m_stack_top--;
      m_size--;
      return true;
    }
  }

  /*****************************************************************************
   * @name Clear
   * @brief Clear stack but keep memory
   * **************************************************************************/
  template <typename T>
  void Stack<T>::Clear() {
    m_size = 0;
    m_stack_top = m_stack_bottom;
  }

  /*****************************************************************************
   * @name GetTop
   * @param element Element on stack top
   * @retval true:  get top success
   * @retval false: stack is empty
   * @brief Get element on stack top
   * **************************************************************************/
  template <typename T>
  bool Stack<T>::GetTop(T& element) const {
    if (m_size == 0) return false;
    else {
      element = *m_stack_top;
      return true;
    }
  }

  /*****************************************************************************
   * @name ShrinktoFit
   * @brief Shrink stack to fit the current size
   * **************************************************************************/
  template <typename T>
  void Stack<T>::ShrinktoFit() {
    if (m_max_size > m_size) {
      if (!m_size) {
        m_max_size = 0;
        delete[] m_stack_bottom;
        m_stack_top = m_stack_bottom = nullptr;
      } else {
        m_max_size = m_size;
        T* temporary = m_stack_bottom;
        m_stack_bottom = new T[m_size];
        for (unsigned i = 0; i < m_size; i++) m_stack_bottom[i] = temporary[i];
        m_stack_top = &m_stack_bottom[m_size - 1];
        delete[] temporary;
      }
    }
  }

  /*****************************************************************************
   * @name Expansion
   * @brief Expand stack capacity by fixed expansion factor(2)
   * **************************************************************************/
  template <typename T>
  void Stack<T>::Expansion() {
    if (!m_max_size) {
      m_max_size = 10;
      m_stack_bottom = new T[m_max_size];
      m_stack_top = m_stack_bottom;
    } else {
      m_max_size *= cExpansionFactor;
      T* temporary = m_stack_bottom;
      m_stack_bottom = new T[m_max_size];
      for (unsigned i = 0; i < m_size; i++) m_stack_bottom[i] = temporary[i];
      m_stack_top = &m_stack_bottom[m_size - 1];
      delete[] temporary;
    }
  }

  /* friend function */
  /*****************************************************************************
   * @name operator<<
   * @note overload '<<' operator
   * **************************************************************************/
  template <typename T>
  std::ostream& operator<<(std::ostream& os, Stack<T>& stack) {
    using namespace std;
    os << "\nInfomation of stack" << endl;
    os << "stack size: " << stack.m_size;
    os << "\tstack max size: " << stack.m_max_size << endl;
    if (stack.m_size > 0) {
      os << "stack elements are as follow: " << endl;
      os << "   top -> " << *stack.m_stack_top << endl;
      for (int i = stack.m_size - 2; i > 0; i--)
        os << "          " << stack.m_stack_bottom[i] << endl;
      os << "bottom -> " << *stack.m_stack_bottom << endl;
    }
    return os;
  }
}  // namespace libofsheerrey

#endif