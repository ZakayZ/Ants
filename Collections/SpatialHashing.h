//
// Created by Artem Novikov on 13.07.2022.
//

#ifndef GEOMETRY_COLLECTIONS_SPATIALHASHING_H_
#define GEOMETRY_COLLECTIONS_SPATIALHASHING_H_

#include <list>
#include <vector>
#include <type_traits>

#include "PositionedData.h"
#include "BoundaryBox.h"

template <typename T>
struct PositionChecker {
 private:
  template <typename TT>
  static auto f(int) -> decltype(std::declval<TT>().GetPosition(), std::true_type()) {}

  template <typename ...>
  static auto f(...) -> std::false_type {}

 public:
  static const bool value = decltype(f<T>(0))::value;
};

template <typename T>
struct PositionPtrChecker {
 private:
  template <typename TT>
  static auto f(int) -> decltype(std::declval<TT>()->GetPosition(), std::true_type()) {}

  template <typename ...>
  static auto f(...) -> std::false_type {}

 public:
  static const bool value = decltype(f<T>(0))::value;
};

template <class T>
static const bool has_position = PositionChecker<T>::value || PositionPtrChecker<T>::value;

template <class Object, typename Space, size_t Dimension, class Alloc>
class SpatialHashing {
 private:
  using DataNode = PositionedData<Object, Space, Dimension>;
  using NodeAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<DataNode>;
  using BucketAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<
      typename std::list<DataNode, NodeAlloc>::iterator>;

 public:
  using iterator = typename std::list<DataNode, NodeAlloc>::iterator;   /// TODO my own iterator with object only
  using const_iterator = typename std::list<DataNode, NodeAlloc>::const_iterator;
  using value_type = Object;

 private:
  using IterAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<iterator>;

 public:
  SpatialHashing(const BoundaryBox<Space, Dimension>& box, const std::array<size_t, Dimension>& divisions)
      : data_(), buckets_(), space_(box), divisions_(divisions) {
    size_t bucket_size = 1;
    for (auto& dim_size : divisions_) {
      bucket_size *= dim_size;
    }
    buckets_.resize(bucket_size);
  }

  SpatialHashing(const SpatialHashing& other) : SpatialHashing(other.space, other.divisions_) {
    for (const auto& object_iter : other.data_) {
      Insert(object_iter->onject, object_iter->position_);
    }
  }

  SpatialHashing(SpatialHashing&& other) noexcept
      : data_(std::move(other.data_)), buckets_(std::move(other.buckets_)),
        divisions_(std::move(other.divisions_)), space_(std::move(other.space_)), size_(other.size_) {
    other.buckets_.resize(buckets_.size());
    other.size_ = 0;
  }

  ~SpatialHashing() = default;

  SpatialHashing& operator=(const SpatialHashing& other) {
    if (&other != this) {
      auto copy = other;
      std::swap(data_, copy.data_);
      std::swap(buckets_, copy.buckets_);
      std::swap(divisions_, copy.data_);
      std::swap(space_, copy.space_);
      std::swap(size_, copy.size_);
    }
    return *this;
  }

  SpatialHashing& operator=(SpatialHashing&& other) noexcept {
    if (&other != this) {
      auto copy = std::move(other);
      std::swap(data_, copy.data_);
      std::swap(buckets_, copy.buckets_);
      std::swap(divisions_, copy.data_);
      std::swap(space_, copy.space_);
      std::swap(size_, copy.size_);
    }
    return *this;
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, const Vector<Space, Dimension>& position, Args&& ... args) {
    auto iter = data_.emplace(pos, std::forward<Args>(args)..., position);
    size_t index = Hash(iter->GetPosition());
    buckets_[index].push_back(iter);
    ++size_;
    return iter;
  }

  template <bool Access = has_position<Object>, typename = std::enable_if_t<Access>>
  iterator emplace(const_iterator pos, Object&& object, const Vector<Space, Dimension>& position) {
    if constexpr (PositionChecker<Object>::value) {
      return emplace(pos, object.GetPosition(), std::move(object));
    } else {
      return emplace(pos, object->GetPosition(), std::move(object));
    }
  }

  iterator insert(const_iterator pos, const Vector<Space, Dimension>& position, const Object& object) {
    return emplace(pos, position, object);
  }

  template <bool Access = has_position<Object>, typename = std::enable_if_t<Access>>
  iterator insert(const_iterator pos, const Object& object) {
    if constexpr (PositionChecker<Object>::value) {
      return insert(pos, object.GetPosition(), object);
    } else {
      return insert(pos, object->GetPosition(), object);
    }
  }

  iterator insert(const_iterator pos, const Vector<Space, Dimension>& position, Object&& object) {
    return emplace(pos, position, std::move(object));
  }

  template <bool Access = has_position<Object>, typename = std::enable_if_t<Access>>
  iterator insert(const_iterator pos, Object&& object) {
    if constexpr (PositionChecker<Object>::value) {
      return insert(pos, object.GetPosition(), std::move(object));
    } else {
      return insert(pos, object->GetPosition(), std::move(object));
    }
  }

