#include <iostream>
//#include "mesos.h"
#include "scheduler.h"

int main () {
	//demo();
  Scheduler f;
  f.addResource(1, 100);
  f.addResource(2, 88);
  f.addResource(3, 188);
	std::cout << "Testing that resources are ordered in minimum order" << std::endl;
	std::cout << "ID:Capacity" << std::endl;
  for (auto& x: f.resources_) std::cout << x->id_ << ":" << x->capacity_;
	std::cout << std::endl;
  std::vector<Job::Ptr> jobs;
  jobs.push_back(Job::create(10, 2, 1));
  jobs.push_back(Job::create(8 , 9, 2));
  jobs.push_back(Job::create(100 , 9, 3));
  auto schedule1 = f.scheduleJobs(jobs);
	for (auto x : schedule1) std::cout << "ID:" << x->id_ << " " << "Duration" << x->duration_ << "resource:" << x->resourceReq_ << "Completion time:" << x->completionTime_ << std::endl;
  return 0;
}

