#ifndef H_SCHEDULER_H
#define H_SCHEDULER_H
#include <functional>
#include <vector>
#include <set>
#include "resource.h"
#include "job.h"
class Scheduler {
public:
  //std::vector<Job::Ptr> jobs_;
  std::function<bool(const Resource::Ptr, const Resource::Ptr)> lambda_;
	std::set<Resource::Ptr, decltype(lambda_)> resources_;
  Scheduler() {
    lambda_ = [] (const Resource::Ptr a, const Resource::Ptr b) { if (a->capacity_ - a->used_ == b->capacity_ - b->used_) return a->id_ > b->id_;
										 return (a->capacity_ - a->used_) < (b->capacity_ - b->used_); }; //removing collisions by matching ID.
		resources_ = std::set<Resource::Ptr, decltype(lambda_)> (lambda_); 
	}
  void addResource(Resource::Ptr r);
/* {
		resources_.insert(r);
	}
*/
  void addResource(int id, int capacity);
/* {
		resources_.insert(std::move(Resource::create(id, capacity)));
  }
*/
  std::vector<Job::Ptr> scheduleJobs(const std::vector<Job::Ptr>& jobs);
};

#endif
