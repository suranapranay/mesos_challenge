#include <memory>
#ifndef JOB_H
#define JOB_H


class Job {
public:
  typedef std::shared_ptr<Job> Ptr;
	int duration_;
  int resourceReq_;
  Job(int duration, int resourceReq): duration_(duration), resourceReq_(resourceReq) {};
  static std::shared_ptr<Job> create(int duration, int resourceReq) { return std::make_shared<Job>(duration, resourceReq); }
};

#endif
