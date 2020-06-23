# Adafruit DallasTemp Library [![Build Status](https://github.com/adafruit/MAX31850_DallasTemp/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/MAX31850_DallasTemp/actions)[![Documentation](https://github.com/adafruit/ci-arduino/blob/master/assets/doxygen_badge.svg)](http://adafruit.github.io/MAX31850_DallasTemp/html/index.html)

Arduino Library for Dallas Temperature ICs
==========================================

For MAX31850 support, be sure to also get OneWire from
https://github.com/adafruit/MAX31850_OneWire

Usage
-----

This library supports the following devices: 
    MAX31850
    DS18B20
    DS18S20 - Please note there appears to be an issue with this series.
    DS1822

You will need a pull-up resistor of about 5 KOhm between the 1-Wire data line
and your 3 or 5V power. If you are using the DS18B20, ground pins 1 and 3. The
centre pin is the data line '1-wire'.

Credits
-------

The OneWire code has been derived from
http://www.arduino.cc/playground/Learning/OneWire.
Miles Burton <miles@mnetcs.com> originally developed this library.
Tim Newsome <nuisance@casualhacker.net> added support for multiple sensors on
the same bus.
Guil Barros [gfbarros@bappos.com] added getTempByAddress (v3.5)
Rob Tillaart [rob.tillaart@gmail.com] added async modus (v3.7.0)
ladyada added MAX31850 support

Website
-------

You can find the latest version of the library at
http://milesburton.com/index.php?title=Dallas_Temperature_Control_Library

License
-------

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
