#pragma once

#include <string>

class Component {
 public:
  bool operator<(const Component &rhs) {
    return getClassID() < rhs.getClassID();
  }

  virtual std::string getClassID() const = 0;
};

#define CLASS_ID_BOILERPLATE  \
  static std::string classID; \
  virtual std::string getClassID() const override { return classID; }

class Drawable : public Component {
 public:
  void setGlyph(char g) { glyph = g; }

  char glyph;

  CLASS_ID_BOILERPLATE
};

class HasLocation : public Component {
 public:
  void linkToGlobal(const int &globalLocationVariable) {
    linkedGlobal = &globalLocationVariable;
  }

  const int *linkedGlobal{nullptr};

  CLASS_ID_BOILERPLATE
};
