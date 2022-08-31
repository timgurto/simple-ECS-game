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

  int location;
};

struct KeyboardControllable : public Component {
  CLASS_ID_BOILERPLATE

  int leftKey;
  int rightKey;

  KeyboardControllable &setLeftKey(int k) {
    leftKey = k;
    return *this;
  }
  KeyboardControllable &setRightKey(int k) {
    rightKey = k;
    return *this;
  }
};
