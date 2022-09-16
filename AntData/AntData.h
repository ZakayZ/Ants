//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_ANTDATA_ANTDATA_H_
#define ANTS_ANTDATA_ANTDATA_H_

#include <typeinfo>

struct AntData {
  explicit AntData(size_t colony_index) : colony_index(colony_index) {}
  size_t colony_index;
  /// TODO state and colony and type
};

#endif //ANTS_ANTDATA_ANTDATA_H_
