#include "scheduler.h"
#include <iostream>
#include <queue> 

void Scheduler::addResource(Resource::Ptr r) {
    resources_.insert(r);
}

void Scheduler::addResource(int id, int capacity) {
	resources_.insert(std::move(Resource::create(id, capacity)));
}

std::vector<Job::Ptr> Scheduler::scheduleJobs(const std::vector<Job::Ptr>& jobs) {
  std::vector<Job::Ptr> schedule;
  auto cmp = [] (const Job::Ptr a, const Job::Ptr b) { return a->duration_ > b->duration_;};
  std::set<Job::Ptr, decltype(cmp)> priorityJobSet(cmp);
  auto outJobComp = [] (std::pair<int, Job::Ptr> a, const std::pair<int, Job::Ptr> b) {return a.second->completionTime_ > b.second->completionTime_ ;};
  std::priority_queue<std::pair<int, Job::Ptr>, std::vector<std::pair<int, Job::Ptr> >, decltype(outJobComp)> outJobQueue(outJobComp); 

  for (auto& x: jobs) {
    priorityJobSet.insert(x); 
  }
	std::cout << " TOTAL JOBS:" << priorityJobSet.size() << std::endl;
  std::cout << std::endl;
	std::cout << "Printing jobset sorted according to the duration" << std::endl;	
	std::cout << "resource required :duration" << std::endl;	
	for (auto x: priorityJobSet) {
		std::cout << x->resourceReq_ << ":" << x->duration_ <<  "    ";
	}
	  std::cout << std::endl;

  int currentTime = 0; //Initial time is 0;
	std::vector<Job::Ptr> jobsToRemoveFromInQueue;
	while (!priorityJobSet.empty()) {
		
		std::cout << " TOTAL REMAINING JOBS:" << priorityJobSet.size() << std::endl;
		for (auto j: jobsToRemoveFromInQueue) {
				 std::cout << j->resourceReq_ << std::endl;
				 priorityJobSet.erase(j); //cleanup any jobs that have completed.
		}

		jobsToRemoveFromInQueue.clear();
		// run the simulation, pop jobs from the outBound queue
		bool scheduledAtLeastOne = false;
		if (!outJobQueue.empty()) {
			currentTime = outJobQueue.top().second->completionTime_;
			std::cout << "new currentTime : " << currentTime << std::endl;
			std::cout << "currently running job count:" << outJobQueue.size() << std::endl;
      while (!outJobQueue.empty() && currentTime == outJobQueue.top().second->completionTime_) {

				schedule.push_back(outJobQueue.top().second);
				std::cout << "Job removed from machine ID:" << outJobQueue.top().first << std::endl;;
				for (auto machine: resources_) {
					if(machine->id_ == outJobQueue.top().first) {
						machine->used_ -= outJobQueue.top().second->resourceReq_;	
						std::cout << "machine with ID" <<  machine->id_ << " was restored:" << outJobQueue.top().second->resourceReq_ << " nodes." << std::endl;
					}
				}
				outJobQueue.pop();
			}
		}

		std::cout << "currently running job count:" << outJobQueue.size() << std::endl;
		for (auto inJob: priorityJobSet) { //pick the longest job
			for (auto resource : resources_) { //iterate resources which are presorted in the set.
				if (resource->getDiff() >= inJob->resourceReq_) { //if any machine can take the job
					scheduledAtLeastOne = true;
					resources_.erase(resource); //unlink from the set
					resource->used_ += inJob->resourceReq_; //update the working capacity.
          resources_.insert(resource); //re-insert.
  				inJob->completionTime_ = inJob->duration_ + currentTime; //update the completion time.
 					outJobQueue.emplace(resource->id_, inJob); //push the job inside the simulator queue.
					jobsToRemoveFromInQueue.push_back(inJob);
					break;
				}	
			}
		}

		if (outJobQueue.empty() && !scheduledAtLeastOne) {
			std::cout << "All jobs cannot be scheduled" << std::endl; 
			break;
		}
  }
  std::cout << "DONE" << std::endl;

	while(!outJobQueue.empty()) {
		schedule.push_back(outJobQueue.top().second);	
		currentTime = outJobQueue.top().second->completionTime_;
		outJobQueue.pop();
	}

	std::cout << "Total time taken" << currentTime << std::endl;
	return schedule;
  // Algorithm: 
  // #1 pick the longest job.
  // #2 schedule it on the minimum possible machine
  // #3 do #1 and #2 till not possible.
  // pop all jobs that were completed, give back the resources and try #3
  // again and again and again!
  // push the jobs done to a vector to keep track.
}
