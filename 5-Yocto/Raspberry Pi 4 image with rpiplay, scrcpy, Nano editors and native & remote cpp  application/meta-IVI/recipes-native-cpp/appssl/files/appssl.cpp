#include <iostream>
#include <openssl/sha.h>

int main() {
    const std::string message = "Hello World";
    
    // Create a buffer to hold the hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Compute the SHA256 hash
    SHA256(reinterpret_cast<const unsigned char*>(message.c_str()), message.length(), hash);
    
    // Print the hash in hexadecimal format
    std::cout << "SHA-256 hash of \"" << message << "\" is: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    std::cout << std::endl;
    
    return 0;
}