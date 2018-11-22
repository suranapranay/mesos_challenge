#include <memory>
#ifndef JOB_H
#define JOB_H


class Job {
public:
  typedef std::shared_ptr<Job> Ptr;
	int duration_;
  int resourceReq_;
	int completionTime_ = 0;
  int id_;
  Job(int duration, int resourceReq, int id): duration_(duration), resourceReq_(resourceReq), id_(id) {}
  static std::shared_ptr<Job> create(int duration, int resourceReq, int id) { return std::make_shared<Job>(duration, resourceReq, id); }
};

#endif
