#pragma once

#include <string>

class Component {
 public:
  bool operator<(const Component &rhs) {
    return getClassID() < rhs.getClassID();
  }

  virtual std::string getClassID() const = 0;
};

class Drawable : public Component {
 public:
  Drawable(char glyphArg) : glyph(glyphArg) {}

  char glyph;

  static std::string classID;
  virtual std::string getClassID() const override { return classID; }
};
