// #define LOG_TAG  "IOpModeManager"
// #include <common/logger.h>

#include <unistd.h>
#include <memory>
#include "IOpModeManager.h"
#include "OpModeManagerImpl.h"

namespace OpModeManager {
    IOpModeManager* gOpModeService{};

    IOpModeManager* getOpModeManager()
    {
        if (!gOpModeService) {
            gOpModeService = new OpModeManagerImpl();
            int result;
            result = gOpModeService->connect();
            if (result) {
                // SLOGE("%s\n", "Unable to connect to service");
                delete gOpModeService;
                gOpModeService = nullptr;
            }
        }
        return gOpModeService;
    }

} //namespace OpModeManager
