#ifndef HC05_TEST_SYSTEM_H
#define HC05_TEST_SYSTEM_H

#include <stdint.h>
#include "HC05.h"
#include "System.h"

class HC05BluetoothTestSystem : public System{
private:
  HC05 *bluetooth;
protected:
public:
  HC05BluetoothTestSystem();
  ~HC05BluetoothTestSystem();

  void initSystem();
  void updateSystem();
};

#endif // HC05_TEST_SYSTEM_H