/*******************************************************************************
 * @file sequential_queue.hpp
 * @author sheer.rey
 * @date Aug. 22, 2022
 *
 * @attention index 0 of queue array is front.
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
    // use to expand queue size while
    T* m_underline_array = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 10;
    std::size_t m_queue_front = 0;
    std::size_t m_queue_back = 0;

    static const unsigned cExpansionFactor = 2;

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
    std::size_t QueueCapacity() const { return m_capacity; }

    void ShrinktoFit();

   protected:
    /* Protected Functions */
    void Expansion();
  };

  /* function definition of template class Queue */

  /* public member function */

  /*****************************************************************************
   * @name Queue
   * @note Constructor
   * @brief Initialize an empty Queue
   * **************************************************************************/
  template <typename T>
  Queue<T>::Queue() {
    // request memory
    m_underline_array = new T[m_capacity];
  }

  /*****************************************************************************
   * @name Queue
   * @note Constructor
   * @param max_size The max queue capacity given by
   * @param element will copy to queue
   * @brief Initialize Queue with given size and size number of elements will
   *        copy to Queue
   * @attention The capacity of queue will expand to be greater than \p size
   * **************************************************************************/
  template <typename T>
  Queue<T>::Queue(const std::size_t size, const T& element) : m_size(size) {
    // calculate capacity to contain more than size numbers of elements
    while (m_capacity <= m_size) { m_capacity *= cExpansionFactor; }

    // request memory
    m_underline_array = new T[m_capacity];

    // initialize first i element of queue
    for (std::size_t i = 0; i < m_size; ++i) { m_underline_array[i] = element; }

    // set front and back index
    m_queue_front = 0;
    m_queue_back = m_size;
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
    // calculate capacity to contain enough numbers of elements
    while (m_capacity <= m_size) { m_capacity *= cExpansionFactor; }

    // request memory
    m_underline_array = new T[m_capacity];

    // set front and back index
    m_queue_front = m_queue_back = 0;

    // initialize element of queue
    for (const T& e : queue) { m_underline_array[m_queue_back++] = e; }
  }

  /*****************************************************************************
   * @name Queue
   * @note Copy constructor
   * @param queue Queue reference to be copy
   * @brief Initialize queue with given queue object
   * **************************************************************************/
  template <typename T>
  Queue<T>::Queue(const Queue& queue)
      : m_size(queue.m_size),
        m_capacity(queue.m_capacity),
        m_queue_front(queue.m_queue_front),
        m_queue_back(queue.m_queue_back) {
    // request memory
    m_underline_array = new T[m_capacity];

    // deep copy queue
    for (std::size_t i = m_queue_front; i != m_queue_back; ++i) {
      if (i >= m_capacity) { i %= m_capacity; }
      m_underline_array[i] = queue.m_underline_array[i];
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
        m_capacity(queue.m_capacity),
        m_queue_front(queue.m_queue_front),
        m_queue_back(queue.m_queue_back) {
    // move underline array
    m_underline_array = queue.m_underline_array;
    queue.m_underline_array = nullptr;
    queue.m_capacity = queue.m_size = 0;
    queue.m_queue_front = queue.m_queue_back = 0;
  }

  /*****************************************************************************
   * @name ~Queue
   * @note destructor
   * **************************************************************************/
  template <typename T>
  Queue<T>::~Queue() {
    delete[] m_underline_array;
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
      delete[] m_underline_array;

      // set new queue properties
      m_size = queue.m_size;
      m_capacity = queue.m_capacity;
      m_queue_front = queue.m_queue_front;
      m_queue_back = queue.m_queue_back;

      // request memory
      m_underline_array = new T[m_capacity];

      // deep copy queue
      for (std::size_t i = m_queue_front; i != m_queue_back; ++i) {
        if (i > m_capacity) { i %= m_capacity; }
        m_underline_array[i] = queue.m_underline_array[i];
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
      delete[] m_underline_array;

      // set new queue properties
      m_size = queue.m_size;
      m_capacity = queue.m_capacity;
      m_queue_front = queue.m_queue_front;
      m_queue_back = queue.m_queue_back;

      // move underline array
      m_underline_array = queue.m_underline_array;
      queue.m_underline_array = nullptr;
      queue.m_capacity = queue.m_size = 0;
      queue.m_queue_front = queue.m_queue_back = 0;
    }
    return *this;
  }

  /*****************************************************************************
   * @name Push
   * @param element Given element to be push
   * @brief Push given element to queue
   * @attention if queue is full, trigger capacity expansion
   * **************************************************************************/
  template <typename T>
  void Queue<T>::Push(const T& element) {
    // full check
    if (m_size == m_capacity) { Expansion(); }

    // push to queue back
    m_underline_array[m_queue_back++] = element;
    if (m_queue_back >= m_capacity) { m_queue_back = 0; }
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
    element = m_underline_array[m_queue_front++];
    if (m_queue_front >= m_capacity) { m_queue_front = 0; }
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
    m_queue_front = (m_queue_front + 1) % m_capacity;
    --m_size;
    return true;
  }

  /*****************************************************************************
   * @name Clear
   * @brief Clear queue but keep memory
   * **************************************************************************/
  template <typename T>
  void Queue<T>::Clear() {
    m_size = 0;
    m_queue_back = m_queue_front;
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
    element = m_underline_array[m_queue_front];
    return true;
  }

  /*****************************************************************************
   * @name Front
   * @retval a reference to queue front
   * @brief Get element on queue front
   * @attention This method may cause out of bounds error
   * **************************************************************************/
  template <typename T>
  inline const T& Queue<T>::Front() const {
    // get front element
    return m_underline_array[m_queue_front];
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
    element = m_underline_array[(m_queue_back + m_capacity - 1) % m_capacity];
    return true;
  }

  /*****************************************************************************
   * @name Back
   * @retval true: get back success
   * @brief Get element on queue back
   * @attention This method may cause out of bounds error
   * **************************************************************************/
  template <typename T>
  inline const T& Queue<T>::Back() const {
    // get back element
    return m_underline_array[(m_queue_back + m_capacity - 1) % m_capacity];
  }

  /*****************************************************************************
   * @name ShrinktoFit
   * @brief Shrink queue to fit the current size
   * **************************************************************************/
  template <typename T>
  void Queue<T>::ShrinktoFit() {
    // shrinkable check
    if (m_capacity > m_size) {
      // empty check
      if (IsEmpty()) {
        // release memory
        delete[] m_underline_array;

        // set new properties
        m_capacity = m_queue_back = m_queue_front = 0;
      } else {
        // request new memory
        T* new_underline_array = new T[m_size];

        // copy queue
        std::size_t index = 0;
        while (index < m_size) {
          new_underline_array[index++] = m_underline_array[m_queue_front++];
          if (m_queue_front >= m_capacity) { m_queue_front %= m_capacity; }
        }

        // release old underline array
        delete[] m_underline_array;

        // set new properties
        m_underline_array = new_underline_array;
        m_queue_front = 0;
        m_queue_back = m_capacity = m_size;
      }
    }
  }

  /*****************************************************************************
   * @name Expansion
   * @brief Expand queue capacity by fixed expansion factor(2)
   * **************************************************************************/
  template <typename T>
  void Queue<T>::Expansion() {
    // set new capacity
    std::size_t new_capacity =
        m_capacity < 10 ? 10 : m_capacity * cExpansionFactor;

    // request new memory
    T* new_underline_array = new T[new_capacity];

    // copy queue
    std::size_t index = 0;
    while (index < m_size) {
      new_underline_array[index++] = m_underline_array[m_queue_front++];
      if (m_queue_front >= m_capacity) { m_queue_front %= m_capacity; }
    }

    // release old underline array
    delete[] m_underline_array;

    // set new properties
    m_capacity = new_capacity;
    m_underline_array = new_underline_array;
    m_queue_front = 0;
    m_queue_back = m_size;
  }
}  // namespace libofsheerrey

#endif