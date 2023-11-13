#ifndef PRIORITY_QUEUE_
#define PRIORITY_QUEUE_
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <vector>

/**
 * @file priority_queue.hpp
 * @brief Priority queue class template.
 *
 * This template represents a priority queue that can store elements of type T.
 * The elements are sorted based on the specified comparison function.
 *
 * @author Yakup Beyoglu
 * @date November 13, 2023
 * @see https://github.com/yakupbeyoglu
 */
namespace yb {
/**
 * @brief Priority queue class template.
 *
 * This template represents a priority queue that can store elements of type T.
 * The elements are sorted in descending order based on the specified comparison
 * function.
 *
 * @tparam T The type of elements to be stored in the priority queue.
 * @tparam Compare The comparison function for ordering elements. Defaults to
 * std::less<T>.
 */

template <typename T, typename Compare = std::less<T>>
class priority_queue {
 public:
  /**
   * @brief Constructor.
   *
   * Constructs an empty priority queue with the specified comparison function.
   *
   * @param comp The comparison function for ordering elements. Defaults to
   * std::less<T>.
   */
  explicit priority_queue(const Compare &comp = Compare()) : comparator(comp) {}

  /**
   * @brief Copy Constructor.
   *
   * Constructs a priority queue with the same elements and comparison function
   * as the given one.
   *
   * @param other The priority queue to copy.
   */
  priority_queue(const priority_queue &other) {
    std::copy(std::begin(other.queue), std::end(other.queue),
              std::back_inserter(queue));
    comparator = other.comparator;
  }

  /**
   * @brief Copy Assignment Operator.
   *
   * Assigns the contents and comparison function of another priority queue to
   * this one.
   *
   * @param other The priority queue to copy.
   * @return A reference to this priority queue.
   */
  priority_queue &operator=(priority_queue other) {
    swap(*this, other);
    return *this;
  }

  /**
   * @brief Move Constructor.
   *
   * Constructs a priority queue by moving the contents and comparison function
   * from another one.
   *
   * @param other The priority queue to move.
   */
  priority_queue(priority_queue &&other) { swap(*this, other); }

  /**
   * @brief Destructor.
   *
   * Destroys the priority queue, ensuring that elements are deleted if they are
   * pointers.
   */
  ~priority_queue() {
    /// Ensure that delete everything without memory leak
    if constexpr (std::is_pointer<T>::value) {
      for (T *element : queue) {
        if (element != nullptr) {
          delete element;
        }
      }
    }

    queue.clear();
  }

  /**
   * @brief Insert element(s) in place.
   *
   * Inserts one or more elements into the priority queue in-place.
   *
   * @tparam Args The types of the arguments to forward to construct the
   * element.
   * @param args The arguments to forward to construct the element.
   */

  template <typename... Args>
  void emplace(Args &&...args) {
    auto it = std::lower_bound(std::begin(queue), std::end(queue),
                               T(std::forward<Args>(args)...), comparator);
    queue.insert(it, T(std::forward<Args>(args)...));
  }

  /**
   * @brief Insert elements from initializer list.
   *
   * Inserts elements from the provided initializer list into the priority
   * queue.
   *
   * @param list The initializer list containing elements to insert.
   */
  void emplace(const std::initializer_list<T> &list) {
    for (const auto &element : list) {
      auto it = std::lower_bound(std::begin(queue), std::end(queue), element,
                                 comparator);
      queue.insert(it, element);
    }
  }

  /**
   * @brief Remove the element with the highest priority.
   *
   * Removes the element with the highest priority from the priority queue.
   */
  void pop_back() {
    if (!queue.empty()) {
      queue.erase(queue.begin());
    }
  }

  /**
   * @brief Erase element at a specific index.
   *
   * Erases the element at the specified index in the priority queue.
   *
   * @param index The index of the element to erase.
   * @throw std::out_of_range if the index is greater than or equal to the size
   * of the queue.
   */
  void erase(std::size_t index) {
    if (index >= queue.size())
      throw std::out_of_range("index is greater than queue size !");
    auto it = queue.cbegin();
    std::advance(it, index);
    queue.erase(it);
  }

  /**
   * @brief Access element at a specific index.
   *
   * Returns a reference to the element at the specified index in the priority
   * queue.
   *
   * @param index The index of the element to access.
   * @return A reference to the element at the specified index.
   */
  const T &at(std::size_t index) const { return queue[index]; }

  /**
   * @brief Access element at a specific index using subscript operator.
   *
   * Returns a reference to the element at the specified index in the priority
   * queue.
   *
   * @param index The index of the element to access.
   * @return A reference to the element at the specified index.
   */
  const T &operator[](std::size_t index) const { return queue.at(index); }

  /**
   * @brief Iterator to the beginning of the priority queue.
   *
   * @return An iterator to the beginning of the priority queue.
   */

  typename std::vector<T>::iterator begin() { return queue.begin(); }

  /**
   * @brief Iterator to the end of the priority queue.
   *
   * @return An iterator to the end of the priority queue.
   */
  typename std::vector<T>::iterator end() { return queue.end(); }

  /**
   * @brief Const iterator to the beginning of the priority queue.
   *
   * @return A const iterator to the beginning of the priority queue.
   */
  typename std::vector<T>::const_iterator begin() const {
    return queue.begin();
  }

  /**
   * @brief Const iterator to the end of the priority queue.
   *
   * @return A const iterator to the end of the priority queue.
   */
  typename std::vector<T>::const_iterator end() const { return queue.end(); }

  /**
   * @brief Access the element with the highest priority.
   *
   * @return A const reference to the element with the highest priority.
   */
  const T &top() const { return queue.front(); }

  /**
   * @brief Get the size of the priority queue.
   *
   * @return The number of elements in the priority queue.
   */
  std::size_t size() const { return queue.size(); }

  /**
   * @brief Check if the priority queue is empty.
   *
   * @return True if the priority queue is empty, false otherwise.
   */
  bool empty() const { return queue.empty(); }

  /**
   * @brief Swap the contents of two priority queues.
   *
   * @param first The first priority queue.
   * @param second The second priority queue.
   */
  friend void swap(priority_queue<T, Compare> &first,
                   priority_queue<T, Compare> &second) {
    using std::swap;
    swap(first.queue, second.queue);
    swap(first.comparator, second.comparator);
  }

  Compare comparator;  /// Compare function
 private:
  std::vector<T> queue;  // Queue which is sorted
};
}  // namespace yb

#endif
