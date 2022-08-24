/*******************************************************************************
 * @file linked_queue.hpp
 * @author sheer.rey
 * @date Aug. 24, 2022
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
 * Tip.1 I hope you know is there may be some slapdash mistake.
 *
 * Another thing is, the reason why I choose to use full english comment is I
 * want to improve my english level by this way.
 *
 * Tip.2 is if you find some grammatical error or others and tell me that
 * I will be very greatful to you! The style of these pair of files may be
 * variable, cause it's also in my C++ learning process, so the programme
 * style may transform C to C++ gradually.
 * ****************************************************************************/

#ifndef _SEQUENTIAL_QUEUE_HPP_
#define _SEQUENTIAL_QUEUE_HPP_

#include <initializer_list>

/* my (sheer.rey) namespace */
namespace libofsheerrey {
  /* queue class template declaration */
  template <typename T>
  class Queue {
   private:
    struct Node {
      T value = 0;
      Node* prev = nullptr;
      Node* next = nullptr;
      Node() = default;
      Node(T val) : value(val) {}
      Node(T val, Node* pre, Node* nxt) : value(val), prev(pre), next(nxt) {}
      Node(const Node&) = default;
      Node(Node&&) = delete;
      Node& operator=(const Node&) = delete;
      Node& operator=(Node&&) = delete;
    };

    std::size_t m_size = 0;
    Node* m_queue_front = nullptr;
    Node* m_queue_back = nullptr;

   public:
    /* Special member functions */
    Queue();
    Queue(const std::size_t size, const T& element);
    Queue(const std::initializer_list<T>& queue);
    Queue(const Queue& queue);
    Queue(Queue&& queue);
    ~Queue();
    Queue& operator=(const Queue& queue);
    Queue& operator=(Queue&& queue);

    /* General member functions */
    void Push(const T& element);
    bool Pop(T& element);
    bool Pop();
    void Clear();
    bool Front(T& element) const;
    bool Back(T& element) const;
    const T& Front() const;
    const T& Back() const;

    bool IsEmpty() const { return !m_size; }
    std::size_t QueueSize() const { return m_size; }
  };

  /* function definition of template class Queue */

  /* public member function */

  /*****************************************************************************
   * @name Queue
   * @note Constructor
   * @brief Initialize an empty Queue
   * **************************************************************************/
  template <typename T>
  inline Queue<T>::Queue() : m_size(0) {}

  /*****************************************************************************
   * @name Queue
   * @note Constructor
   * @param max_size The max queue capacity given by
   * @param element will copy to queue
   * @brief Initialize Queue with given size and size number of elements will
   *        copy to Queue
   * **************************************************************************/
  template <typename T>
  Queue<T>::Queue(std::size_t size, const T& element) : m_size(size) {
    // construct first node
    if (size > 0) {
      m_queue_back = m_queue_front = new Node(element);
    } else {
      return;
    }

    // construct other nodes
    while (--size) {
      m_queue_back->next = new Node(element, m_queue_back, nullptr);
      m_queue_back = m_queue_back->next;
    }
  }

  /*****************************************************************************
   * @name Queue
   * @note Constructor
   * @param queue Initiative element list, front first
   * @brief Initialize queue with given initialization list
   * @attention The capacity of queue will expand to be containable with all
   *            element of initiative list
   * **************************************************************************/
  template <typename T>
  Queue<T>::Queue(const std::initializer_list<T>& queue)
      : m_size(queue.size()) {
    typename std::initializer_list<T>::iterator it = queue.begin();

    // construct first node
    if (m_size > 0) { m_queue_back = m_queue_front = new Node(*it++); }

    // construct other nodes
    while (it != queue.end()) {
      m_queue_back->next = new Node(*it++, m_queue_back, nullptr);
      m_queue_back = m_queue_back->next;
    }
  }

  /*****************************************************************************
   * @name Queue
   * @note Copy constructor
   * @param queue Queue reference to be copy
   * @brief Initialize queue with given queue object
   * **************************************************************************/
  template <typename T>
  Queue<T>::Queue(const Queue& queue) : m_size(queue.m_size) {
    // deep copy first node
    if (m_size > 0) {
      m_queue_back = m_queue_front = new Node(queue.m_queue_front->value);
    } else {
      return;
    }

    // deep copy other nodes
    Node* temp = queue.m_queue_front->next;
    while (temp != nullptr) {
      m_queue_back->next = new Node(temp->value, m_queue_back, nullptr);
      m_queue_back = m_queue_back->next;
      temp = temp->next;
    }
  }

  /*****************************************************************************
   * @name Queue
   * @note Move constructor
   * @param queue Queue rvalue reference to be copy
   * @brief Initialize queue with given queue object
   * **************************************************************************/
  template <typename T>
  Queue<T>::Queue(Queue&& queue)
      : m_size(queue.m_size),
        m_queue_front(queue.m_queue_front),
        m_queue_back(queue.m_queue_back) {
    // move underline list
    queue.m_queue_back = queue.m_queue_front = nullptr;
    queue.m_size = 0;
  }

  /*****************************************************************************
   * @name Queue
   * @note Destructor
   * **************************************************************************/
  template <typename T>
  Queue<T>::~Queue() {
    Clear();
  }

