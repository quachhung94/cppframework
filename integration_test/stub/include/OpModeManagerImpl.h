#if !defined(_OP_MODE_MANAGER_IMPL_H_)
#define _OP_MODE_MANAGER_IMPL_H_

// #include "EvCppWrapper.h"
#include "IOpModeManager.h"
#include "OpModeManagerTypes.h"
#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

// #include "OpModeManager.pb.h"
// #include "RpcProto.pb.h"

namespace OpModeManager {
    using namespace std;
    // using namespace EvCppWrapper;

    class OpModeManagerImpl : public IOpModeManager {
    public:
        static const uint8_t SERVICE_IP[10];
        static const uint32_t SIN_ADDR_LENGTH_MAX = 32;
        static const uint32_t DEFAULT_RPC_TIMEOUT = 100; // Milliseconds

    public:
        OpModeManagerImpl();
        virtual ~OpModeManagerImpl();

        virtual int32_t connect();
        virtual void    disconnect();

        virtual int32_t registerReceiver(std::shared_ptr<IOpModeReceiver>& receiver);
        virtual int32_t unregisterReceiver();
        
        virtual int32_t getOperationMode(OperationModeType* mode);
        virtual int32_t setOperationMode(OperationModeType mode);

        virtual int32_t setPostResult(PostResults post_result);
        virtual int32_t setActivatedStatus(ActivatedStatus status);
        virtual int32_t setEvConnectStatus(EvConnectStatus status);
        virtual int32_t setDiagRequest(DiagRequests request);
        virtual int32_t setLocalDfuRequest(DfuRequests request);
        virtual int32_t setOtaDfuRequest(DfuRequests request);
        virtual int32_t setEmergencyStatus(EmgStatus status);
        virtual int32_t setRebootRequest(RebootRequests request);

    // public:
        // static void onReadCallback(struct bufferevent* bev, void* args)
        // {
        //     reinterpret_cast<OpModeManagerImpl*>(args)->onRead(bev, args);
        // }
        // static void onWriteCallback(struct bufferevent* bev, void* args)
        // {
        //     reinterpret_cast<OpModeManagerImpl*>(args)->onWrite(bev, args);
        // }
        // static void onEventCallback(struct bufferevent* bev, short events, void* args)
        // {
        //     reinterpret_cast<OpModeManagerImpl*>(args)->onEvent(bev, events, args);
        // }

    private:
        bool isConnected() { return mConnected; }
        void loop();

#if 0
        void dispatch();
#endif

        // void onEvent(struct bufferevent* bev, short events, void* cbarg);
        // void onRead(struct bufferevent* bev, void* cbarg);
        // void onWrite(struct bufferevent* bev, void* cbarg);
        // int send(int cmd, const ::google::protobuf::Message* request, uint32_t timeout = DEFAULT_RPC_TIMEOUT);
        // int sendAsync(int cmd, const ::google::protobuf::Message* request);
        // void handleReceiveMessage(EvBuffer& buffer);

        void setModeAcquisitionResult(OperationModeType mode);
        OperationModeType getModeAcquisitionResult();
        bool isDataAvailable() { return mNewDataReceived; }

    public:
        static bool mNewDataReceived;
        static bool mConnected;

    private:
        std::shared_ptr<IOpModeReceiver> mReceiver;
        std::thread* mThread{};
        std::mutex mMutex;
        std::condition_variable mConnCondvar;
        std::condition_variable mCondVar;
        bool mRunning{};

        // std::unique_ptr<EvBaseLoop> mEvBase;
        // std::unique_ptr<EvBufferEvent> mEvBuff;
        // EvEvent mEvTimeout;

        OperationModeType mAcquiredMode;
    };

} // namespace OpModeManager
#endif // !defined(_OP_MODE_MANAGER_IMPL_H_)
