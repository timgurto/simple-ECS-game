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

/* Example:

// Using macros:

    BEGIN_COMPONENT(Cartesian)
    int x;
    int y;
    END_COMPONENT(Cartesian)


// Fully expanded:

    struct Cartesian : public Component {
        static std::string classID;
        virtual std::string getClassID() const override { return classID; }

        int x;
        int y;
    };
    std::string Cartesian::classID = "Cartesian";
*/
