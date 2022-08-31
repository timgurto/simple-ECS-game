#include "Component.h"

bool Component::operator<(const Component &rhs) const {
  return getClassID() < rhs.getClassID();
}
