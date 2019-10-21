#include "trigger.h"

using namespace std;

Trigger::Trigger(
  string stateTopic,
  string commandTopic,
  string initialState
) {
  this->stateTopic = stateTopic;
  this->commandTopic = commandTopic;
  this->value = initialState;
}
