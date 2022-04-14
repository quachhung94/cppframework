#ifndef _HTTPSERVERADAPTER_H_
#define _HTTPSERVERADAPTER_H_

#include "server/http/http_server.h"
#include "boost/function.hpp"
#include "spdlog/spdlog.h"
#include "utility/singleton.h"
#include "string/string_utils.h"
#include <iostream>
#include <map>
#include <mutex>

class Cache : public CppCommon::Singleton<Cache>
{
   friend CppCommon::Singleton<Cache>;

public:
    std::string GetAllCache()
    {
        std::scoped_lock locker(_cache_lock);
        std::string result;
        result += "[\n";
        for (const auto& item : _cache)
        {
            result += "  {\n";
            result += "    \"key\": \"" + item.first + "\",\n";
            result += "    \"value\": \"" + item.second + "\",\n";
            result += "  },\n";
        }
        result += "]\n";
        return result;
    }

    bool GetCacheValue(std::string_view key, std::string& value)
    {
        std::scoped_lock locker(_cache_lock);
        auto it = _cache.find(key);
        if (it != _cache.end())
        {
            value = it->second;
            return true;
        }
        else
            return false;
    }

    void PutCacheValue(std::string_view key, std::string_view value)
    {
        std::scoped_lock locker(_cache_lock);
        auto it = _cache.emplace(key, value);
        if (!it.second)
            it.first->second = value;
    }

    bool DeleteCacheValue(std::string_view key, std::string& value)
    {
        std::scoped_lock locker(_cache_lock);
        auto it = _cache.find(key);
        if (it != _cache.end())
        {
            value = it->second;
            _cache.erase(it);
            return true;
        }
        else
            return false;
    }

private:
    std::mutex _cache_lock;
    std::map<std::string, std::string, std::less<>> _cache;
};

typedef enum {
  en_httpServerAdapterCallbackType_CONNECT,
  en_httpServerAdapterCallbackType_DISCONNECT,
  en_httpServerAdapterCallbackType_RECEIVE,
  en_httpServerAdapterCallbackType_SENT,
  en_httpServerAdapterCallbackType_EMPTY,
  en_httpServerAdapterCallbackType_ERROR,
  en_httpServerAdapterCallbackType_NUM
} en_httpServerAdapterCallbackType;

class onHTTPServerAdapterEventType {
public:
  onHTTPServerAdapterEventType(en_httpServerAdapterCallbackType _type){
    type = _type;
  }
  onHTTPServerAdapterEventType (onHTTPServerAdapterEventType && ) = default;
  onHTTPServerAdapterEventType (const onHTTPServerAdapterEventType & ) = default;
  ~onHTTPServerAdapterEventType(){}
  void setType(en_httpServerAdapterCallbackType _type) {type = _type;}
  virtual void operator() () {}
  virtual void operator() (const void *buffer, size_t size) {}
  virtual void operator() (size_t sent, size_t pending) {}
  virtual void operator() (int error, const std::string& category, const std::string& message) {}
  onHTTPServerAdapterEventType & operator= ( const onHTTPServerAdapterEventType & ) = default;
  onHTTPServerAdapterEventType & operator= ( onHTTPServerAdapterEventType && ) = default;
  en_httpServerAdapterCallbackType type;
};

