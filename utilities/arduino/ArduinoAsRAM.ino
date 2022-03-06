const byte data[256] = {};

// 12 is LSB, A5 is MSB
const int addressPins[] = { 12, 13, A0, A1, A2, A3, A4, A5 };

// 0 is LSB, 3 is MSB
const int dataInPins[] = { 0, 1, 2, 3 };

// 0 is LSB, 3 is MSB
const int dataOutPins[] = { 4, 5, 6, 7 };

const int readWritePin = 8;
const int clockPin = 9;

// Don't update datalines unless address changes
int lastAddress = -1;

int getCurrentAddress() {
    int address = 0;
    for (int i = 0; i < sizeof(addressPins); i++) {
        address |= digitalRead(addressPins[i]) << i;
    }
    return address;
}

byte getCurrentData(int currentAddress) {
    Serial.print("Reading Address: ");
    Serial.print(currentAddress, HEX);
    return pgm_read_word_near(machineCode + currentAddress);
}

void outputCurrentData(int currentData) {
    for (int i = 0; i < sizeof(dataPins); i++) {
        digitalWrite(dataPins[i], currentData & 1);
        currentData >>= 1;
    }
    Serial.print(" - Outputing: ");
    Serial.println(currentData, HEX);
}

void setup() {
    Serial.begin(9600)
        while (!Serial);

    for (int i = 0; i < sizeof(addressPins); i++) {
        pinMode(addressPins[i], INPUT);
    }

    for (int i = 0; i < sizeof(dataPins); i++) {
        pinMode(dataPins[i], OUTPUT);
    }

    Serial.println("Initialized");
}


void loop() {
    int currentAddress = getCurrentAddress();
    if (currentAddress != lastAddress) {
        byte currentData = getCurrentData(currentAddress);
        outputCurrentData(currentData);
        lastAddress = currentAddress;
    }
}
