#include <iostream>
//#include "mesos.h"
#include "scheduler.h"

int main () {
	//demo()

	// Consider a schedule with 2 Machines, (1, 5) and (2, 5);
	// consider 3 Jobs, (5, 3), (8,3), (100, 2)  where 5, 8, 100 are the DURATIONS, and 3, 3, 2 are the resource requirements.
	// With FCFS, Jobs with duration 5 and 8 will be scheduled first and Job with duration 100 will start at T = 5 (after job with duration 5 is completed).
	// However, prioritizing Machines with highest duration makes more sense as we can parallelize more.
  // Thus our scheduler picks Duration 100 job, and then both Job 5 and 8 run in parallel. Thus taking a total time of 100.
  Scheduler f;
  f.addResource(1, 5);
  f.addResource(2, 5);
	std::cout << "Testing that resources are ordered in minimum order" << std::endl;
	std::cout << "ID:Capacity" << std::endl;
  for (auto& x: f.resources_) std::cout << x->id_ << ":" << x->capacity_;
	std::cout << std::endl;
  std::vector<Job::Ptr> jobs;
  jobs.push_back(Job::create(5, 3, 1));
  jobs.push_back(Job::create(8 , 3, 2));
  jobs.push_back(Job::create(100 ,2 , 3));
  auto schedule1 = f.scheduleJobs(jobs);
	for (auto x : schedule1) std::cout << "ID:" << x->id_ << " " << "Duration" << x->duration_ << "resource:" << x->resourceReq_ << "Completion time:" << x->completionTime_ << std::endl;
  return 0;
}

