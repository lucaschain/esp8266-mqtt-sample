#include <iostream>

using namespace std;

class Trigger {
  public:
    Trigger(string, string, string);

    string stateTopic;
    string commandTopic;
    string value;
};
