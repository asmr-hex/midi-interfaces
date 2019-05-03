#ifndef GLOVE_H_
#define GLOVE_H_

#include <map>
#include "sensors/flex.h"
#include "sensors/orientation.h"


class Glove {
public:
  Glove();

private:
  std::map<std::string, sensor::Flex> fingers;
  sensor::Orientation orientation;
};

#endif
