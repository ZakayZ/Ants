//
// Created by Artem Novikov on 13.07.2022.
//

#ifndef GEOMETRY_COLLECTIONS_SPATIALTREE_H_
#define GEOMETRY_COLLECTIONS_SPATIALTREE_H_

#include <array>
#include <list>
#include "Vector.h"
#include "BoundaryBox.h"
#include "PositionedData.h"

template <class Object, typename Space, size_t Dimension, class Alloc>
class SpatialTree {
 private:
  using DataNode = PositionedData<Object, Space, Dimension>;
  using NodeAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<DataNode>;

 public:
  using iterator = typename std::list<DataNode, NodeAlloc>::iterator;
  using const_iterator = typename std::list<DataNode, NodeAlloc>::const_iterator;

 private:
  using IterAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<iterator>;

 public:
  static size_t DefaultCapacity;
  static size_t DefaultDepth;

  SpatialTree() = delete;

  explicit SpatialTree(const BoundaryBox<Space, Dimension>& control_box) : tree_(control_box) {}

  SpatialTree(const BoundaryBox<Space, Dimension>& control_box, size_t depth)
      : tree_(control_box, depth) {}

  SpatialTree(const BoundaryBox<Space, Dimension>& control_box, size_t depth, size_t max_capacity)
      : tree_(control_box, depth, max_capacity) {}

  SpatialTree(const SpatialTree& other)
      : tree_(other.tree_.GetControlSpace(), other.tree_.GetMaxDepth(), other.tree_.GetMaxCapacity()) {
    for (auto& data : other) {
      Insert(data);
    }
  }

  SpatialTree(SpatialTree&& other) noexcept = default;

  ~SpatialTree() = default;

  SpatialTree& operator=(const SpatialTree& other) {
    if (this != &other) {
      auto copy = other;
      std::swap(tree_, copy.tree_);
      std::swap(data_, copy.data_);
    }
    return *this;
  }

  SpatialTree& operator=(SpatialTree&& other) noexcept = default;

  iterator Insert(const Object& object, const Vector<Space, Dimension>& position) {
    data_.emplace_back(object, position);
    auto iter = --data_.end();
    tree_.Insert(iter);
    return iter;
  }

  void Move(iterator iter, const Vector<Space, Dimension>& new_position) {
    tree_.Move(iter, new_position);
    iter->position = new_position;
  }

  void Erase(iterator iter) {
    tree_.Erase(iter);
    data_.erase(iter);
  }

  void Clear() {
    while (!IsEmpty()) {
      Erase(data_.begin());
    }
  }

  template <class Functor, class Predicate>
  void ApplyInBox(const BoundaryBox<Space, Dimension>& search_box, Functor& function, Predicate& condition) {
    tree_.ApplyInBox(search_box, function, condition);
  }

  template <class Predicate, class InputIterator>
  void GetInBox(const BoundaryBox<Space, Dimension>& search_box, Predicate& condition, InputIterator input) {
    tree_.GetInBox(search_box, condition, input);
  }

  size_t GetMaxDepth() const { return tree_.GetMaxDepth(); }

  auto GetControlSpace() const { return tree_.GetControlSpace(); }

  size_t GetMaxCapacity() const { return tree_.GetMaxCapacity(); }

  size_t GetSize() const { return tree_.GetSize(); }
  bool IsEmpty() const { return GetSize() == 0; }

  iterator begin() { return data_.begin(); }
  const_iterator begin() const { return data_.cbegin(); }
  const_iterator cbegin() { return data_.cbegin(); }

  iterator end() { return data_.end(); }
  const_iterator end() const { return data_.cend(); }
  const_iterator cend() { return data_.cend(); }

 private:
  iterator Insert(const DataNode& node) {
    data_.emplace_back(node);
    auto iter = --data_.end();
    tree_.Insert(iter);
    return iter;
  }

  class Tree;

  std::list<DataNode, NodeAlloc> data_;
  Tree tree_;
};

template <class Object, typename Space, size_t Dimension, class Alloc>
size_t SpatialTree<Object, Space, Dimension, Alloc>::DefaultCapacity = 20;

template <class Object, typename Space, size_t Dimension, class Alloc>
size_t SpatialTree<Object, Space, Dimension, Alloc>::DefaultDepth = 7;

////////////////////////////////////////////////DEFINITION//////////////////////////////////////////////////////////////

template <class Object, typename Space, size_t Dimension, class Alloc>
class SpatialTree<Object, Space, Dimension, Alloc>::Tree {
 public:
  Tree() = delete;
  Tree(const Tree& other) = delete;
  Tree(Tree&& other) noexcept = default;

  Tree(const BoundaryBox<Space, Dimension>& control_box) : control_space_(control_box) {}

  Tree(const BoundaryBox<Space, Dimension>& control_box, size_t depth) : control_space_(control_box), depth_(depth) {}

  Tree(const BoundaryBox<Space, Dimension>& control_box, size_t depth, size_t max_capacity)
      : control_space_(control_box), depth_(depth), max_capacity_(max_capacity) {}

  ~Tree() = default;
  Tree& operator=(const Tree& other) = delete;
  Tree& operator=(Tree&& other) noexcept = default;

  void SetMaxDepth(size_t new_depth) {
    depth_ = new_depth;
    if (new_depth == 0) {
      Unite();
    } else {
      if (Divided()) {
        for (size_t i = 0; i < subtrees_.size(); ++i) {
          if (ValidSubTree(i)) {
            subtrees_[i]->SetMaxDepth(depth_ - 1);
          }
        }
      } else {
        if (Divisible()) {
          SubDivide();
        }
      }
    }
  }

