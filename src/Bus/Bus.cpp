#include <Bus/Bus.h>
#include <exception>
#include <stdexcept>

Bus::Bus(std::size_t addressableLength){
    mAddressableRange = addressableLength;
}

/**
 * Checks if two address ranges conflict
 * with each other.
 *
 * @param range1 - first address range
 * @param range2 - second address range
 *
 * @return whether the ranges conflict
 **/
bool addressRangesConflict(AddressRange range1, AddressRange range2){
    if(range1.second <= range2.first || range2.second <= range1.first){
       return false;
    }else{
       return true;
    }
}

void Bus::registerReadableDevice(ReadableDevice *device, std::size_t lowerAddress, std::size_t upperAddress){
    // Create an address range from the given address bounds
    AddressRange addressRange = std::make_pair(lowerAddress, upperAddress);

    // Check if the given address range conflicts with another device
    for(auto readableIt = mReadableDeviceList.begin(); readableIt != mReadableDeviceList.end(); readableIt++){
        // Get the address pair
        AddressRange deviceAddressRange = readableIt->second;

        // Throw an exception if the ranges conflict
        if(addressRangesConflict(addressRange, deviceAddressRange)){
            throw std::range_error("Address Range Conflicts");
        }

    }

    // Create a registered readable device
    RegisteredReadableDevice registeredReadableDevice = std::make_pair(device, addressRange);

    // Push the device into the list
    mReadableDeviceList.push_back(registeredReadableDevice);
}

void Bus::registerWritableDevice(WritableDevice *device, std::size_t lowerAddress, std::size_t upperAddress){
    // Create an address range from the given address bounds
    AddressRange addressRange = std::make_pair(lowerAddress, upperAddress);

    // Check if the given address range conflicts with another device
    for(auto writableIt = mWritableDeviceList.begin(); writableIt != mWritableDeviceList.end(); writableIt++){
        // Get the address pair
        AddressRange deviceAddressRange = writableIt->second;

        // Throw an exception if the ranges conflict
        if(addressRangesConflict(addressRange, deviceAddressRange)){
            throw std::range_error("Address Range Conflicts");
        }

    }

    // Create a registered writable device
    RegisteredWritableDevice registeredWritableDevice = std::make_pair(device, addressRange);

    // Push the device into the list
    mWritableDeviceList.push_back(registeredWritableDevice);
}

/**
 * Check if the given address is within the address range.
 *
 * @param address - the address to check
 * @param addressRange - the range to check against
 *
 * @return whether or not the address is in the range.
 **/
bool addressInRange(std::size_t address, AddressRange addressRange){
    if(address >= addressRange.first && address < addressRange.second){
        return true;
    }else{
        return false;
    }
}

/**
 * Rectify the given address against the address range.
 *
 * @param address - the address to rectify
 * @param addressRange - the range to rectify against
 *
 * @return the rectified address
 **/
std::size_t rectifyAddress(std::size_t address, AddressRange addressRange){
    return address - addressRange.first;
}

uint8_t Bus::read(std::size_t address){

    // Find the readable device that aligns with the given address
    for(auto readableIt = mReadableDeviceList.begin(); readableIt != mReadableDeviceList.end(); readableIt++){
        // Readable device
        ReadableDevice *device = readableIt->first;

        // Get the device address range
        AddressRange deviceAddressRange = readableIt->second;

        // Check if the address is matching within the range
        if(addressInRange(address, deviceAddressRange)){
            // read from the device
            return (*device).read(rectifyAddress(address, deviceAddressRange));
        }
    }

    // No readable device for the given address
    throw std::out_of_range("No devices in the given address");
}

void Bus::write(std::size_t address, uint8_t value){

}
