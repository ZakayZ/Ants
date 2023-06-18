//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_UTILS_CONDITIONALITERATOR_H_
#define ANTS_NEW_UTILS_CONDITIONALITERATOR_H_

#include <iterator>

template <class Iterator, class Predicate>
class ConditionalIterator {
 public:
  using difference_type = typename Iterator::difference_type;

  using value_type = typename Iterator::value_type;

  using reference = typename Iterator::reference;

  using pointer = typename Iterator::pointer;

  using iterator_category = typename std::forward_iterator_tag;

  ConditionalIterator(const Iterator& iterator, const Iterator& end, Predicate&& predicate)
      : iterator_(iterator), border_(end), predicate_(std::move(predicate)) {}

  ConditionalIterator(const ConditionalIterator& iter) = default;

  ConditionalIterator(ConditionalIterator&& iter) noexcept = default;

  ConditionalIterator& operator=(const ConditionalIterator& iter) = default;

  ConditionalIterator& operator=(ConditionalIterator&& iter) noexcept = default;

  pointer operator->() const {
    return (iterator_.operator->());
  }

  reference operator*() const {
    return *iterator_;
  }

  ConditionalIterator& operator++() {
    do {
      ++iterator_;
    } while (!predicate_(*iterator_) && iterator_ != border_);
    return *this;
  }

  ConditionalIterator operator++(int) {
    auto copy = *this;
    this->operator++();
    return copy;
  }

  bool operator==(const ConditionalIterator& other) const {
    return iterator_ == other.iterator_;
  }

  bool operator<(const ConditionalIterator& other) const {
    return iterator_ > other.iterator_;
  }

  bool operator<=(const ConditionalIterator& other) const {
    return iterator_ >= other.iterator_;
  }

  bool operator>(const ConditionalIterator& other) const {
    return iterator_ < other.iterator_;
  }

  bool operator>=(const ConditionalIterator& other) const {
    return iterator_ <= other.iterator_;
  }

  bool operator!=(const ConditionalIterator& other) const {
    return iterator_ != other.iterator_;
  }

 private:
  Iterator iterator_;
  Iterator border_;
  Predicate predicate_;
};

#endif //ANTS_NEW_UTILS_CONDITIONALITERATOR_H_
