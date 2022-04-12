#include "IfRuntime.h"
#include <thread>
#include "system/cpu.h"
#include "spdlog/spdlog.h"
// handle creation asio io context for SUT Interface runtime

// post, dispatch, defer function object api
IfRuntime::IfRuntime() {
  // get number of available hw thread
  auto numthread = CppCommon::CPU::PhysicalCores();
  if (numthread >= 0) {
    // create Service with threads num and enable thread pool
    this->_service = std::make_shared<CppServer::Asio::Service>();
    if (this->_service->Start()){
      SPDLOG_INFO("[SUT_IF][RUNTIME]: Service started!!!!");
    }
  }
}

IfRuntime::~IfRuntime() {
  this->_service->Stop();
  while(this->_service->IsStarted()){}
}

std::shared_ptr<CppServer::Asio::Service> IfRuntime::getService() {
  return this->_service;
}
