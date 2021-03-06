#define L_Wheel 0x04
#define R_Wheel 0x05

// RS485 modbus RTU protocol Communication

static const uint8_t Tx1Pin = 18; //Serial1 tx
static const uint8_t Rx1Pin = 19; //Serial1 rx

uint8_t Tx_Buf[16];
uint8_t Rx_Buf[16];
volatile unsigned char rx_buf_head = 0;

// Real time millis
unsigned long pre_time = 0;
unsigned long now_time = 0;

/*
ISR(USART2_RX_vect) {
    char c = UDR0;
    Rx_Buf[rx_buf_head] = c;
    if (rx_buf_head == 64 - 1)
        rx_buf_head = 0;
    else
        rx_buf_head++;
}
*/
void setup() {
    Serial1.begin(115200);
}

void loop() {
    /* 10sec counter */
    /*
        now_time = millis();
        if (now_time - pre_time > 1000)
        {
            pre_time = now_time;
        }
    */

    /* Read mode */
    /*
        MB_ReadRegFunCode_03H(L_Wheel, 0x202C, 0x0001);
        delay(2000);
    */

    /* Velocity mode */
    /*
        MB_WriteSingleRegFunCode_06H(L_Wheel, 0x2032, 0x0003);    // Left Set Profile Velocity Mode
        delay(10);
        MB_WriteSingleRegFunCode_06H(R_Wheel, 0x2032, 0x0003);    // Right Set Profile Velocity Mode
        delay(10);
        MB_WriteSingleRegFunCode_06H(L_Wheel, 0x2031, 0x0008);    // Left Motor enable
        delay(10);
        MB_WriteSingleRegFunCode_06H(R_Wheel, 0x2031, 0x0008);    // Right Motor enable
        delay(10);
        MB_WriteSingleRegFunCode_06H(L_Wheel, 0x203A, 0x0064);    // Left Set target speed 100RPM(0x0064 = 100)
        delay(10);
        MB_WriteSingleRegFunCode_06H(R_Wheel, 0x203A, 0xFF9C);    // Right Set target speed -100RPM(0xFF9C = -100)
        delay(10);
    */

    /* Absolute Position mode */
    /*
        MB_WriteSingleRegFunCode_06H(L_Wheel, 0x2032, 0x0002);
        delay(1000);
        MB_WriteSingleRegFunCode_06H(L_Wheel, 0x2036, 0x0064);
        delay(1000);
        MB_WriteSingleRegFunCode_06H(L_Wheel, 0x2031, 0x0008);
        delay(1000);
        MB_WriteMultipleRegFunCode_10H(L_Wheel, 0x2034, 0x0000, 0x5000);
        delay(1000);
        MB_WriteSingleRegFunCode_06H(L_Wheel, 0x2031, 0x0010);
        delay(1000);
        Serial1.end();
    */

    /* EBIMU Example */
    /*
        float euler[3];
        if (EBimuAsciiParser(euler, 3))
        {
        Serial.print("\n\r");
        Serial.print(euler[0]);   Serial.print(" ");
        Serial.print(euler[1]);   Serial.print(" ");
        Serial.print(euler[2]);   Serial.print(" ");
        }
        byte buffer [8] ;
        while (Serial2.available() > 0)
        {
        for (uint8_t i = 0 ; i < 8 ; i++)
        {
            buffer[i] = Serial2.read ();
            Serial.write(buffer[i]);
        }
        }
        Serial2.end();
    */
}

static const uint8_t auchCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

static const uint8_t auchCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

uint16_t MB_CRC16(uint8_t *pushMsg, uint8_t usDataLen)
{
    uint8_t uchCRCHi = 0xff;
    uint8_t uchCRCLo = 0xff;
    uint8_t uIndex;
    while (usDataLen--)
    {
        uIndex = uchCRCHi ^ *pushMsg++;
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
        uchCRCLo = auchCRCLo[uIndex];
    }
    return (uchCRCHi << 8 | uchCRCLo);
}

void MB_ReadRegFunCode_03H(uint8_t _addr, uint16_t _reg, uint16_t _num)
{
    uint16_t TxCount = 0;
    uint16_t crc = 0;

    Tx_Buf[TxCount++] = _addr;
    Tx_Buf[TxCount++] = 0x03;
    Tx_Buf[TxCount++] = _reg >> 8;
    Tx_Buf[TxCount++] = _reg;
    Tx_Buf[TxCount++] = _num >> 8;
    Tx_Buf[TxCount++] = _num;

    crc = MB_CRC16((uint8_t*)&Tx_Buf, TxCount);

    Tx_Buf[TxCount++] = crc >> 8;
    Tx_Buf[TxCount++] = crc;
    /* Transmit to ZLAC8015 */
    digitalWrite(Tx1Pin, HIGH);
    for (uint8_t i = 0 ; i < 8 ; i++)
    {
        Serial1.write(Tx_Buf[i]);
    }
    digitalWrite(Tx1Pin, LOW);
    /* Receive from ZLAC8015*/
    /*
        while (Serial1.available() > 0)
        {
        for (uint8_t j = 0 ; j < 7 ; j++)   // Function code 0x03 recevie data is 7
        {
            Rx_Buf[j] = Serial1.read();
        }
        }
        Serial1.flush();

        RX_data[3] = Rx_Buf[3];
        RX_data[2] = Rx_Buf[2];
        RX_data[1] = Rx_Buf[6];
        RX_data[0] = Rx_Buf[5];
    */
}

