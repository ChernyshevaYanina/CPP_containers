#ifndef SRC_INCLUDE_RANDOM_ACCESS_ITERATOR_H
#define SRC_INCLUDE_RANDOM_ACCESS_ITERATOR_H
#include <memory>

namespace my_сontainers {
template <class T>
class randomAccessIterator {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using difference_type = ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;
  randomAccessIterator() = default;
  randomAccessIterator(pointer iter) : iter_(iter) {};
  reference operator*() const { return *iter_; };
  randomAccessIterator& operator++() {
    ++iter_;
    return *this;
  }
  randomAccessIterator operator++(int) {
    randomAccessIterator tmp(*this);
    ++(*this);
    return tmp;
  }
  randomAccessIterator& operator--() {
    --iter_;
    return *this;
  }
  randomAccessIterator operator--(int) {
    randomAccessIterator tmp(*this);
    --(*this);
    return tmp;
  }
  randomAccessIterator& operator+=(difference_type diff) {
    difference_type dist = diff;
    if (dist >= 0) {
      while (dist--) ++iter_;
    } else {
      while (dist++) --iter_;
    }
    return *this;
  };
  friend randomAccessIterator& operator-=(randomAccessIterator it,
                                          difference_type diff) {
    return it.iter_ += -diff;
  };
  friend randomAccessIterator operator+(randomAccessIterator it,
                                        difference_type diff) {
    randomAccessIterator temp(it);
    return temp += diff;
  };
  randomAccessIterator& operator-=(difference_type diff) {
    iter_ -= diff;
    return *this;
  };
  difference_type operator-(const randomAccessIterator& rhs) const {
    return iter_ - rhs.iter_;
  };
  reference operator[](difference_type diff) { return *(iter_ + diff); };
  bool operator<(const randomAccessIterator& other) const {
    return other.iter_ - iter_ > 0;
  };
  bool operator>(const randomAccessIterator& other) const {
    return other.iter_ < iter_;
  };
  bool operator<=(const randomAccessIterator& other) const {
    return !(other.iter_ < iter_);
  };
  bool operator>=(const randomAccessIterator& other) const {
    return !(iter_ < other.iter_);
  };
  bool operator==(const randomAccessIterator& other) {
    return iter_ == other.iter_;
  };
  bool operator!=(const randomAccessIterator& other) {
    return iter_ != other.iter_;
  };

 private:
  pointer iter_;
};

template <class T>
class constRandomAccessIterator {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using const_reference = const T&;
  using const_iterator = const T*;
  using difference_type = ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  constRandomAccessIterator() = default;
  constRandomAccessIterator(const_iterator iter) : iter_(iter) {}

  constRandomAccessIterator& operator++() {
    ++iter_;
    return *this;
  }
  constRandomAccessIterator operator++(int) {
    constRandomAccessIterator tmp(*this);
    ++(*this);
    return tmp;
  }
  constRandomAccessIterator& operator--() {
    --iter_;
    return *this;
  }
  constRandomAccessIterator operator--(int) {
    constRandomAccessIterator tmp(*this);
    --(*this);
    return tmp;
  }
  constRandomAccessIterator& operator+=(difference_type diff) {
    difference_type dist = diff;
    if (dist >= 0) {
      while (dist--) ++iter_;
    } else {
      while (dist++) --iter_;
    }
    return *this;
  };
  friend constRandomAccessIterator& operator-=(constRandomAccessIterator it,
                                               difference_type diff) {
    return it.iter_ += -diff;
  };
  friend constRandomAccessIterator operator+(constRandomAccessIterator it,
                                             difference_type diff) {
    constRandomAccessIterator temp(it);
    return temp += diff;
  };
  constRandomAccessIterator& operator-=(difference_type diff) {
    iter_ -= diff;
    return *this;
  };
  difference_type operator-(const constRandomAccessIterator& rhs) const {
    return iter_ - rhs.iter_;
  };
  const_reference operator[](difference_type diff) { return *(iter_ + diff); };
  bool operator<(const constRandomAccessIterator& other) const {
    return other.iter_ - iter_ > 0;
  };
  bool operator>(const constRandomAccessIterator& other) const {
    return other.iter_ < iter_;
  };
  bool operator<=(const constRandomAccessIterator& other) const {
    return !(other.iter_ < iter_);
  };
  bool operator>=(const constRandomAccessIterator& other) const {
    return !(iter_ < other.iter_);
  };
  bool operator==(const constRandomAccessIterator& other) {
    return iter_ == other.iter_;
  };
  bool operator!=(const constRandomAccessIterator& other) {
    return iter_ != other.iter_;
  };

 private:
  const_iterator iter_;
};
}  // namespace myContainers

#endif  // SRC_INCLUDE_RANDOM_ACCESS_ITERATOR_H