/*
 * Author: Yevgeniy Kiveisha <yevgeniy.kiveisha@intel.com>
 * Copyright (c) 2014 Intel Corporation.
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

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "max44009.h"

using namespace upm;

MAX44009::MAX44009 (int bus, int devAddr) {
    m_name = "MAX44009";

    m_maxControlAddr = devAddr;
    m_bus = bus;

    m_i2cMaxControlCtx = mraa_i2c_init(m_bus);

    mraa_result_t ret = mraa_i2c_address(m_i2cMaxControlCtx, m_maxControlAddr);
    if (ret != MRAA_SUCCESS) {
        fprintf(stderr, "Messed up i2c bus\n");
    }
}

MAX44009::~MAX44009() {
    mraa_i2c_stop(m_i2cMaxControlCtx);
}

uint16_t
MAX44009::getLuxValue () {
    uint8_t data = 0;
    uint8_t exponent = 0;
    uint8_t mantissa = 0;

    data = i2cReadReg_8 (LUXDATA_HIGH);
    exponent = data >> 4;
    mantissa = data & 0xF;

    return pow(2, exponent) * mantissa * 0.72;
}

uint8_t
MAX44009::getLuxData () {
    uint8_t data = 0;

    data = i2cReadReg_8 (LUXDATA_HIGH);

    return data;
}

/*
 * **************
 *  private area
 * **************
 */
uint8_t
MAX44009::i2cReadReg_8 (int reg) {
    uint8_t data;

    mraa_i2c_address(m_i2cMaxControlCtx, m_maxControlAddr);
    mraa_i2c_write_byte(m_i2cMaxControlCtx, reg);

    mraa_i2c_address(m_i2cMaxControlCtx, m_maxControlAddr);
    mraa_i2c_read(m_i2cMaxControlCtx, &data, 0x1);

    return data;
}

uint16_t
MAX44009::i2cReadReg_16 (int reg) {
    uint16_t data;

    mraa_i2c_address(m_i2cMaxControlCtx, m_maxControlAddr);
    mraa_i2c_write_byte(m_i2cMaxControlCtx, reg);

    mraa_i2c_address(m_i2cMaxControlCtx, m_maxControlAddr);
    mraa_i2c_read(m_i2cMaxControlCtx, (uint8_t *)&data, 0x2);

    return data;
}

mraa_result_t
MAX44009::i2cWriteReg (uint8_t reg, uint8_t value) {
    mraa_result_t error = MRAA_SUCCESS;

    uint8_t data[2] = { reg, value };
    error = mraa_i2c_address (m_i2cMaxControlCtx, m_maxControlAddr);
    error = mraa_i2c_write (m_i2cMaxControlCtx, data, 2);

    return error;
}
