#include "HTTPServerAdapter.h"
#include "spdlog/spdlog.h"


// void TCPServerAdapter::onConnected(std::shared_ptr<CppServer::Asio::TCPSession>& session)
// {
//   SPDLOG_DEBUG("[SUT_IF][ISO15118][TCP]: connected {0}-{1}",this->endpoint().address().to_string(), this->endpoint().port());
//   SPDLOG_DEBUG("[SUT_IF][ISO15118][TCP]: start listening on {0} {1}", this->address(), this->port());
//   if (this->_onEventHandler[en_tcpServerAdapterCallbackType_CONNECT] != nullptr)
//     (*this->_onEventHandler[en_tcpServerAdapterCallbackType_CONNECT])();
// }

// void TCPServerAdapter::onDisconnected(std::shared_ptr<CppServer::Asio::TCPSession>& session)
// {
//     SPDLOG_DEBUG("[SUT_IF][ISO15118][TCP]: Id {} disconnect");
//   if (this->_onEventHandler[en_tcpServerAdapterCallbackType_DISCONNECT] != nullptr)
//     (*this->_onEventHandler[en_tcpServerAdapterCallbackType_DISCONNECT])();
// }

void HTTPServerAdapter::onError(int error, const std::string& category, const std::string& message)
{
  SPDLOG_DEBUG("[SUT_IF][ISO15118][TCP]: on error {0}, {1}, {2}", error, category , message);
  // if (this->_onEventHandler[en_tcpServerAdapterCallbackType_ERROR] != nullptr)
  //   (*this->_onEventHandler[en_tcpServerAdapterCallbackType_ERROR])(error, category, message);
}

// void TCPServerAdapter::onReceived(std::shared_ptr<CppServer::Asio::TCPSession>& session, const void* buffer, size_t size)
// {
//     SPDLOG_DEBUG("[SUT_IF][ISO15118][TCP]: receive: {}", (char*)buffer);
  
//   if (this->_onEventHandler[en_tcpServerAdapterCallbackType_RECEIVE] != nullptr)
//     (*this->_onEventHandler[en_tcpServerAdapterCallbackType_RECEIVE])(buffer, size);
// }

void HTTPServerAdapter::setEventCallBack(const std::shared_ptr<onHTTPServerAdapterEventType>& eventHandler)
{
  this->_onEventHandler[eventHandler->type] = eventHandler;
}

// void TCPServerAdapterSession::onConnected()
// {
//   SPDLOG_INFO("TCP session with Id {} CONNECTED", id().string());
// }

// void TCPServerAdapterSession::onDisconnected()
// {
//   SPDLOG_INFO("Chat TCP session with Id {} disconnected!", id().string());
// }

// void TCPServerAdapterSession::onSent(size_t sent, size_t pending)
// {
//   SPDLOG_INFO("Sent: {} bytes", sent);
// }

// void TCPServerAdapterSession::onReceived(const void* buffer, size_t size)
// {
//   std::string message((const char*)buffer, size);
//   // SPDLOG_INFO("Incoming: {}", message);
//   std::string res("This is RESPONSE from SERVER");

//   // Multicast message to all connected sessions
//   // server()->Multicast(message);

//   // If the buffer starts with '!' the disconnect the current session
//   // if (message == "!")
//       // Disconnect();
  
//   SendAsync(res);
  
// }

// void TCPServerAdapterSession::onError(int error, const std::string& category, const std::string& message)
// {
//     SPDLOG_DEBUG("[SUT_IF][ISO15118][TCP]: Chat TCP session on error {0}, {1}, {2}", error, category , message);
// }
