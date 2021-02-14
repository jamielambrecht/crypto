#include "Crypto.h"
#include <iostream>
#include <limits>
#include <cstring>
#include <cstdio>
#include <stdio.h>

Crypto::Crypto() {
	/*
	for (unsigned i = 0; i < DATA_BUFFER_SIZE - 1; i++) {
		InputDataBuffer[i] = 0x20;
	}
	InputDataBuffer[DATA_BUFFER_SIZE - 1] = 0x00;

	for (unsigned i = 0; i < KEY_SIZE - 1; i++) {
		CryptKey[i] = 0x20;
	}
	CryptKey[KEY_SIZE - 1] = 0x00;
	*/

	std::memset(InputDataBuffer, 0x00, DATA_BUFFER_SIZE);
	std::memset(CryptoMatrix, 0x00, DATA_BUFFER_SIZE);
	std::memset(ClearMatrix, 0x00, DATA_BUFFER_SIZE);
	std::memset(CryptKey, 0x00, KEY_SIZE);
}

Crypto::~Crypto() { }

void Crypto::InputData() {
	if (std::strlen(InputDataBuffer) == 0) {

		do {
			if (std::cin.fail()) {
				std::cout << "ERROR: Message limit exceeded.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::memset(InputDataBuffer, 0x00, DATA_BUFFER_SIZE);
			}
			std::cout << "Please enter the message to encrypt (Max 128 characters).\n";
			std::cin.getline(InputDataBuffer, DATA_BUFFER_SIZE);
		} while (std::cin.fail());
		InputDataCount = strlen(InputDataBuffer);
		std::cout << InputDataCount << " characters read." << '\n';
		std::cout << std::endl;


	} else {
		std::cout << "There is already a message. Use reset to start over.\n";
	}

}

void Crypto::Encrypt() {
	if (std::strlen(InputDataBuffer) > 0) {
		if (std::strlen(CryptoMatrix) == 0) {

			do {
				if (std::cin.fail()) {
					std::cout << "ERROR: Invalid key length.\n";
					std::cin.clear();
					if (std::strlen(CryptKey) >= 8) {
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::memset(CryptKey, 0x00, KEY_SIZE);
				}
				std::cout << "Please enter an encryption key (8 characters).\n";
				std::cin.getline(CryptKey, KEY_SIZE);
				if (std::strlen(CryptKey) < 8) {
					std::cin.setstate(std::ios_base::failbit);
				}
			} while (std::cin.fail());
			std::cout << std::endl;

			int i = 0;
			while (i < InputDataCount || i % (KEY_SIZE - 1) != 0) {	
				CryptoMatrix[i] = InputDataBuffer[i] ^ CryptKey[i % (KEY_SIZE - 1)];
				i++;
			}
			std::cout << "Message encrypted!\n";
			std::cout << std::endl;

		} else {
			std::cout << "Message is already encrypted!\n";
		}
	} else {
		std::cout << "Nothing to encrypt!\n";
	}
}

void Crypto::Decrypt() {
	if (std::strlen(CryptoMatrix) > 0) {
		if (std::strlen(ClearMatrix) == 0) {
			int i = 0;
			while (i < InputDataCount || i % (KEY_SIZE - 1) != 0) {	
				ClearMatrix[i] = CryptoMatrix[i] ^ CryptKey[i % (KEY_SIZE - 1)];
				i++;
			}
			std::cout << "Message decrypted!\n";
			std::cout << std::endl;
		} else {
			std::cout << "Message is already decrypted!\n";
		}
	} else {
		std::cout << "Nothing to decrypt!\n";
	}
}

void Crypto::DisplayCryptoMatrix() {
	if (std::strlen(CryptoMatrix) > 0) {
		std::cout << "Encrypted message: ";
		printf("%s\n", CryptoMatrix);
	} else {
		std::cout << "No encrypted message to display!\n";
	}
	std::cout << std::endl;
}

void Crypto::DisplayClearMatrix() {
	if (std::strlen(ClearMatrix) > 0) {
		std::cout << "Decrypted message: ";
		printf("%s\n", ClearMatrix);
		std::cout << std::endl;
	} else {
		std::cout << "No decrypted message to display!\n";
	}
}	

int main(int argc, char *argv[]) {
	std::cout << "Crypto: Message Encryption Program\n";
	Crypto * crypto = new Crypto();
	bool exit_flag = false;
	char menu_input;
	do {
		std::cout << "Please select an option:\n";
		std::cout << "1. Enter a message.\t\t2. Encrypt message.\t\t3. Decrypt Message.\n";
		std::cout << "4. Display encrypted message.\t5. Display Decrypted Message.\t6. Reset\t\t7. Exit\n";
		std::cin.get(menu_input);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
		switch (menu_input) {
			case '1':
				crypto->InputData();
				break;
			case '2':
				crypto->Encrypt();
				break;
			case '3':
				crypto->Decrypt();
				break;
			case '4':
				crypto->DisplayCryptoMatrix();
				break;
			case '5':
				crypto->DisplayClearMatrix();
				break;
			case '6':
				std::cout << "Are you sure you want to reset? (All data will be lost.) y/N\n";
				std::cin.get(menu_input);
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
				if (std::tolower(menu_input) == 'y') {
					delete crypto;
					crypto = new Crypto();
					std::cout << "All data has been reset!\n\n";
				}
				break;
			case '7':
				exit_flag = true;
				break;
			default:
				// std::cin.clear();
				// std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
				exit_flag = false;
		} 
	} while (!exit_flag);

	/*
	crypto->InputData();
	crypto->Encrypt();
	crypto->Decrypt();
	crypto->DisplayCryptoMatrix();
	crypto->DisplayClearMatrix();
	*/
	return 0;

}