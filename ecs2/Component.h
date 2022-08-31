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
  void setGlyph(char g) { glyph = g; }

  char glyph;

  static std::string classID;
  virtual std::string getClassID() const override { return classID; }
};

class HasLocation : public Component {
 public:
  void linkToGlobal(const int &globalLocationVariable) {
    linkedGlobal = &globalLocationVariable;
  }

  const int *linkedGlobal{nullptr};

  static std::string classID;
  virtual std::string getClassID() const override { return classID; }
};
