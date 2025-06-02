#include <string>   // Required for std::string and std::to_string
#include <cstdint>  // Required for uint32_t to ensure a 32-bit unsigned integer type

// Function to convert an unsigned 32-bit integer to its IPv4 string representation.
// An IPv4 address consists of 4 octets (bytes), where each octet is an 8-bit number
// ranging from 0 to 255. A 32-bit unsigned integer can be conceptualized as these
// four 8-bit octets concatenated together.
// The problem requires extracting these four octets from the 32-bit number
// and formatting them as a "X.X.X.X" string.

std::string uint32_to_ipv4(uint32_t ip_num) {
    // To extract each octet, we utilize bitwise right shifts and bitwise AND operations.
    // A bitwise right shift (>>) moves the bits of the number to the right.
    // Shifting by N bits is equivalent to dividing by 2^N.
    // A bitwise AND with 0xFF (which is 255 in decimal, or 11111111 in binary)
    // acts as a mask, isolating only the lowest 8 bits after the shift.

    // Extract the first octet (most significant 8 bits):
    // We shift the 32-bit number right by 24 bits (3 * 8 bits). This brings the
    // bits of the first octet to the least significant 8-bit position.
    // Then, we apply the 0xFF mask to ensure we only capture these 8 bits.
    uint8_t octet1 = (ip_num >> 24) & 0xFF;

    // Extract the second octet:
    // We shift the 32-bit number right by 16 bits (2 * 8 bits). This brings the
    // bits of the second octet to the least significant 8-bit position.
    // Then, we apply the 0xFF mask.
    uint8_t octet2 = (ip_num >> 16) & 0xFF;

    // Extract the third octet:
    // We shift the 32-bit number right by 8 bits (1 * 8 bits). This brings the
    // bits of the third octet to the least significant 8-bit position.
    // Then, we apply the 0xFF mask.
    uint8_t octet3 = (ip_num >> 8) & 0xFF;

    // Extract the fourth octet (least significant 8 bits):
    // No right shift is needed as these bits are already in the least significant
    // 8-bit position. We simply apply the 0xFF mask to isolate them.
    uint8_t octet4 = ip_num & 0xFF;

    // Convert each extracted octet (which are integer values between 0 and 255)
    // to its string representation using std::to_string.
    // Then, concatenate these string representations with dots in between to form
    // the final IPv4 address string.
    std::string result = std::to_string(octet1) + "." +
                         std::to_string(octet2) + "." +
                         std::to_string(octet3) + "." +
                         std::to_string(octet4);

    return result;
}
