/*
 * Copyright 2014 The Imaging Source Europe GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _USB3CAMERA_H_
#define _USB3CAMERA_H_

#include "UsbSession.h"
#include "UsbCamera.h"

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "libusb-1.0/libusb.h"

namespace tis
{

struct device_info;


class Usb3Camera : public UsbCamera
{

public:

    Usb3Camera (std::shared_ptr<UsbSession> session, device_info dev, unsigned int _interface = 0);

    ~Usb3Camera ();

    Usb3Camera (const Usb3Camera& _camera) = delete;
    Usb3Camera& operator=(const Usb3Camera&) = delete;

    /// @name get_firmware_version
    /// @return integer containing the currently used firmware version
    int get_firmware_version ();

    int delete_firmware (std::function<void(int)> progress);
    /// @name download_firmware
    /// @param firmware - vector containing the firmware file
    /// @param progress - callback function
    /// @return libusb return value; >= 0 on success
    int download_firmware (std::vector<unsigned char>& firmware, std::function<void(int)> progress);

    /// @name upload_firmware
    /// @param firmware_package - path to firmware/firmwarepack that shall be used
    /// @param firmware - optional firmware file name that shall be extracted from firmwarepack
    /// @param progress - callback function for updates
    /// @return true if success
    /// @brief uploads firmware to camera
    bool upload_firmware (const std::string& firmware_package,
                          const std::string& firmware,
                          std::function<void(int)> progress);

    UVC_COMPLIANCE get_mode ();

    int set_mode (UVC_COMPLIANCE mode);

private:

    /// @name write_eeprom
    /// @param
    /// @param
    /// @param
    /// @return
    /// @brief
    int write_eeprom (unsigned int addr, unsigned char* data, unsigned int size);


    /// @name read_eeprom
    /// @param addr - address from which to read
    /// @param data - buffer in which read data shall be written
    /// @param size - size of data
    /// @return integer response from libusb; >= 0 on success
    int read_eeprom (unsigned int addr, unsigned char* data, unsigned int size);

    /// @erase_sector
    /// @param addr - address of sector that shall be erased
    /// @return integer response from libusb; >= 0 on success
    int erase_sector (unsigned int addr);

    /// @erase_eeprom
    /// @param progress - callback function for progress updates
    /// @return
    int erase_eeprom (std::function<void(int)> progress);

    bool initialize_eeprom (std::vector<uint8_t>& firmware);

    /// @name upload_firmware_file
    /// @param firmware - vector containing the firmware that shall be written
    /// @param progress - callback function
    /// @return
    /// @brief
    int upload_firmware_file (std::vector<uint8_t> firmware, std::function<void(int)> progress);

}; /* class Usb3Camera */

}; /* namespace tis */

#endif /* _USB3CAMERA_H_ */
