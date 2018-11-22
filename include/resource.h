#ifndef H_RESOURCE_H 
#define H_RESOURCE_H 


class Resource {
public:
  typedef std::shared_ptr<Resource> Ptr;
	int id_;
  int capacity_;
  int used_;
  Resource(int id, int capacity): id_(id), capacity_(capacity), used_(0) {}
  static std::shared_ptr<Resource> create(int id, int capacity) { return std::make_shared<Resource>(id, capacity); }
};

#endif