void MB_WriteSingleRegFunCode_06H(uint8_t _addr, uint16_t _reg, uint16_t _data)
{
    uint16_t TxCount = 0;
    uint16_t crc = 0;
    Tx_Buf[TxCount++] = _addr;            // 역주소에서
    Tx_Buf[TxCount++] = 0x06;             // 기능코드
    Tx_Buf[TxCount++] = _reg >> 8;        // 레지스터 주소 하이 바이트
    Tx_Buf[TxCount++] = _reg;             // 레지스터 주소 로우 바이트
    Tx_Buf[TxCount++] = _data >> 8;       // 레지스터(16bits) 개수가 높은 바이트
    Tx_Buf[TxCount++] = _data;            //로우 바이트

    crc = MB_CRC16((uint8_t*)&Tx_Buf, TxCount);
    Tx_Buf[TxCount++] = crc >> 8;         //crc 하이 바이트
    Tx_Buf[TxCount++] = crc;              //crc  로우 바이트

    digitalWrite(Tx1Pin, HIGH);
    for (uint8_t i = 0 ; i < 8 ; i++)
    {
        Serial1.write(Tx_Buf[i]);
    }
    digitalWrite(Tx1Pin, LOW);
}

void MB_WriteMultipleRegFunCode_10H(uint8_t _addr, uint16_t _reg, uint16_t _num0, uint16_t _num1)
{
    uint16_t TxCount = 0;
    uint16_t crc = 0;

    Tx_Buf[TxCount++] = _addr;            // 역주소에서
    Tx_Buf[TxCount++] = 0x10;             // 기능코드
    Tx_Buf[TxCount++] = _reg >> 8;        // 레지스터 주소 하이 바이트
    Tx_Buf[TxCount++] = _reg;             // 레지스터 주소 로우 바이트
    Tx_Buf[TxCount++] = 0x00;
    Tx_Buf[TxCount++] = 0x02;             // 0x0002 = register address 2개
    Tx_Buf[TxCount++] = 0x04;             // Number of bytes = 4

    Tx_Buf[TxCount++] = _num0 >> 8;       // High 8 bits of data 0
    Tx_Buf[TxCount++] = _num0;
    Tx_Buf[TxCount++] = _num1 >> 8;       // High 8 bits of data 1
    Tx_Buf[TxCount++] = _num1;

    crc = MB_CRC16((uint8_t*)&Tx_Buf, TxCount);
    Tx_Buf[TxCount++] = crc;              // crc 로우 바이트
    Tx_Buf[TxCount++] = crc >> 8;         // crc 하이 바이트

    digitalWrite(Tx1Pin, HIGH);
    for (uint8_t i = 0 ; i < 13 ; i++)
    {
        Serial1.write(Tx_Buf[i]);
    }
    digitalWrite(Tx1Pin, LOW);
}

// 모터 제어를 위한 데이터 송신
/*
    //Left motor encoder counter
    void encoderLeftMotor() {
    if (digitalRead(PIN_ENCOD_A_MOTOR_LEFT) == digitalRead(PIN_ENCOD_B_MOTOR_LEFT)) pos_left++;
    else pos_left--;
    }

    //Right motor encoder counter
    void encoderRightMotor() {
    if (digitalRead(PIN_ENCOD_A_MOTOR_RIGHT) == digitalRead(PIN_ENCOD_B_MOTOR_RIGHT)) pos_right--;
    else pos_right++;
    }

    // setup에 위치
    // Define the rotary encoder for left motor
    pinMode(PIN_ENCOD_A_MOTOR_LEFT, INPUT);
    pinMode(PIN_ENCOD_B_MOTOR_LEFT, INPUT);
    digitalWrite(PIN_ENCOD_A_MOTOR_LEFT, HIGH);                // turn on pullup resistor
    digitalWrite(PIN_ENCOD_B_MOTOR_LEFT, HIGH);
    attachInterrupt(0, encoderLeftMotor, RISING);
    attachInterrupt(1, encoderRightMotor, RISING);

*/
// ob+ ob- oa+ oa- 구분하기

// 엔코더 데이터를 저장하여 rosserial로 송신해야함

// ebimu. 데이터를 수신해서
// gmapping에 필요한 데이터로 계산하여 저장하여 rosserial로 송신해야함.

// dealy 0.00030381sec (0.30381msec)
