
class Crypto {

	static const unsigned DATA_BUFFER_SIZE = 129;
	static const unsigned KEY_SIZE = 9;

private:
	char InputDataBuffer[DATA_BUFFER_SIZE];
	char CryptKey[KEY_SIZE];
	char CryptoMatrix[DATA_BUFFER_SIZE];
	char ClearMatrix[DATA_BUFFER_SIZE];
	short InputDataCount;

public:
	Crypto();
	~Crypto();

	void InputData();
	void Encrypt();
	void Decrypt();
	void DisplayCryptoMatrix();
	void DisplayClearMatrix();
};


