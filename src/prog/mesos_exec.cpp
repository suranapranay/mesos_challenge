#include <iostream>
#include "mesos.h"
#include "scheduler.h"

int main () {
	demo();
  Scheduler f;
  f.addResource(1, 100);
  f.addResource(2, 88);
  f.addResource(3, 188);
  for (auto& x: f.resources_) std::cout << x->id_ << std::endl;
  return 0;
}

