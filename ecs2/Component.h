#pragma once

struct Component {
  bool operator<(const Component &rhs) { return classID() < rhs.classID(); }

 private:
  virtual std::string classID() const = 0;
};

struct Drawable : public Component {
  Drawable(char glyphArg) : glyph(glyphArg) {}

  char glyph;

 private:
  virtual std::string classID() const override { return "drawable"; }
};
