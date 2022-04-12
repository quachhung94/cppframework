#ifndef _IFRUNTIME_H_
#define _IFRUNTIME_H_

#include "server/asio/service.h"

class IfRuntime
{
private:
  std::shared_ptr<CppServer::Asio::Service> _service;
public:
  IfRuntime();
  IfRuntime(const IfRuntime&) = delete;
  IfRuntime(IfRuntime&&) = delete;
  ~IfRuntime();

  IfRuntime& operator=(const IfRuntime&) = delete;
  IfRuntime& operator=(IfRuntime&&) = delete;

  std::shared_ptr<CppServer::Asio::Service> getService();
};

#endif