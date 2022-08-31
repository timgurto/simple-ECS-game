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

struct Drawable : public Component {
  CLASS_ID_BOILERPLATE

  char glyph;
  bool shouldDrawBehind{false};

  Drawable &drawBehind() {
    shouldDrawBehind = true;
    return *this;
  }
};

struct HasLocation : public Component {
  CLASS_ID_BOILERPLATE

  const int *linkedGlobal{nullptr};
  int location;

  int getLocation() {
    if (linkedGlobal) return *linkedGlobal;
    return location;
  }
};
