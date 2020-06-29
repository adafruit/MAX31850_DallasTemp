/*!
 * @file DallasTemperature.h
 */
#ifndef DallasTemperature_h
#define DallasTemperature_h

#define DALLASTEMPLIBVERSION "3.7.2" //!< Version of the library

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef REQUIRESNEW
#define REQUIRESNEW                                                            \
  false //!< set to true to include code for new and delete operators
#endif

#ifndef REQUIRESALARMS
#define REQUIRESALARMS                                                         \
  true //!< set to true to include code implementing alarm search functions
#endif

#include <OneWire.h>
#include <inttypes.h>

// Model IDs
#define DS18S20MODEL 0x10  //!< DS18S20 model ID
#define DS18B20MODEL 0x28  //!< DS18B20 model ID
#define DS1822MODEL 0x22   //!< DS1822 model ID
#define MAX31850MODEL 0x3B //!< MAX31850 model ID

// OneWire commands
#define STARTCONVO                                                             \
  0x44 //!< Tells device to take a temperature reading and put it on the
       //!< scratchpad
#define COPYSCRATCH 0x48     //!< Copy EEPROM
#define READSCRATCH 0xBE     //!< Read EEPROM
#define WRITESCRATCH 0x4E    //!< Write to EEPROM
#define RECALLSCRATCH 0xB8   //!< Reload from last known
#define READPOWERSUPPLY 0xB4 //!< Determine if device needs parasite power
#define ALARMSEARCH 0xEC     //!< Query bus for devices with an alarm condition

// Scratchpad locations
#define TEMP_LSB 0        //!< Temperature LSB byte location
#define TEMP_MSB 1        //!< Temperature MSB byte location
#define HIGH_ALARM_TEMP 2 //!< High alarm temp byte location
#define LOW_ALARM_TEMP 3  //!< Low alarm temp byte location
#define CONFIGURATION                                                          \
  4 //!< DS18S20: store for CRC. DS18B20 & DS1822: configuration register
#define INTERNAL_BYTE 5 //!< Internal use & CRC
#define COUNT_REMAIN                                                           \
  6 //!< DS18S20: COUNT_REMAIN, DS18B20 & DS1822: store for CRC
#define COUNT_PER_C 7 //!< DS18S20: COUNT_PER_C. DS18B20 & DS1822: store for crc
#define SCRATCHPAD_CRC 8 //!< Scratchpad CRC

// Device resolution
#define TEMP_9_BIT 0x1F  //!<  9 bit resolution
#define TEMP_10_BIT 0x3F //!< 10 bit resolution
#define TEMP_11_BIT 0x5F //!< 11 bit resolution
#define TEMP_12_BIT 0x7F //!< 12 bit resolution

// Error Codes
#define DEVICE_DISCONNECTED -127 //!< Device disconnected error code

typedef uint8_t DeviceAddress[8]; //!< Device address

/*!
 * @brief DallasTemperature class
 */
class DallasTemperature {
public:
  /*!
   * @brief DallasTemp constructor
   */
  DallasTemperature(OneWire *);

  /*!
   * @brief initalise the bus
   */
  void begin(void);

  /*!
   * @brief returns the number of devices found on the bus
   * @return Returns the number of devices found on the bus
   */
  uint8_t getDeviceCount(void);

  /*!
   * @brief Checks if a conversion is complete on the wire
   * @return Returns whether the conversion is complete
   */
  bool isConversionComplete(void);

  /*!
   * @brief returns true if address is valid
   * @param deviceAddress Address to determine the validity
   * @return Returns true if address is valid
   */
  bool validAddress(uint8_t *);

  /*!
   * @brief finds an address at a given index on the bus
   * @param deviceAddress Device address to search for
   * @param index Where on the index to search
   * @return Returns true if the device was found
   */
  bool getAddress(uint8_t *, const uint8_t);

  /*!
   * @brief attempt to determine if the device at the given address is connected
   * to the bus
   * @param deviceAddress Address to search for
   * @return Returns true if the device is connected
   */
  bool isConnected(uint8_t *);

  /*!
   * @brief attempt to determine if the device at the given address is connected
   * to the bus also allows for updating the read scratchpad
   * @param deviceAddress Address to check the connection
   * @param scratchPad scratchPad to update
   * @return Returns true if connected
   */
  bool isConnected(uint8_t *, uint8_t *);

  /*!
   * @brief read device's scratchpad
   * @param deviceAddress Address to read the scratchpad of
   * @param scratchPad Scratch pad to read from
   */
  void readScratchPad(uint8_t *, uint8_t *);

  /*!
   * @brief write device's scratchpad
   * @param deviceAddress Address of the device to write to
   * @param scratchPad Scratch pad to write to
   */
  void writeScratchPad(uint8_t *, const uint8_t *);

  /*!
   * @brief read device's power requirements
   * @param deviceAddress Address of the device to read from
   * @return Returns True if the device has power requirements
   */
  bool readPowerSupply(uint8_t *);

  /*!
   * @brief gets global resolution
   * @return Returns the global resolution
   */
  uint8_t getResolution();

  /*!
   * @brief set global resolution to 9, 10, 11, or 12 bits
   * @param newResolution Resolution to set to
   */
  void setResolution(uint8_t);

  /*!
   * @brief Returns the device resolution, 9-12
   * @param deviceAddress Device to get the resolution of
   * @return Returns the device resolution, 9-12
   */
  uint8_t getResolution(uint8_t *);

  /*!
   * @brief set resolution of a device to 9, 10, 11, or 12 bits
   * @param deviceAddress Address of device to set the resolution of
   * @param newResolution Resolution to set
   * @return Returns True if successful
   */
  bool setResolution(uint8_t *, uint8_t);