  template <typename... Args>
  void emplace_back(const Vector<Space, Dimension>& position, Args&& ... args) {
    emplace(data_.cend(), position, std::forward<Args>(args)...);
  }

  template <bool Access = has_position<Object>, typename = std::enable_if_t<Access>>
  void emplace_back(Object&& object) {
    if constexpr(PositionChecker<Object>::value) {
      emplace_back(object.GetPosition(), std::move(object));
    } else {
      emplace_back(object->GetPosition(), std::move(object));
    }
  }

  void push_back(const Vector<Space, Dimension>& position, const Object& object) {
    insert(data_.cend(), position, object);
  }

  template <bool Access = has_position<Object>, typename = std::enable_if_t<Access>>
  void push_back(const Object& object) {
    if constexpr(PositionChecker<Object>::value) {
      push_back(object.GetPosition(), object);
    } else {
      push_back(object->GetPosition(), object);
    }
  }

  void RegisterMove(iterator it, const Vector<Space, Dimension>& new_position) {
    size_t prev_index = Hash(it->position_);
    size_t new_index = Hash(new_position);
    if (prev_index != new_index) {
      buckets_[prev_index].erase(std::find(buckets_[prev_index].begin(), buckets_[prev_index].end(), it));
      buckets_[new_index].push_back(it);
      it->position_ = new_position;
    }
  }

  template <bool Access = has_position<Object>, typename = std::enable_if_t<Access>>
  void RegisterMove(iterator it) {
    if constexpr (PositionChecker<Object>::value) {
      RegisterMove(it, it->object.GetPosition());
    } else {
      RegisterMove(it, it->object->GetPosition());
    }
  }

  template <bool Access = has_position<Object>, typename = std::enable_if_t<Access>>
  void UpdatePositions() {
    for (auto it = begin(); it != end(); ++it) {
      RegisterMove(it);
    }
  }

  void erase(iterator iter) {
    size_t index = Hash(iter->position_);
    buckets_[index].erase(std::find(buckets_[index].begin(), buckets_[index].end(), iter));
    data_.erase(iter);
    --size_;
  }

  void clear() {
    data_.clear();
    for (auto& bucket : buckets_) {
      bucket.clear();
    }
    size_ = 0;
  }

  template <class Functor, class Predicate>
  void ApplyInBox(const BoundaryBox<Space, Dimension>& box, Functor function, Predicate predicate) {
    std::array<size_t, Dimension> begins;
    std::array<size_t, Dimension> ends;
    for (size_t i = 0; i < Dimension; ++i) {
      begins[i] = BucketIndex(box.GetLeft()[i], i);
      ends[i] = BucketIndex(box.GetRight()[i], i);
    }
    ApplyInBoxIterate<0>(0, begins, ends, function, predicate);
  }

  template <class Predicate, class InputIterator>
  void GetInBox(const BoundaryBox<Space, Dimension>& box, InputIterator input, Predicate predicate) {
    std::array<size_t, Dimension> begins;
    std::array<size_t, Dimension> ends;
    for (size_t i = 0; i < Dimension; ++i) {
      begins[i] = BucketIndex(box.GetLeft()[i], i);
      ends[i] = BucketIndex(box.GetRight()[i], i);
    }
    GetInBoxIterate<0>(0, begins, ends, predicate, input);
  }

  [[nodiscard]] size_t size() const { return size_; }

  [[nodiscard]] bool empty() const { return size_ == 0; }

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
                       InputIterator input, Predicate predicate) {
    if constexpr (Index == Dimension) {
      for (auto& iter : buckets_[current_hash]) {
        if constexpr (PositionChecker<Object>::value) {
          if (predicate(iter->object)) {
            input = iter;
          }
        } else {
          if (predicate(*(iter->object))) {
            input = iter;
          }
        }
      }
    } else {
      auto upper_hash = current_hash * divisions_[Index];
      for (size_t i = std::max(begins[Index], size_t(0)); i < std::min(ends[Index], divisions_[Index]); ++i) {
        GetInBoxIterate<Index + 1>(upper_hash + i, begins, ends, input, predicate);
      }
    }
  }

  template <size_t Index, class Predicate, class Functor>
  void ApplyInBoxIterate(size_t current_hash,
                         const std::array<size_t, Dimension>& begins, const std::array<size_t, Dimension>& ends,
                         Predicate predicate, Functor function) {
    if constexpr (Index == Dimension) {
      for (auto& iter : buckets_[current_hash]) {
        if constexpr (PositionChecker<Object>::value) {
          if (predicate(iter->object)) {
            function(iter->object);
          }
        } else {
          auto& obj = *(iter->object);
          if (predicate(obj)) {
            function(obj);
          }
        }
      }
    } else {
      auto upper_hash = current_hash * divisions_[Index];
      for (size_t i = std::max(begins[Index], size_t(0)); i < std::min(ends[Index], divisions_[Index]); ++i) {
        ApplyInBoxIterate<Index + 1>(upper_hash + i, begins, ends, function, predicate);
      }
    }
  }

  size_t BucketIndex(const Space& coordinate, size_t dimension) const {
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
  size_t size_{};
};

#endif //GEOMETRY_COLLECTIONS_SPATIALHASHING_H_
