#include "Gateway.h"
#include "Router.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <str.hpp>
#include <print.hpp>

Gateway::Gateway()
{
    masterConf.read();
}

Gateway::~Gateway(){}

std::string Gateway::routeRequest(
    std::string mainCommand,
    std::vector<int> optValues,
    std::vector<std::string> optStrings)
{
    std::string rmsg = "";

    router.setRequestPath(mainCommand);
    if(router.get("test")){
        rmsg = "Zserver running now!";
    }
    else if(router.get("hello")){
        rmsg = helloController.sayHello();
    }
    else if(router.get("config/get", optStrings, true)){
        rmsg = configController.getConfig(optStrings.front());
    }
    else if(router.get("config/list/get")){
        rmsg = configController.getList();
    }
    else if(router.get("gpio/chmode/input", optValues, true)){
        int pinNo = optValues.front();
        gpioController.chModeInput(pinNo);
    }
    else if(router.get("gpio/chmode/output", optValues, true)){
        int pinNo = optValues.front();
        gpioController.chModeOutput(pinNo);
    }
    else if(router.get("gpio/setio/high", optValues, true)){
        int pinNo = optValues.front();
        gpioController.setHigh(pinNo);
    }
    else if(router.get("gpio/setio/low", optValues, true)){
        int pinNo = optValues.front();
        gpioController.setLow(pinNo);
    }
    else if(router.get("camera/capture/save", optValues, true)){
        std::string imagePath = masterConf.imagePath + "ttt.png";
        cameraController.save(imagePath);
    }


    else{
        rmsg = "404 Not Found... > " + mainCommand;
    }

    return rmsg;
}