class HTTPServerAdapterSession: public CppServer::HTTP::HTTPSession
{
public:
  using CppServer::HTTP::HTTPSession::HTTPSession;

protected:
  void onReceivedRequest(const CppServer::HTTP::HTTPRequest& request) override
  {
      // Show HTTP request content
      std::cout << std::endl << request;

      // Process HTTP request methods
      if (request.method() == "HEAD")
          SendResponseAsync(response().MakeHeadResponse());
      else if (request.method() == "GET")
      {
          std::string key(request.url());
          std::string value;

          // Decode the key value
          key = CppCommon::Encoding::URLDecode(key);
          CppCommon::StringUtils::ReplaceFirst(key, "/api/cache", "");
          CppCommon::StringUtils::ReplaceFirst(key, "?key=", "");

          if (key.empty())
          {
              // Response with all cache values
              SendResponseAsync(response().MakeGetResponse(Cache::GetInstance().GetAllCache(), "application/json; charset=UTF-8"));
          }
          // Get the cache value by the given key
          else if (Cache::GetInstance().GetCacheValue(key, value))
          {
              // Response with the cache value
              SendResponseAsync(response().MakeGetResponse(value));
          }
          else
              SendResponseAsync(response().MakeErrorResponse(404, "Required cache value was not found for the key: " + key));
      }
      else if ((request.method() == "POST") || (request.method() == "PUT"))
      {
          std::string key(request.url());
          std::string value(request.body());

          // Decode the key value
          key = CppCommon::Encoding::URLDecode(key);
          CppCommon::StringUtils::ReplaceFirst(key, "/api/cache", "");
          CppCommon::StringUtils::ReplaceFirst(key, "?key=", "");

          // Put the cache value
          Cache::GetInstance().PutCacheValue(key, value);

          // Response with the cache value
          SendResponseAsync(response().MakeOKResponse());
      }
      else if (request.method() == "DELETE")
      {
          std::string key(request.url());
          std::string value;

          // Decode the key value
          key = CppCommon::Encoding::URLDecode(key);
          CppCommon::StringUtils::ReplaceFirst(key, "/api/cache", "");
          CppCommon::StringUtils::ReplaceFirst(key, "?key=", "");

          // Delete the cache value
          if (Cache::GetInstance().DeleteCacheValue(key, value))
          {
              // Response with the cache value
              SendResponseAsync(response().MakeGetResponse(value));
          }
          else
              SendResponseAsync(response().MakeErrorResponse(404, "Deleted cache value was not found for the key: " + key));
      }
      else if (request.method() == "OPTIONS")
          SendResponseAsync(response().MakeOptionsResponse());
      else if (request.method() == "TRACE")
          SendResponseAsync(response().MakeTraceResponse(request.cache()));
      else
          SendResponseAsync(response().MakeErrorResponse("Unsupported HTTP method: " + std::string(request.method())));
  }

  void onReceivedRequestError(const CppServer::HTTP::HTTPRequest& request, const std::string& error) override
  {
      std::cout << "Request error: " << error << std::endl;
  }

  void onError(int error, const std::string& category, const std::string& message) override
  {
      std::cout << "HTTP session caught an error with code " << error << " and category '" << category << "': " << message << std::endl;
  }
};

class HTTPServerAdapter : public CppServer::HTTP::HTTPServer
{
private:
  std::shared_ptr<onHTTPServerAdapterEventType> _onEventHandler[en_httpServerAdapterCallbackType_NUM];
public:
  using CppServer::HTTP::HTTPServer::HTTPServer;

  // bool start();
  // bool stop();
  // bool restart();
  // bool disconnectAll();
  // bool multicast(std::string_view text);
  void setEventCallBack(const std::shared_ptr<onHTTPServerAdapterEventType>& eventHandler);
  
protected:
  std::shared_ptr<CppServer::Asio::TCPSession> CreateSession(const std::shared_ptr<CppServer::Asio::TCPServer>& server) override
  {
      return std::make_shared<HTTPServerAdapterSession>(std::dynamic_pointer_cast<CppServer::HTTP::HTTPServer>(server));
  }
  // void onConnected(std::shared_ptr<CppServer::Asio::TCPSession>& session) override;
  // void onDisconnected(std::shared_ptr<CppServer::Asio::TCPSession>& session) override;
  void onError(int error, const std::string& category, const std::string& message) override;
  // void onReceived(std::shared_ptr<CppServer::Asio::TCPSession>& session, const void* buffer, size_t size) override;
};

#endif