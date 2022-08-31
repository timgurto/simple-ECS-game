#include "Component.h"

bool Component::operator<(const Component &rhs) const {
  return getClassID() < rhs.getClassID();
}

std::string Drawable::classID = "drawable";
std::string HasLocation::classID = "hasLocation";
