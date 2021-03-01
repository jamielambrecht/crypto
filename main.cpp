#include "Crypto.h"
#include <iostream>
#include <limits>
#include <cstring>
#include <cstdio>
#include <stdio.h>
using namespace std;

Crypto::Crypto() {
	
	for (unsigned i = 0; i < DATA_BUFFER_SIZE - 1; i++) {
		InputDataBuffer[i] = 0x00;
	}
	InputDataBuffer[DATA_BUFFER_SIZE - 1] = 0x00;

	for (unsigned i = 0; i < KEY_SIZE - 1; i++) {
		CryptKey[i] = 0x00;
	}
	CryptKey[KEY_SIZE - 1] = 0x00;

	for (unsigned i = 0; i < DATA_BUFFER_SIZE - 1; i++) {
		CryptoMatrix[i] = 0x00;
	}
	CryptoMatrix[DATA_BUFFER_SIZE - 1] = 0x00;

	for (unsigned i = 0; i < DATA_BUFFER_SIZE - 1; i++) {
		ClearMatrix[i] = 0x00;
	}
	ClearMatrix[DATA_BUFFER_SIZE - 1] = 0x00;
	

	//memset(InputDataBuffer, 0x00, DATA_BUFFER_SIZE);
	//memset(CryptoMatrix, 0x00, DATA_BUFFER_SIZE);
	//memset(ClearMatrix, 0x00, DATA_BUFFER_SIZE);
	//memset(CryptKey, 0x00, KEY_SIZE);
}

Crypto::~Crypto() { }

void Crypto::InputData() {
	if (!StateFlags[STATE_INPUT]) {

		do {
			if (cin.fail()) {
				cout << "ERROR: Message limit exceeded.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				//memset(InputDataBuffer, 0x00, DATA_BUFFER_SIZE);
				for (unsigned i = 0; i < DATA_BUFFER_SIZE - 1; i++) {
					InputDataBuffer[i] = 0x00;
				}
				InputDataBuffer[DATA_BUFFER_SIZE - 1] = 0x00;
			}
			cout << endl;
			cout << "Please enter the message to encrypt (Max 128 characters).\n";
			cin.getline(InputDataBuffer, DATA_BUFFER_SIZE);
		} while (cin.fail());
		InputDataCount = strlen(InputDataBuffer);
		cout << InputDataCount << " characters read." << '\n';
		cout << endl;

		StateFlags[STATE_INPUT] = true;
	}
	else {
		cout << endl;
		cout << "There is already a message. Use reset to start over.\n";
		cout << endl;
	}

}

void Crypto::Encrypt() {
	if (StateFlags[STATE_INPUT]) {
		if (!StateFlags[STATE_ENCRYPT]) {

			do {
				if (cin.fail()) {
					cout << "ERROR: Invalid key length.\n";
					cin.clear();
					if (strlen(CryptKey) >= 8) {
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					//memset(CryptKey, 0x00, KEY_SIZE);
					for (unsigned i = 0; i < KEY_SIZE - 1; i++) {
						CryptKey[i] = 0x00;
					}
					CryptKey[KEY_SIZE - 1] = 0x00;
				}
				cout << endl;
				cout << "Please enter an encryption key (8 characters).\n";
				cin.getline(CryptKey, KEY_SIZE);
				if (strlen(CryptKey) < KEY_SIZE - 1) {
					cin.setstate(ios_base::failbit);
				}
			} while (cin.fail());

			int i = 0;
			while (i < InputDataCount || i % (KEY_SIZE - 1) != 0) {
				CryptoMatrix[i] = InputDataBuffer[i] ^ CryptKey[i % (KEY_SIZE - 1)];
				i++;
			}
			cout << endl;
			cout << "Message encrypted!\n";
			StateFlags[STATE_ENCRYPT] = true;
		}
		else {
			cout << endl;
			cout << "Message is already encrypted!\n";
		}
	}
	else {
		cout << "Nothing to encrypt!\n";
	}
}

void Crypto::Decrypt() {
	if (StateFlags[STATE_ENCRYPT]) {
		if (!StateFlags[STATE_DECRYPT]) {
			int i = 0;
			while (i < InputDataCount || i % (KEY_SIZE - 1) != 0) {
				ClearMatrix[i] = CryptoMatrix[i] ^ CryptKey[i % (KEY_SIZE - 1)];
				i++;
			}
			cout << endl;
			cout << "Message decrypted!\n";
			StateFlags[STATE_DECRYPT] = true;
		}
		else {
			cout << endl;
			cout << "Message is already decrypted!\n";
		}
	}
}

void Crypto::DisplayCryptoMatrix() {
	if (StateFlags[STATE_ENCRYPT]) {
		cout << "Encrypted message: ";
		//printf("%s\n", CryptoMatrix);
		for (size_t i = 0; i < InputDataCount; i++) {
			cout << CryptoMatrix[i];
		}
		cout << endl;
	}
	else {
		cout << "No encrypted message to display!\n";
	}
	cout << endl;
}

void Crypto::DisplayClearMatrix() {
	if (StateFlags[STATE_DECRYPT]) {
		cout << "Decrypted message: ";
		//printf("%s\n", ClearMatrix);
		for (size_t i = 0; i < InputDataCount; i++) {
			cout << ClearMatrix[i];
		}
		cout << endl;
	}
	else {
		cout << "No decrypted message to display!\n";
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	cout << "Crypto: Message Encryption Program\n";
	Crypto* crypto = new Crypto();
	bool exit_flag = false;
	char menu_input;
	do {
		cout << "Please select an option:\n";
		cout << "1. Enter a message.\t2. Encrypt message.\n";
		cout <<	"3. Decrypt Message.\t4. Reset\n";
		cout << "5. Exit\n";
		cin.get(menu_input);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (menu_input - 48) {
		case STATE_INPUT:
			crypto->InputData();
			break;
		case STATE_ENCRYPT:
			crypto->Encrypt();
			crypto->DisplayCryptoMatrix();
			break;
		case STATE_DECRYPT:
			crypto->Decrypt();
			crypto->DisplayClearMatrix();
			break;
		case STATE_RESET:
			cout << endl;
			cout << "Are you sure you want to reset? All data will be lost. (y/N): ";
			cin.get(menu_input);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (menu_input == 89 || menu_input == 121) {
				delete crypto;
				crypto = new Crypto();
				cout << "All data has been reset!\n";
			}
			cout << endl;
			break;
		case STATE_EXIT:
			exit_flag = true;
			break;
		default:
			// cin.clear();
			// cin.ignore(numeric_limits<streamsize>::max(), '\n');	
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