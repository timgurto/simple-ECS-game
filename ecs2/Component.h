#pragma once

#include <string>

struct Component {
 public:
  bool operator<(const Component &rhs) const;

  virtual std::string getClassID() const = 0;
};

#define BEGIN_COMPONENT(ClassName)      \
  struct ClassName : public Component { \
    static std::string classID;         \
    virtual std::string getClassID() const override { return classID; }

#define END_COMPONENT(ClassName) \
  }                              \
  ;                              \
  std::string ClassName::classID = #ClassName;
