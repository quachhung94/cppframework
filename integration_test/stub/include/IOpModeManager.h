#if !defined(_I_OP_MODE_MANAGER_H_)
#define _I_OP_MODE_MANAGER_H_

#include "IOpModeReceiver.h"
#include "OpModeManagerTypes.h"
#include <memory>
#include <stdint.h>

namespace OpModeManager {
    class IOpModeManager {
    public:
        IOpModeManager() {}
        virtual ~IOpModeManager() {}

        virtual int32_t connect() = 0;
        virtual void    disconnect() = 0;

        virtual int32_t registerReceiver(std::shared_ptr<IOpModeReceiver>& receiver) = 0;
        virtual int32_t unregisterReceiver() = 0;

        virtual int32_t getOperationMode(OperationModeType* mode) = 0;
        virtual int32_t setOperationMode(OperationModeType mode) = 0;

        virtual int32_t setPostResult(PostResults post_result) = 0;
        virtual int32_t setActivatedStatus(ActivatedStatus status) = 0;
        virtual int32_t setEvConnectStatus(EvConnectStatus status) = 0;
        virtual int32_t setDiagRequest(DiagRequests request) = 0;
        virtual int32_t setLocalDfuRequest(DfuRequests request) = 0;
        virtual int32_t setOtaDfuRequest(DfuRequests request) = 0;
        virtual int32_t setEmergencyStatus(EmgStatus status) = 0;
        virtual int32_t setRebootRequest(RebootRequests request) = 0;
    };

    IOpModeManager* getOpModeManager();

} // namespace OpModeManager

#endif // !defined(_I_OP_MODE_MANAGER_H_)
