#include <vector>
#include <functional>
#include "./trigger.h"

using namespace std;

class TriggerCollection {
  public:
    TriggerCollection(vector<Trigger>);

    void dispatchMessage(
      string,
      string,
      function<void(string, string)>
    );

    vector<string> topicsOfInterest() const;

  private:
    vector<Trigger> _triggers;
};
