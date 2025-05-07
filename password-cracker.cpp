#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <string>

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)str.c_str(), str.size(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return ss.str();
}

void crackPassword(const std::string& targetHash, const std::string& wordlistFile) {
    std::ifstream infile(wordlistFile);
    if (!infile.is_open()) {
        std::cerr << "Could not open wordlist file.\n";
        return;
    }

    std::string word;
    while (std::getline(infile, word)) {
        std::string hashed = sha256(word);
        if (hashed == targetHash) {
            std::cout << "[+] Password found: " << word << "\n";
            return;
        }
    }

    std::cout << "[-] Password not found in wordlist.\n";
}

int main() {
    std::string hashToCrack;
    std::string wordlist;

    std::cout << "Enter SHA-256 hash to crack: ";
    std::cin >> hashToCrack;
    std::cout << "Enter path to wordlist: ";
    std::cin >> wordlist;

    crackPassword(hashToCrack, wordlist);

    return 0;
}
