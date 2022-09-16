//
// Created by Artem Novikov on 13.07.2022.
//

#ifndef GEOMETRY_COLLECTIONS_SPATIALHASHING_H_
#define GEOMETRY_COLLECTIONS_SPATIALHASHING_H_

#include <list>
#include <vector>
#include "PositionedData.h"
#include "BoundaryBox.h"

template <class Object, typename Space, size_t Dimension, class Alloc>
class SpatialHashing {
 private:
  using DataNode = PositionedData<Object, Space, Dimension>;
  using NodeAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<DataNode>;
  using BucketAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<
      typename std::list<DataNode, NodeAlloc>::iterator>;
 public:
  using iterator = typename std::list<DataNode, NodeAlloc>::iterator;
  using const_iterator = typename std::list<DataNode, NodeAlloc>::const_iterator;
 private:
  using IterAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<iterator>;
 public:
  SpatialHashing(const BoundaryBox<Space, Dimension>& box, const std::array<size_t, Dimension>& divisions)
      : space_(box), divisions_(divisions) {}

  SpatialHashing(const SpatialHashing& other)
      : space_(other.space_), divisions_(other.divisions_) {
    for (const auto& object_iter : other.data_) {
      Insert(object_iter->onject, object_iter->position_);
    }
  }

  SpatialHashing(SpatialHashing&& other) noexcept {
    /// TODO
  }

  ~SpatialHashing() = default;

  SpatialHashing& operator=(const SpatialHashing& other);

  SpatialHashing& operator=(SpatialHashing&& other) noexcept; /// TODO

  iterator Insert(const Object& object, const Vector<Space, Dimension>& position) {
    data_.emplace_back(object, position);
    auto iter = --data_.end();
    size_t index = Hash(position);
    buckets_[index].push_back(iter);
    ++size_;
    return iter;
  }

  void Move(iterator iter, const Vector<Space, Dimension>& new_position) {
    size_t prev_index = Hash(iter->position_);
    size_t new_index = Hash(new_position);
    if (prev_index != new_index) {
      buckets_[prev_index].erase(std::find(buckets_[prev_index].begin(), buckets_[prev_index].end(), iter));
      buckets_[new_index].push_back(iter);
      iter->position_ = new_position;
    }
  }

  void Erase(iterator iter) {
    size_t index = Hash(iter->position_);
    buckets_[index].erase(std::find(buckets_[index].begin(), buckets_[index].end(), iter));
    data_.erase(iter);
    --size_;
  }

  void Clear() {
    while (!IsEmpty()) {
      Erase(data_.begin());
    }
  }

  template <class Functor, class Predicate>
  void ApplyInBox(const BoundaryBox<Space, Dimension>& box, Functor& function, Predicate& predicate) {
    std::list<iterator, IterAlloc> objects;
    std::array<size_t, Dimension> begins;
    std::array<size_t, Dimension> ends;
    for (size_t i = 0; i < Dimension; ++i) {
      begins[i] = BucketIndex(box.GetLeft()[i], i);
      ends[i] = BucketIndex(box.GetRight()[i], i);
    }
    ApplyInBoxIterate<0>(0, begins, ends, function, predicate);
    return objects;
  }

  template <class Predicate, class InputIterator>
  void GetInBox(const BoundaryBox<Space, Dimension>& box, Predicate& predicate, InputIterator input) {
    std::array<size_t, Dimension> begins;
    std::array<size_t, Dimension> ends;
    for (size_t i = 0; i < Dimension; ++i) {
      begins[i] = BucketIndex(box.GetLeft()[i], i);
      ends[i] = BucketIndex(box.GetRight()[i], i);
    }
    GetInBoxIterate<0>(0, begins, ends, predicate, input);
  }

  size_t GetSize() const { return size_; }
  bool IsEmpty() const { return size_ == 0; }

  iterator begin() { return data_.begin(); }
  const_iterator begin() const { return data_.cbegin(); }
  const_iterator cbegin() { return data_.cbegin(); }

  iterator end() { return data_.end(); }
  const_iterator end() const { return data_.cend(); }
  const_iterator cend() { return data_.cend(); }

 private:
  template <size_t Index, class Predicate, class InputIterator>
  void GetInBoxIterate(size_t current_hash,
                       const std::array<size_t, Dimension>& begins, const std::array<size_t, Dimension>& ends,
                       Predicate& predicate, InputIterator input) const {
    if constexpr (Index == Dimension) {
      for (auto& iter : buckets_[current_hash]) {
        if (predicate(iter->object)) {
          input.push_back(iter);
        }
      }
    } else {
      for (size_t i = begins[Index]; i < ends[Index]; ++i) {
        GetInBoxIterate<Index + 1>(current_hash + i * divisions_[Index], begins, ends, predicate, input);
      }
    }
  }

  template <size_t Index, class Predicate, class Functor>
  void ApplyInBoxIterate(size_t current_hash,
                         const std::array<size_t, Dimension>& begins, const std::array<size_t, Dimension>& ends,
                         Predicate& predicate, Functor& function) const {
    if constexpr (Index == Dimension) {
      for (auto& iter : buckets_[current_hash]) {
        if (predicate(iter->object)) {
          function(iter->object);
        }
      }
    } else {
      for (size_t i = begins[Index]; i < ends[Index]; ++i) {
        ApplyInBoxIterate<Index + 1>(current_hash + i * divisions_[Index], begins, ends, function, predicate);
      }
    }
  }

  size_t BucketIndex(const Space& coordinate, size_t dimension) {
    return ((coordinate - space_.GetLeft()[dimension]) / (space_.GetRight()[dimension] - space_.GetLeft()[dimension]))
        * divisions_[dimension];
  }

  size_t Hash(const Vector<Space, Dimension>& position) const {
    size_t hash = 0;
    for (size_t i = 0; i < Dimension; ++i) {
      hash = hash * divisions_[i] + BucketIndex(position[i], i);
    }
    return hash;
  }

  std::list<DataNode, NodeAlloc> data_;
  std::vector<std::list<typename std::list<DataNode, NodeAlloc>::iterator>> buckets_;
  std::array<size_t, Dimension> divisions_;
  BoundaryBox<Space, Dimension> space_;
  size_t size_ = 0;
};

#endif //GEOMETRY_COLLECTIONS_SPATIALHASHING_H_
