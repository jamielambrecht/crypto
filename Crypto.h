#pragma once

enum STATE {
	STATE_INITIAL = 0,
	STATE_INPUT,
	STATE_ENCRYPT,
	STATE_DECRYPT,
	STATE_RESET,
	STATE_EXIT,
	STATE_STATES_COUNT
};

const unsigned DATA_BUFFER_SIZE = 129;
const unsigned KEY_SIZE = 9;

class Crypto {

private:
	char InputDataBuffer[DATA_BUFFER_SIZE];
	char CryptKey[KEY_SIZE];
	char CryptoMatrix[DATA_BUFFER_SIZE];
	char ClearMatrix[DATA_BUFFER_SIZE];
	short InputDataCount;

	bool StateFlags[STATE_STATES_COUNT] = { 0 };

public:
	Crypto();
	~Crypto();

	void InputData();
	void Encrypt();
	void Decrypt();
	void DisplayCryptoMatrix();
	void DisplayClearMatrix();
};


