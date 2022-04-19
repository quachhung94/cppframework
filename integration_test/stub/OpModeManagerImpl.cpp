#include "OpModeManagerImpl.h"
#include "IOpModeReceiver.h"
#include "OpModeManagerInternalTypes.h"
// #include "RpcProto.pb.h"
#include <map>
#include <mutex>
#include <stack>
#include <unistd.h>

#define OPS_MODE_SERVICE_PORT 9198

namespace OpModeManager {
using namespace std;
// using namespace RpcProto;
using namespace OpModeManager;

const uint8_t OpModeManagerImpl::SERVICE_IP[10] = "127.0.0.1";
bool OpModeManagerImpl::mNewDataReceived        = false;
bool OpModeManagerImpl::mConnected              = false;

OpModeManagerImpl::OpModeManagerImpl()
    : IOpModeManager(),
      // mEvBase(new EvBaseLoop()),
      // mEvBuff(new EvBufferEvent()),
      mAcquiredMode(POST_MODE)
{
}

OpModeManagerImpl::~OpModeManagerImpl() {}

int32_t OpModeManagerImpl::registerReceiver(shared_ptr<IOpModeReceiver>& receiver)
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::unregisterReceiver()
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::getOperationMode(OperationModeType* mode)
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::setOperationMode(OperationModeType mode)
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::setPostResult(PostResults post_result)
{
    int32_t result;
    return result;
}

int32_t OpModeManagerImpl::setActivatedStatus(ActivatedStatus status)
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::setEvConnectStatus(EvConnectStatus status)
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::setDiagRequest(DiagRequests request)
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::setLocalDfuRequest(DfuRequests request)
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::setOtaDfuRequest(DfuRequests request)
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::setEmergencyStatus(EmgStatus status)
{
    int32_t result = E_OK;
    return result;
}

int32_t OpModeManagerImpl::setRebootRequest(RebootRequests request)
{
    int32_t result = E_OK;
    return result;
}

void OpModeManagerImpl::loop() {}

// void OpModeManagerImpl::onEvent(struct bufferevent *bev, short events, void *cbarg) {
// }

// void OpModeManagerImpl::onRead(struct bufferevent *bev, void *cbarg) {
//     (void) cbarg;
// }

int32_t OpModeManagerImpl::connect()
{
    auto ret = E_OK;
    return ret;
}

void OpModeManagerImpl::disconnect()
{
    // mRunning = false;
    // mConnected = false;
    // mThread->join();
    // delete mThread;
    // mEvBuff->own(true);
    // mEvBuff->free();
}

// int32_t OpModeManagerImpl::send(int32_t cmd, const ::google::protobuf::Message *request, uint32_t timeout) {
//     auto result = E_OK;
//     return result;
// }

// int32_t OpModeManagerImpl::sendAsync(int32_t cmd, const ::google::protobuf::Message *request) {
//     return E_OK;
// }

// void OpModeManagerImpl::handleReceiveMessage(EvBuffer &buffer) {
// }

void OpModeManagerImpl::setModeAcquisitionResult(OperationModeType mode) { mAcquiredMode = mode; }

OperationModeType OpModeManagerImpl::getModeAcquisitionResult() { return mAcquiredMode; }

} // namespace OpModeManager
