//
// Created by Artem Novikov on 06.08.2022.
//

#ifndef GEOMETRY_COLLECTIONS_DATANODE_H_
#define GEOMETRY_COLLECTIONS_DATANODE_H_

#include "Vector.h"

template <class Object, typename Space, size_t Dimension, class Alloc = std::allocator<Object>>
class SpatialTree;

template <class Object, typename Space, size_t Dimension, class Alloc = std::allocator<Object>>
class SpatialHashing;

template <class Object, typename Space, size_t Dimension>
struct PositionedData {
 public:
  PositionedData(const Object& object, const Vector<Space, Dimension>& position) : object(object), position_(position) {}
  PositionedData(Object&& object, const Vector<Space, Dimension>& position)
      : object(std::move(object)), position_(position) {}
  Object object;
  const Vector<Space, Dimension>& GetPosition() const { return position_; }
 private:
  template <class, typename , size_t, class>
  friend class SpatialTree;

  template <class, typename , size_t, class>
  friend class SpatialHashing;

  Vector<Space, Dimension> position_;
};

template <class Object, typename Space>
using PositionedData2 = PositionedData<Object, Space, 2>;

template <class Object> using PositionedData2f = PositionedData2<Object, float>;
template <class Object> using PositionedData2d = PositionedData2<Object, double>;
template <class Object> using PositionedData2i = PositionedData2<Object, int>;

template <class Object, typename Space>
using PositionedData3 = PositionedData<Object, Space, 3>;

template <class Object> using PositionedData3f = PositionedData3<Object, float>;
template <class Object> using PositionedData3d = PositionedData3<Object, double>;
template <class Object> using PositionedData3i = PositionedData3<Object, int>;

#endif //GEOMETRY_COLLECTIONS_DATANODE_H_