  /*****************************************************************************
   * @name copy operator=
   * @note overload '=' operator
   * **************************************************************************/
  template <typename T>
  Queue<T>& Queue<T>::operator=(const Queue& queue) {
    // self check
    if (this != &queue) {
      // release origin queue memory
      Clear();

      // set new queue properties
      m_size = queue.m_size;

      // deep copy first node
      if (m_size > 0) {
        m_queue_back = m_queue_front = new Node(queue.m_queue_front->value);
      } else {
        return *this;
      }

      // deep copy other nodes
      Node* temp = queue.m_queue_front->next;
      while (temp != nullptr) {
        m_queue_back->next = new Node(temp->value, m_queue_back, nullptr);
        m_queue_back = m_queue_back->next;
        temp = temp->next;
      }
    }

    return *this;
  }

  /*****************************************************************************
   * @name move operator=
   * @note overload '=' operator
   * **************************************************************************/
  template <typename T>
  Queue<T>& Queue<T>::operator=(Queue&& queue) {
    // self check
    if (this != &queue) {
      // release origin queue memory
      Clear();

      // set new queue properties
      m_size = queue.m_size;
      m_queue_front = queue.m_queue_front;
      m_queue_back = queue.m_queue_back;

      // move underline list
      queue.m_queue_back = queue.m_queue_front = nullptr;
      queue.m_size = 0;
    }
    return *this;
  }

  /*****************************************************************************
   * @name Push
   * @param element Given element to be push
   * @brief Push given element to queue
   * **************************************************************************/
  template <typename T>
  void Queue<T>::Push(const T& element) {
    // push to queue back
    if (IsEmpty()) {
      m_queue_front = m_queue_back = new Node(element);
    } else {
      m_queue_back->next = new Node(element, m_queue_back, nullptr);
      m_queue_back = m_queue_back->next;
    }
    ++m_size;
  }

  /*****************************************************************************
   * @name Pop
   * @param element Element be poped out
   * @retval true: pop success
   * @retval false: queue is empty
   * @brief Pop top element from queue and store it
   * **************************************************************************/
  template <typename T>
  bool Queue<T>::Pop(T& element) {
    // empty check
    if (IsEmpty()) { return false; }

    // pop element
    element = m_queue_front->value;
    if (m_queue_back == m_queue_front) {
      // only 1 node in queue
      delete m_queue_back;
      m_queue_front = m_queue_back = nullptr;
    } else {
      // more than 1 node in queue
      m_queue_front = m_queue_front->next;
      delete m_queue_front->prev;
      m_queue_front->prev = nullptr;
    }
    --m_size;
    return true;
  }

  /*****************************************************************************
   * @name Pop
   * @retval true: pop success
   * @retval false: queue is empty
   * @brief Pop top element from queue
   * **************************************************************************/
  template <typename T>
  bool Queue<T>::Pop() {
    // empty check
    if (IsEmpty()) { return false; }

    // pop element
    if (m_size == 1) {
      // only 1 node in queue
      delete m_queue_back;
      m_queue_front = m_queue_back = nullptr;
    } else {
      // more than 1 node in queue
      m_queue_front = m_queue_front->next;
      delete m_queue_front->prev;
      m_queue_front->prev = nullptr;
    }
    --m_size;
    return true;
  }

  /*****************************************************************************
   * @name Clear
   * @brief Clear queue
   * **************************************************************************/
  template <typename T>
  void Queue<T>::Clear() {
    while (m_queue_front != nullptr) {
      Node* temp = m_queue_front;
      m_queue_front = m_queue_front->next;
      delete temp;
    }
    m_queue_front = m_queue_back = nullptr;
    m_size = 0;
  }

  /*****************************************************************************
   * @name Front
   * @param element Element on queue front
   * @retval true: get front success
   * @retval false: queue is empty
   * @brief Get element on queue front
   * **************************************************************************/
  template <typename T>
  bool Queue<T>::Front(T& element) const {
    // empty check
    if (IsEmpty()) { return false; }

    // get front element
    element = m_queue_front->value;
    return true;
  }

  /*****************************************************************************
   * @name Front
   * @retval a reference to queue front
   * @brief Get element on queue front
   * @attention This method may cause using null pointer error
   * **************************************************************************/
  template <typename T>
  inline const T& Queue<T>::Front() const {
    // get front element
    return m_queue_front->value;
  }

  /*****************************************************************************
   * @name Back
   * @param element Element on queue back
   * @retval true: get back success
   * @retval false: queue is empty
   * @brief Get element on queue back
   * **************************************************************************/
  template <typename T>
  bool Queue<T>::Back(T& element) const {
    // empty check
    if (IsEmpty()) { return false; }

    // get back element
    element = m_queue_back->value;
    return true;
  }

  /*****************************************************************************
   * @name Back
   * @retval true: get back success
   * @brief Get element on queue back
   * @attention This method may cause using null pointer error
   * **************************************************************************/
  template <typename T>
  inline const T& Queue<T>::Back() const {
    // get back element
    return m_queue_back->value;
  }
}  // namespace libofsheerrey

#endif