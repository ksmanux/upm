/*
 * Author: Henry Bruce <henry.bruce@intel.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#pragma once

#include <stdint.h>
#include "iModuleStatus.h"

namespace upm
{
/**
 * @brief ILightSensor Interface for Light Sensors
 */
 
/**
 *
 * @brief Interface for Light Sensors
 
 * This interface is used to represent light sensors

 * @snippet light-sensor.cxx Interesting 
 */

   class ILightSensor : public IModuleStatus
   {
   public:
	/**
	 * Get visible illuminance raw value.
	 *
	 * @return uint16_t visible illuminance raw value
	 */
       virtual uint16_t getVisibleRaw() = 0;

	/**
	 * Get visible illuminance in Lux.
	 *
	 * @return double visible illuminance in Lux
	 */
       virtual double getVisibleLux() = 0;


       virtual ~ILightSensor() {}
   };
}

