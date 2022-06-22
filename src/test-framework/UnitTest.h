#include <string>
#include <vector>

using std::string, std::vector;

class Assertion {

protected:
  typedef enum { Pending, Passed, Failed } Outcome;
  Outcome state = Pending;

  void pass() { state = Passed; }
  void fail(const string &reason = "No reason given") {
    state = Failed;
    // TODO: Use the reason
  }

public:
  bool hasPassed() { return state == Passed; }
  bool hasFailed() { return state == Failed; }
};

template <typename Actual> class Expectation : public Assertion {
  Actual actual;

  Expectation(Actual actual) : actual(actual) {}

public:
  Expectation &toBe(Actual expectedValue) {
    if (actual == expectedValue)
      pass();
    else
      fail();
    return *this;
  }
};

class UnitTest {
  vector<Assertion *> assertions;
  UnitTest() {}
  ~UnitTest() {
    for (auto assertion : assertions)
      delete assertion;
  }

  template <typename Actual> Expectation<Actual> expect(Actual &actual) {
    Expectation<Actual> *expectation = new Expectation(actual);
    assertions.push_back(expectation);
    return expectation;
  }

  bool hasPassed() {
    for (auto assertion : assertions) {
      if (assertion->hasPassed())
        continue;
      else
        return false;
    }
    // Otherwise
    return true;
  }
}
