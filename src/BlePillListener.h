#ifndef BlePillListener_H
#define BlePillListener_H
#include <Arduino.h>
#include <functional>

#include "Config.h"

#include "BleListener.h"

class PillHydrometerInfo: public BleHydrometerDevice{
public:
    PillHydrometerInfo(){}
    BleHydrometerDevice* duplicate(void){
        PillHydrometerInfo* info= new PillHydrometerInfo();

        info->gravity = this->gravity;
        info->temperature = this->temperature;
        info->rssi = this->rssi;
        info->temperature = this->temperature;
        info->accX = this->accX;
        info->accY = this->accY;
        info->accZ = this->accZ;
        info->battery = this->battery;
        info->macAddress=this->macAddress;
        info->rssi = this->rssi;
        return info;
    }
    float gravity;
    float temperature;
    uint16_t accX;
    uint16_t accY;
    uint16_t accZ;
    float battery;
};


typedef std::function<void(PillHydrometerInfo*)> PillDataHandler;


class PillListener:public BleDeviceListener {
public:
    PillListener(uint8_t mac[6]):_dataAvailableHandler(NULL),_mac(mac){}

    void listen(PillDataHandler onData);
    // callbacks
    bool identifyDevice(NimBLEAdvertisedDevice*);
    void setMac(uint8_t mac[6]){
            NimBLEAddress nmac(mac);
            _mac = nmac;
        }
protected:
    PillDataHandler _dataAvailableHandler;
    PillHydrometerInfo _info;
    NimBLEAddress _mac;
};

class PillScanner:public BleDeviceScanner {
public:
    PillScanner(){}
    // callbacks
    BleHydrometerDevice* checkDevice(NimBLEAdvertisedDevice*);
};

extern PillScanner pillScanner;
#endif