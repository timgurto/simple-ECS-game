#pragma once

#include <string>

struct Component {
 public:
  bool operator<(const Component &rhs) const;

  virtual std::string getClassID() const = 0;
};

#define CLASS_ID_BOILERPLATE  \
  static std::string classID; \
  virtual std::string getClassID() const override { return classID; }
