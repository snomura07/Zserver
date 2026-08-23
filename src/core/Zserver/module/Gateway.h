#ifndef INCLUDED_GATEWAY
#define INCLUDED_GATEWAY
#include <string>
#include <vector>
#include <MasterConfig/MasterConfig.h>
#include "Router.h"
#include "../controller/GpioController.h"
#include "../controller/CameraController.h"
#include "../controller/HelloController.h"
#include "../controller/ConfigController.h"

class Gateway
{
public:
    Gateway();
    ~Gateway();
    std::string routeRequest(
        std::string mainCommand,
        std::vector<int> optValues,
        std::vector<std::string> optStrings
    );

private:
    Router router;
    GpioController gpioController;
    CameraController cameraController;
    HelloController helloController;
    ConfigController configController;
    MasterConfig masterConf;
};

#endif
