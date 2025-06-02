#include <string>
#include <bitset>

std::string uint32_to_ip(uint32_t ip) {
    // Extract each octet from the 32-bit number by shifting and masking
    uint8_t octet1 = (ip >> 24) & 0xFF; // Right-shift 24 bits to get the first 8 bits (1st octet)
    uint8_t octet2 = (ip >> 16) & 0xFF; // Right-shift 16 bits to get the next 8 bits (2nd octet)
    uint8_t octet3 = (ip >> 8)  & 0xFF; // Right-shift 8 bits to get the next 8 bits (3rd octet)
    uint8_t octet4 = ip & 0xFF;         // No shift needed for the last 8 bits (4th octet)
    
    // Convert each octet to a string and concatenate them with '.' as separator
    return std::to_string(octet1) + "." + 
           std::to_string(octet2) + "." + 
           std::to_string(octet3) + "." + 
           std::to_string(octet4);
}