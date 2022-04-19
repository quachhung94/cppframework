#if !defined(_I_OP_MODE_RECEIVER_H_)
#define _I_OP_MODE_RECEIVER_H_

#include "OpModeManagerTypes.h"
#include <memory>

namespace OpModeManager {
class IOpModeReceiver {
public:
    virtual ~IOpModeReceiver() {}
    virtual void onModeChanged(OperationModeType mode, OperationModeType prev) = 0;
    virtual void onRebootRequest(){};
    virtual void onStartDiag(){};
    virtual void onStartLocalDfu(){};
    virtual void onStartOtaDfu(){};
    virtual void onInactivated(){};
    virtual void onActivateSource(bool is_online) { (void)is_online; };
    virtual void onForceIdle(){};
};

} // namespace OpModeManager

#endif // !defined(_I_OP_MODE_RECEIVER_H_)
