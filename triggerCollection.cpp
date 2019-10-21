#include <iostream>
#include <functional>
#include <vector>
#include "triggerCollection.h"

using namespace std;

TriggerCollection::TriggerCollection(vector<Trigger> triggers) {
  _triggers = triggers;
}

void TriggerCollection::dispatchMessage(
  string topic, string message, function<void(string, string)> updateCallback
) {
  for(auto&& trigger: _triggers) {

    if (message == trigger.commandTopic) {
      updateCallback(trigger.stateTopic, message);
    }

    if (message == trigger.stateTopic) {
      trigger.value = message;
    }
  }
}

vector<string> TriggerCollection::topicsOfInterest() const {
  vector<string> topics;

  for(auto&& trigger: _triggers) {
    topics.push_back(trigger.stateTopic);
    topics.push_back(trigger.commandTopic);
  }

  return topics;
}
