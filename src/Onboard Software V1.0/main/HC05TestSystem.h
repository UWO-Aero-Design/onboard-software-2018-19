#ifndef HC05_TEST_SYSTEM_H
#define HC05_TEST_SYSTEM_H

#include <stdint.h>
#include "Bluetooth.h"
#include "System.h"

class HC05BluetoothTestSystem : public System{
private:
  HC05Bluetooth *bluetooth;
protected:
public:
  HC05BluetoothTestSystem();
  ~HC05BluetoothTestSystem();

  void initSystem();
  void updateSystem();
};

#endif // HC05_TEST_SYSTEM_H