  /*!
   * @brief sets the waitForConversion flag
   * @param flag What value to set the waitForConversion flag to
   */
  void setWaitForConversion(bool);
  /*!
   * @brief gets the value of the waitForConversion flag
   * @return Returns the value of the waitForConversion flag
   */
  bool getWaitForConversion(void);

  /*!
   * @brief sets the checkForConversion flag
   * @param flag What value to set the checkForConversion flag to
   */
  void setCheckForConversion(bool);
  /*!
   * @brief gets the value of the checkForConversion flag
   * @return Returns the value of the checkForConversion flag
   */
  bool getCheckForConversion(void);

  /*!
   * @brief sends command for all devices on the bus to perform a temperature
   * conversion
   */
  void requestTemperatures(void);

  /*!
   * @brief sends command for one device to perform a temperature conversion by
   * address
   * @param deviceAddress Address of the desired device
   * @return Returns FALSE if device is disconnected. Otherwise returns TRUE
   */
  bool requestTemperaturesByAddress(uint8_t *);

  /*!
   * @brief sends command for one device to perform a temperature conversion by
   * index
   * @param deviceIndex Index of the device to send the command to
   * @return Returns FALSE if device is disconnected. Otherwise returns TRUE
   */
  bool requestTemperaturesByIndex(uint8_t);

  /*!
   * @brief returns temperature in degrees C or DEVICE_DISCONNECTED if the
   * device's scratch pad cannot be read successfully.
   * the numeric value of DEVICE_DISCONNECTED is defined in
   * DallasTemperature.h. It is a large negative number outside the
   * operating range of the device
   * @param deviceAddress Address of the device to get the temperature from
   * @return Returns DEVICE_DISCONNECTED if device is disconnected. Otherwise
   * returns the temperature
   */
  float getTempC(uint8_t *);

  /*!
   * @brief returns temperature in degrees F
   * @param deviceAddress Address of the device to get the temperature from
   * @return Returns DEVICE_DISCONNECTED if device is disconnected. Otherwise
   * returns the temperature
   */
  float getTempF(uint8_t *);

  /*!
   * @brief Get temperature for device index (slow)
   * @param deviceIndex Index of the device
   * @return Returns DEVICE_DISCONNECTED if device is disconnected. Otherwise
   * returns the temperature
   */
  float getTempCByIndex(uint8_t);

  /*!
   * @brief Get temperature for device index (slow)
   * @param deviceIndex Index of the device
   * @return Returns DEVICE_DISCONNECTED if device is disconnected. Otherwise
   * returns the temperature
   */
  float getTempFByIndex(uint8_t);

  /*!
   * @brief returns true if the bus requires parasite power
   * @return returns true if the bus requires parasite power
   */
  bool isParasitePowerMode(void);

  /*!
   * @brief Checks if the clock has been raised indicating the conversion is
   * complete
   * @param deviceAddress Address of the device to check
   * @return Returns True if conversion is available
   */
  bool isConversionAvailable(uint8_t *);

#if REQUIRESALARMS

  typedef void AlarmHandler(uint8_t *);

  // sets the high alarm temperature for a device
  // accepts a char.  valid range is -55C - 125C
  void setHighAlarmTemp(uint8_t *, const char);

  // sets the low alarm temperature for a device
  // accepts a char.  valid range is -55C - 125C
  void setLowAlarmTemp(uint8_t *, const char);

  // returns a signed char with the current high alarm temperature for a device
  // in the range -55C - 125C
  char getHighAlarmTemp(uint8_t *);

  // returns a signed char with the current low alarm temperature for a device
  // in the range -55C - 125C
  char getLowAlarmTemp(uint8_t *);

  // resets internal variables used for the alarm search
  void resetAlarmSearch(void);

  // search the wire for devices with active alarms
  bool alarmSearch(uint8_t *);

  // returns true if ia specific device has an alarm
  bool hasAlarm(uint8_t *);

  // returns true if any device is reporting an alarm on the bus
  bool hasAlarm(void);

  // runs the alarm handler for all devices returned by alarmSearch()
  void processAlarms(void);

  // sets the alarm handler
  void setAlarmHandler(AlarmHandler *);

  // The default alarm handler
  static void defaultAlarmHandler(uint8_t *);

#endif

  /*!
   * @brief convert float celsius to farenheit
   * @param celsius Float of degrees celsius
   * @return Returns the degrees in fahrenheit
   */
  static float toFahrenheit(const float);

  /*!
   * @brief convert float farenheit to celsius
   * @param fahrenheit Float of degrees fahrenheit
   * @return Returns the degrees in celsius
   */
  static float toCelsius(const float);

#if REQUIRESNEW

  // initalize memory area
  void *operator new(unsigned int);

  // delete memory reference
  void operator delete(void *);

#endif

private:
  typedef uint8_t ScratchPad[9];

  // parasite power on or off
  bool parasite;

  // used to determine the delay amount needed to allow for the
  // temperature conversion to take place
  uint8_t bitResolution;

  // used to requestTemperature with or without delay
  bool waitForConversion;

  // used to requestTemperature to dynamically check if a conversion is complete
  bool checkForConversion;

  // count of devices on the bus
  uint8_t devices;

  // Take a pointer to one wire instance
  OneWire *_wire;

  // reads scratchpad and returns the temperature in degrees C
  float calculateTemperature(uint8_t *, uint8_t *);

  void blockTillConversionComplete(uint8_t *, uint8_t *);

#if REQUIRESALARMS

  // required for alarmSearch
  uint8_t alarmSearchAddress[8];
  char alarmSearchJunction;
  uint8_t alarmSearchExhausted;

  // the alarm handler function pointer
  AlarmHandler *_AlarmHandler;

#endif
};
#endif