  size_t GetMaxDepth() const { return depth_; }

  auto GetControlSpace() const { return control_space_; }

  auto GetMaxCapacity() const { return max_capacity_; }

  size_t GetSize() const { return size_; }

  void Insert(iterator iter) {
    if (Divided()) {
      auto index = GetSubTreeIndex(iter->position);
      CheckSubTree(index);
      subtrees_[index]->Insert(iter);
    } else {
      points_.push_back(iter);
      if (Divisible()) {
        SubDivide();
      }
    }
    ++size_;
  }

  void Move(iterator iter, const Vector<Space, Dimension>& new_position) {
    if (Divided()) {
      auto old_index = GetSubTreeIndex(iter->position);
      auto new_index = GetSubTreeIndex(new_position);
      if (old_index == new_index) {
        subtrees_[old_index]->Move(iter, new_position);
      } else {
        CheckSubTree(new_index);
        subtrees_[new_index]->Insert(iter);
        subtrees_[old_index]->Erase(iter);
      }
    }
  }

  void Erase(iterator iter) {
    if (Divided()) {
      subtrees_[GetSubTreeIndex(iter->position)]->Erase(iter);
      if (size_ < max_capacity_ / 2) {
        Unite();
      }
    } else {
      points_.erase(std::find(points_.begin(), points_.end(), iter));
    }
    --size_;
  }

  template <class Functor, class Predicate>
  void ApplyInBox(const BoundaryBox<Space, Dimension>& search_box, Functor& function, Predicate& condition) {
    if (Divided()) {
      for (size_t i = 0; i < subtrees_.size(); ++i) {
        auto subtree_box = GetBoxByIndex(i);
        if (ValidSubTree(i) && search_box.Intersects(subtree_box)) {
          subtrees_[i]->ApplyInBox(search_box, function, condition);
        }
      }
    } else {
      if (search_box.Intersects(control_space_)) {
        for (auto& point : points_) {
          if (search_box.Contains(point->position) && condition(point->object)) {
            function(point->object);
          }
        }
      }
    }
  }

  template <class Predicate, class InputIterator>
  void GetInBox(const BoundaryBox<Space, Dimension>& search_box, Predicate& condition, InputIterator input) {
    if (Divided()) {
      for (size_t i = 0; i < subtrees_.size(); ++i) {
        auto subtree_box = GetBoxByIndex(i);
        if (ValidSubTree(i) && search_box.Intersects(subtree_box)) {
          subtrees_[i]->GetInBox(search_box, condition, input);
        }
      }
    } else {
      if (search_box.Intersects(control_space_)) {
        for (auto& point : points_) {
          if (search_box.Contains(point->position) && condition(point->object)) {
            *input = point;
          }
        }
      }
    }
  }

 private:
  void CheckSubTree(size_t index) {
    if (subtrees_[index].get() == nullptr) {
      subtrees_[index] = std::make_unique<Tree>(GetBoxByIndex(index), depth_ - 1, max_capacity_);
    }
  }

  [[nodiscard]] bool ValidSubTree(size_t index) const {
    return subtrees_[index]->get() != nullptr && subtrees_[index]->size_ > 0;
  }

  [[nodiscard]] bool Divided() const { return size_ != points_.size(); }

  [[nodiscard]] bool Divisible() const { return size_ >= max_capacity_ && depth_ > 0; }

  size_t GetSubTreeIndex(const Vector<Space, Dimension>& position) const {
    size_t index = 0;
    auto midpoint = (control_space_.GetLeft() + control_space_.GetRight()) / 2;
    for (size_t i = 0; i < Dimension; ++i) {
      index += (1 << i) * (position[i] >= midpoint[i]);
    }
    return index;
  }

  BoundaryBox<Space, Dimension> GetBoxByIndex(size_t index) const {
    BoundaryBox<Space, Dimension> box(control_space_);
    for (size_t i = 0; i < Dimension; ++i) {
      if (index & (1 << i)) {
        box.GetLeft()[i] = (box.GetLeft()[i] + box.GetRight()[i]) / 2;
      } else {
        box.GetRight()[i] = (box.GetLeft()[i] + box.GetRight()[i]) / 2;
      }
    }
    return box;
  }

  void SubDivide() {
    for (auto& point : points_) {
      auto index = GetSubTreeIndex(point->position);
      CheckSubTree(index);
      subtrees_[index]->points_.push_back(point);
    }
    points_.clear();
  }

  void Unite() {
    for (size_t subtree_index = 0; subtree_index < subtrees_.size(); ++subtree_index) {
      if (ValidSubTree(subtree_index)) {
        subtrees_[subtree_index]->Unite();
        for (auto& iter : subtrees_[subtree_index]->points_) {
          points_.push_back(iter);
        }
        subtrees_[subtree_index]->points_.clear();
      }
    }
  }

  BoundaryBox<Space, Dimension> control_space_;
  size_t depth_ = DefaultDepth;
  size_t max_capacity_ = DefaultCapacity;
  std::list<iterator, IterAlloc> points_; /// TODO vector might be better
  std::array<std::unique_ptr<Tree>, 1 << Dimension> subtrees_;
  size_t size_ = 0;
};

#endif //GEOMETRY_COLLECTIONS_SPATIALTREE_H_
