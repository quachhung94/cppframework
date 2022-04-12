#include "server.h"
// #include "spdlog/spdlog.h"

namespace S {
Demo::Demo(const std::shared_ptr<IfRuntime>& runtime, const std::string &ipv6_multicast, uint16_t port, const std::string& _ipv6IF)
{
  std::cout << "Demo Initial!!" << std::endl;
  this->ipv6IF = _ipv6IF;
  // get CppCommon::Asio::Service
  this->_pRunTime = runtime;
  this->_ptrService = this->_pRunTime->getService();
  // get the working io_service(bound to another thread) for queue operation
  this->_ptrIOService = this->_ptrService->GetAsioService();

  this->_pSSLContextIf = std::make_shared<CppServer::Asio::SSLContext>(asio::ssl::context::tlsv12);
  this->_pSSLContextIf->set_password_callback([](size_t max_length, asio::ssl::context::password_purpose purpose) -> std::string { return "qwerty"; });
  this->_pSSLContextIf->use_certificate_chain_file("tools/certificates/server.pem");
  this->_pSSLContextIf->use_private_key_file("tools/certificates/server.pem", asio::ssl::context::pem);
  this->_pSSLContextIf->use_tmp_dh_file("tools/certificates/dh4096.pem");

  // Create TCP Server IF
  this->_pTLSServerIf = std::make_shared<TLSServerAdapter>(this->_ptrService, this->_pSSLContextIf, ipv6_multicast, port);
  std::cout << "Demo Initial DONE!!"<< std::endl;
}

Demo::~Demo()
{
    this->_pTLSServerIf.reset();
}

bool Demo::start()
{
  std::cout << "Demo Start" << std::endl;
  auto self(this->shared_from_this());
    // create TCP handler object
  this->_onTLSConnect = std::make_shared<onTLSEvent>(en_tlsServerAdapterCallbackType_CONNECT, self);
  this->_onTLSDisconnect = std::make_shared<onTLSEvent>(en_tlsServerAdapterCallbackType_DISCONNECT, self);
  this->_onTLSEmpty = std::make_shared<onTLSEvent>(en_tlsServerAdapterCallbackType_EMPTY, self);
  this->_onTLSReceive = std::make_shared<onTLSEvent>(en_tlsServerAdapterCallbackType_RECEIVE, self);
  this->_onTLSSent = std::make_shared<onTLSEvent>(en_tlsServerAdapterCallbackType_SENT, self);
  this->_onTLSError = std::make_shared<onTLSEvent>(en_tlsServerAdapterCallbackType_ERROR, self);
  // add TCP handler object to TCP interface
  this->_pTLSServerIf->setEventCallBack(this->_onTLSConnect);
  this->_pTLSServerIf->setEventCallBack(this->_onTLSDisconnect);
  this->_pTLSServerIf->setEventCallBack(this->_onTLSEmpty);
  this->_pTLSServerIf->setEventCallBack(this->_onTLSReceive);
  this->_pTLSServerIf->setEventCallBack(this->_onTLSSent);
  this->_pTLSServerIf->setEventCallBack(this->_onTLSError);


  this->_pTLSServerIf->start();
  std::cout << "Demo Start Success" << std::endl;

  // Endless loop
  // this->_ptrIOService->run();

  return true;
}


bool Demo::stop()
{
  (void)this->_pTLSServerIf->disconnectAll();
  this->_pTLSServerIf->stop();
  std::cout << "[STC]: Logical link leave, stop TCP, UDP" << std::endl;
  return true;
}

// event for connect/disconnect TCP
void onTLSEvent::operator()() {
//   std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_TCP);
  switch (this->type){
    case en_tlsServerAdapterCallbackType_CONNECT: {
      // push event to event queue
    //   this->parent->_pTLSServerIf->IsStarted();
      std::cout << "en_tlsServerAdapterCallbackType_CONNECT"<< std::endl;
    //   responseEvent->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();
    //   responseEvent->TcpControlRes->result.portStatus.closed = !(this->parent->_pTCPIf->IsConnected());
    //   responseEvent->TcpControlRes->result.portNumber.intValue = this->parent->_pTCPIf->port();
    //   responseEvent->TcpControlRes->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_connectPort;
    //   responseEvent->TcpControlRes->ack = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success;
    //   this->parent->pt_V2G_TCP_TLS_ALM_SECC_Port->setEvent(responseEvent);
    //   Logging::debug(LogComponent_ENABLE, fmt::format("[STC]: SUT TCP {0} - {1} connected",this->parent->_pTCPIf->address(), this->parent->_pTCPIf->port()));
      break;
    }
    case en_tlsServerAdapterCallbackType_DISCONNECT: {
    //   responseEvent->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();
    //   responseEvent->TcpControlRes->result.portStatus.closed = !(this->parent->_pTCPIf->IsConnected());
    //   responseEvent->TcpControlRes->result.portNumber.intValue = this->parent->_pTCPIf->port();
    //   responseEvent->TcpControlRes->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort;
    //   responseEvent->TcpControlRes->ack = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success;
    //   this->parent->pt_V2G_TCP_TLS_ALM_SECC_Port->setEvent(responseEvent);
    //   Logging::debug(LogComponent_ENABLE, fmt::format("[STC]: SUT TCP {0} - {1} disconnected",this->parent->_pTCPIf->address(), this->parent->_pTCPIf->port()));
        std::cout << "en_tlsServerAdapterCallbackType_DISCONNECT"<< std::endl;
      break;
    }
    case en_tlsServerAdapterCallbackType_EMPTY: {
      std::cout << "Empty event TCP"<< std::endl;
      break;
    }
    default:
      break;
  }
}

// TCP receive event receive handler
void onTLSEvent::operator()(const void *buffer, size_t size) {
//   std::shared_ptr<V2gTpMessage> recMsg = std::make_shared<V2gTpMessage>();
  // push data to recMsg
//   recMsg->setMessage((const char*)buffer, size);
  // update to port queue
//   this->parent->pt_V2G_TCP_TLS_ALM_SECC_Port->setMsg(recMsg);
  std::cout << "[STC]: TCP receive event receive handler"<< std::endl;
}

// TCP interface sent event handler
void onTLSEvent::operator()(size_t sent, size_t pending) {
//   std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_TCP);
    std::cout << "[STC]: TCP interface sent event handler"<< std::endl;
}

// TCP interface error event handler
void onTLSEvent::operator()(int error, const std::string& category, const std::string& message) {
//   std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_TCP);
  // process tcp error
  // connected error/ disconnected error/ send error/ receive error/ connection abort ?
  std::cout << "[STC]: SUT TCP Error {0} - {1} disconnected " << category << " " << message<< std::endl;
}
}