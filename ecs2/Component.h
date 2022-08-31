#pragma once

#include <string>

struct Component {
 public:
  bool operator<(const Component &rhs) {
    return getClassID() < rhs.getClassID();
  }

  virtual std::string getClassID() const = 0;
};

#define CLASS_ID_BOILERPLATE  \
  static std::string classID; \
  virtual std::string getClassID() const override { return classID; }

struct Drawable : public Component {
  CLASS_ID_BOILERPLATE

  void setGlyph(char g) { glyph = g; }

  char glyph;
};

struct HasLocation : public Component {
  CLASS_ID_BOILERPLATE

  void linkToGlobal(const int &globalLocationVariable) {
    linkedGlobal = &globalLocationVariable;
  }

  const int *linkedGlobal{nullptr};
};
