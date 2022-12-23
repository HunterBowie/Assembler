#include <avr/pgmspace.h>

#define RUN_PROGRAM 3

#define PROGRAM_LARGE_CODE 0
#define PROGRAM_LARGE_CONTROL 1
#define PROGRAM_SMALL_NUMBERS 2
#define PROGRAM_SMALL_CODE 3


#define LATCH_PIN 2
#define DATA_SERIAL_PIN 3
#define DATA_CLOCK_PIN 4
#define ADRESS_SERIAL_PIN 5
#define ADRESS_CLOCK_PIN 6
#define SMALL_WRITE_PIN 7
#define LARGE_WRITE_PIN 8

int SELECTED_EEPROM_PIN = 0;

int get_digit(int num, int digit) {

  if (digit == 0) {
    return num % 10;
  }
  if (digit == 1) {
    return  int((num % 100) / 10);
  }
  if (digit == 2) {
    return int((num % 1000) / 100);
  }
}


void highPulse(int PIN) {
  digitalWrite(PIN, HIGH);
  delay(1);
  digitalWrite(PIN, LOW);
  delay(1);
}

void lowPulse(int PIN) {
  digitalWrite(PIN, LOW);
  delay(1);
  digitalWrite(PIN, HIGH);
  delay(1);
}

void shiftOut(byte data, unsigned short SERIAL_PIN, unsigned short CLOCK_PIN) {
//  Serial.print("shifting: ");
//  Serial.println(data, BIN);
  for (int i = 7; i >= 0; i--) {
    int bit = bitRead(data, i);
    if (bit == 0) {
      digitalWrite(SERIAL_PIN, LOW);
    }
    else {
      digitalWrite(SERIAL_PIN, HIGH);
    }
    highPulse(CLOCK_PIN);
  }
}


// set 8 bit data
void setData(byte data) {
  shiftOut(data, DATA_SERIAL_PIN, DATA_CLOCK_PIN);
}

// sets 16 bit adress
void setAddress(unsigned int address) { // 00000000 00000001
  shiftOut(byte(address), ADRESS_SERIAL_PIN, ADRESS_CLOCK_PIN);
  shiftOut(address>>8, ADRESS_SERIAL_PIN, ADRESS_CLOCK_PIN);

}

void writeEEPROM(unsigned int address, byte data) {
  setAddress(address);
  setData(data);
  highPulse(LATCH_PIN);
  lowPulse(SELECTED_EEPROM_PIN);

  Serial.print("address: ");
  Serial.print(address, BIN);
  Serial.print("  data: ");
  Serial.println(data, BIN);

  
}



void programEEPROM_code(){
  

  //@INSERT_START
writeEEPROM(0, 2);
writeEEPROM(1, 0);
writeEEPROM(2, 3);
writeEEPROM(3, 247);
writeEEPROM(4, 2);
writeEEPROM(5, 0);
writeEEPROM(6, 3);
writeEEPROM(7, 246);
writeEEPROM(8, 16);
writeEEPROM(9, 46);
writeEEPROM(10, 12);
writeEEPROM(11, 0);
writeEEPROM(12, 3);
writeEEPROM(13, 247);
writeEEPROM(14, 16);
writeEEPROM(15, 20);
writeEEPROM(16, 8);
writeEEPROM(17, 10);
writeEEPROM(18, 31);
writeEEPROM(19, 0);
writeEEPROM(20, 16);
writeEEPROM(21, 68);
writeEEPROM(22, 1);
writeEEPROM(23, 247);
writeEEPROM(24, 7);
writeEEPROM(25, 0);
writeEEPROM(26, 11);
writeEEPROM(27, 38);
writeEEPROM(28, 8);
writeEEPROM(29, 30);
writeEEPROM(30, 16);
writeEEPROM(31, 82);
writeEEPROM(32, 2);
writeEEPROM(33, 48);
writeEEPROM(34, 14);
writeEEPROM(35, 0);
writeEEPROM(36, 17);
writeEEPROM(37, 0);
writeEEPROM(38, 16);
writeEEPROM(39, 96);
writeEEPROM(40, 2);
writeEEPROM(41, 48);
writeEEPROM(42, 14);
writeEEPROM(43, 0);
writeEEPROM(44, 17);
writeEEPROM(45, 0);
writeEEPROM(46, 2);
writeEEPROM(47, 0);
writeEEPROM(48, 15);
writeEEPROM(49, 0);
writeEEPROM(50, 2);
writeEEPROM(51, 56);
writeEEPROM(52, 14);
writeEEPROM(53, 0);
writeEEPROM(54, 2);
writeEEPROM(55, 12);
writeEEPROM(56, 14);
writeEEPROM(57, 0);
writeEEPROM(58, 2);
writeEEPROM(59, 1);
writeEEPROM(60, 14);
writeEEPROM(61, 0);
writeEEPROM(62, 2);
writeEEPROM(63, 1);
writeEEPROM(64, 15);
writeEEPROM(65, 0);
writeEEPROM(66, 17);
writeEEPROM(67, 0);
writeEEPROM(68, 2);
writeEEPROM(69, 0);
writeEEPROM(70, 15);
writeEEPROM(71, 0);
writeEEPROM(72, 2);
writeEEPROM(73, 1);
writeEEPROM(74, 14);
writeEEPROM(75, 0);
writeEEPROM(76, 2);
writeEEPROM(77, 1);
writeEEPROM(78, 15);
writeEEPROM(79, 0);
writeEEPROM(80, 17);
writeEEPROM(81, 0);
writeEEPROM(82, 2);
writeEEPROM(83, 0);
writeEEPROM(84, 15);
writeEEPROM(85, 0);
writeEEPROM(86, 2);
writeEEPROM(87, 192);
writeEEPROM(88, 14);
writeEEPROM(89, 0);
writeEEPROM(90, 2);
writeEEPROM(91, 1);
writeEEPROM(92, 15);
writeEEPROM(93, 0);
writeEEPROM(94, 17);
writeEEPROM(95, 0);
writeEEPROM(96, 2);
writeEEPROM(97, 0);
writeEEPROM(98, 15);
writeEEPROM(99, 0);
writeEEPROM(100, 2);
writeEEPROM(101, 2);
writeEEPROM(102, 14);
writeEEPROM(103, 0);
writeEEPROM(104, 2);
writeEEPROM(105, 1);
writeEEPROM(106, 15);
writeEEPROM(107, 0);
writeEEPROM(108, 17);
writeEEPROM(109, 0);
writeEEPROM(110, 0);
writeEEPROM(111, 0);
writeEEPROM(112, 0);
writeEEPROM(113, 0);
writeEEPROM(114, 0);
writeEEPROM(115, 0);
writeEEPROM(116, 0);
writeEEPROM(117, 0);
writeEEPROM(118, 0);
writeEEPROM(119, 0);
writeEEPROM(120, 0);
writeEEPROM(121, 0);
writeEEPROM(122, 0);
writeEEPROM(123, 0);
writeEEPROM(124, 0);
writeEEPROM(125, 0);
writeEEPROM(126, 0);
writeEEPROM(127, 0);
writeEEPROM(128, 0);
writeEEPROM(129, 0);
writeEEPROM(130, 0);
writeEEPROM(131, 0);
writeEEPROM(132, 0);
writeEEPROM(133, 0);
writeEEPROM(134, 0);
writeEEPROM(135, 0);
writeEEPROM(136, 0);
writeEEPROM(137, 0);
writeEEPROM(138, 0);
writeEEPROM(139, 0);
writeEEPROM(140, 0);
writeEEPROM(141, 0);
writeEEPROM(142, 0);
writeEEPROM(143, 0);
writeEEPROM(144, 0);
writeEEPROM(145, 0);
writeEEPROM(146, 0);
writeEEPROM(147, 0);
writeEEPROM(148, 0);
writeEEPROM(149, 0);
writeEEPROM(150, 0);
writeEEPROM(151, 0);
writeEEPROM(152, 0);
writeEEPROM(153, 0);
writeEEPROM(154, 0);
writeEEPROM(155, 0);
writeEEPROM(156, 0);
writeEEPROM(157, 0);
writeEEPROM(158, 0);
writeEEPROM(159, 0);
writeEEPROM(160, 0);
writeEEPROM(161, 0);
writeEEPROM(162, 0);
writeEEPROM(163, 0);
writeEEPROM(164, 0);
writeEEPROM(165, 0);
writeEEPROM(166, 0);
writeEEPROM(167, 0);
writeEEPROM(168, 0);
writeEEPROM(169, 0);
writeEEPROM(170, 0);
writeEEPROM(171, 0);
writeEEPROM(172, 0);
writeEEPROM(173, 0);
writeEEPROM(174, 0);
writeEEPROM(175, 0);
writeEEPROM(176, 0);
writeEEPROM(177, 0);
writeEEPROM(178, 0);
writeEEPROM(179, 0);
writeEEPROM(180, 0);
writeEEPROM(181, 0);
writeEEPROM(182, 0);
writeEEPROM(183, 0);
writeEEPROM(184, 0);
writeEEPROM(185, 0);
writeEEPROM(186, 0);
writeEEPROM(187, 0);
writeEEPROM(188, 0);
writeEEPROM(189, 0);
writeEEPROM(190, 0);
writeEEPROM(191, 0);
writeEEPROM(192, 0);
writeEEPROM(193, 0);
writeEEPROM(194, 0);
writeEEPROM(195, 0);
writeEEPROM(196, 0);
writeEEPROM(197, 0);
writeEEPROM(198, 0);
writeEEPROM(199, 0);
writeEEPROM(200, 0);
writeEEPROM(201, 0);
writeEEPROM(202, 0);
writeEEPROM(203, 0);
writeEEPROM(204, 0);
writeEEPROM(205, 0);
writeEEPROM(206, 0);
writeEEPROM(207, 0);
writeEEPROM(208, 0);
writeEEPROM(209, 0);
writeEEPROM(210, 0);
writeEEPROM(211, 0);
writeEEPROM(212, 0);
writeEEPROM(213, 0);
writeEEPROM(214, 0);
writeEEPROM(215, 0);
writeEEPROM(216, 0);
writeEEPROM(217, 0);
writeEEPROM(218, 0);
writeEEPROM(219, 0);
writeEEPROM(220, 0);
writeEEPROM(221, 0);
writeEEPROM(222, 0);
writeEEPROM(223, 0);
writeEEPROM(224, 0);
writeEEPROM(225, 0);
writeEEPROM(226, 0);
writeEEPROM(227, 0);
writeEEPROM(228, 0);
writeEEPROM(229, 0);
writeEEPROM(230, 0);
writeEEPROM(231, 0);
writeEEPROM(232, 0);
writeEEPROM(233, 0);
writeEEPROM(234, 0);
writeEEPROM(235, 0);
writeEEPROM(236, 0);
writeEEPROM(237, 0);
writeEEPROM(238, 0);
writeEEPROM(239, 0);
writeEEPROM(240, 0);
writeEEPROM(241, 0);
writeEEPROM(242, 0);
writeEEPROM(243, 0);
writeEEPROM(244, 0);
writeEEPROM(245, 0);
writeEEPROM(246, 0);
writeEEPROM(247, 0);
writeEEPROM(248, 0);
writeEEPROM(249, 0);
writeEEPROM(250, 0);
writeEEPROM(251, 0);
writeEEPROM(252, 0);
writeEEPROM(253, 0);
writeEEPROM(254, 0);
writeEEPROM(255, 0);
//@INSERT_END
}





#define HLT     0b000000000000000000000001
#define PC_O    0b000000000000000000000010
#define PC_I    0b000000000000000000000100
#define PC_E    0b000000000000000000001000
#define F_I     0b000000000000000000010000
#define A_O     0b000000000000000000100000
#define A_I     0b000000000000000001000000
#define ALU_O   0b000000000000000010000000
#define ALU_C   0b000000000000000100000000
#define ALU_IB  0b000000000000001000000000
#define B_O     0b000000000000010000000000
#define B_I     0b000000000000100000000000
#define B_C     0b000000000001000000000000
#define MD_O    0b000000000010000000000000
#define MD_I    0b000000000100000000000000
#define MA_I    0b000000001000000000000000
#define I_I     0b000000010000000000000000
#define PX_I    0b000000100000000000000000
#define PY_I    0b000001000000000000000000
#define PX_O    0b000010000000000000000000
#define PY_O    0b000100000000000000000000
#define SP_O    0b001000000000000000000000
#define SP_I    0b010000000000000000000000
#define SP_E    0b100000000000000000000000
#define NUM_INSTRUCTIONS 32
#define NUM_CYCLES 6
#define NUM_FLAGS 8



const PROGMEM uint32_t INSTRUCTIONS[NUM_FLAGS][NUM_INSTRUCTIONS][NUM_CYCLES] = {
    { // Carry: 0 Negative: 0 Zero: 0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // NOP  0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|A_I|PC_E,  0},                               // LDA  1 
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|A_I|PC_E,              0,              0},                               // LDI  2
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_I|A_O|PC_E,  0},                               // STA  3
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_O|A_I|PC_E|F_I},              // ADD  4
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_C|ALU_IB|ALU_O|A_I|PC_E|F_I}, // SUB  5
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_C|A_I|PC_E|F_I,   0,              0},                               // INC  6
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_IB|A_I|PC_E|F_I,  0,              0},                               // DEC  7
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JMP  8
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JC   9
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JN   10
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JZ   11
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PX_I|PC_E,0,                          0,              0},                               // INX  12
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PY_I|PC_E,0,                          0,              0},                               // INY  13
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PX_O|PC_E,0,                          0,              0},                               // OUTX 14
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PY_O|PC_E,0,                          0,              0},                               // OUTY 15
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    PC_O|MD_I,                  SP_E|PC_O|MA_I, PC_I|MD_O},                       // CALL 16
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     MD_O|PC_I,      PC_E},                            // RET  17
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    A_O|MD_I|SP_E|PC_E,         0,              0},                               // PUSH 18
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     A_I|MD_O|PC_E,  0},                               // POP  19
    {0,         0,             0,            0,                          0,              0},                               // NULL 20
    {0,         0,             0,            0,                          0,              0},                               // NULL 21
    {0,         0,             0,            0,                          0,              0},                               // NULL 22
    {0,         0,             0,            0,                          0,              0},                               // NULL 23
    {0,         0,             0,            0,                          0,              0},                               // NULL 24
    {0,         0,             0,            0,                          0,              0},                               // NULL 25
    {0,         0,             0,            0,                          0,              0},                               // NULL 26
    {0,         0,             0,            0,                          0,              0},                               // NULL 27
    {0,         0,             0,            0,                          0,              0},                               // NULL 28
    {0,         0,             0,            0,                          0,              0},                               // NULL 29
    {0,         0,             0,            0,                          0,              0},                               // NULL 30
    {HLT,       0,             0,            0,                          0,              0},                               // HALT 31
    },
    { // Carry: 0 Negative: 0 Zero: 1
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // NOP  0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|A_I|PC_E,  0},                               // LDA  1 
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|A_I|PC_E,              0,              0},                               // LDI  2
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_I|A_O|PC_E,  0},                               // STA  3
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_O|A_I|PC_E|F_I},              // ADD  4
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_C|ALU_IB|ALU_O|A_I|PC_E|F_I}, // SUB  5
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_C|A_I|PC_E|F_I,   0,              0},                               // INC  6
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_IB|A_I|PC_E|F_I,  0,              0},                               // DEC  7
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JMP  8
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JC   9
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JN   10
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JZ   11
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PX_I|PC_E,0,                          0,              0},                               // INX  12
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PY_I|PC_E,0,                          0,              0},                               // INY  13
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PX_O|PC_E,0,                          0,              0},                               // OUTX 14
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PY_O|PC_E,0,                          0,              0},                               // OUTY 15
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    PC_O|MD_I,                  SP_E|PC_O|MA_I, PC_I|MD_O},                       // CALL 16
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     MD_O|PC_I,      PC_E},                            // RET  17
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    A_O|MD_I|SP_E|PC_E,         0,              0},                               // PUSH 18
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     A_I|MD_O|PC_E,  0},                               // POP  19
    {0,         0,             0,            0,                          0,              0},                               // NULL 20
    {0,         0,             0,            0,                          0,              0},                               // NULL 21
    {0,         0,             0,            0,                          0,              0},                               // NULL 22
    {0,         0,             0,            0,                          0,              0},                               // NULL 23
    {0,         0,             0,            0,                          0,              0},                               // NULL 24
    {0,         0,             0,            0,                          0,              0},                               // NULL 25
    {0,         0,             0,            0,                          0,              0},                               // NULL 26
    {0,         0,             0,            0,                          0,              0},                               // NULL 27
    {0,         0,             0,            0,                          0,              0},                               // NULL 28
    {0,         0,             0,            0,                          0,              0},                               // NULL 29
    {0,         0,             0,            0,                          0,              0},                               // NULL 30
    {HLT,       0,             0,            0,                          0,              0},                               // HALT 31
    },
    { // Carry: 0 Negative: 1 Zero: 0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // NOP  0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|A_I|PC_E,  0},                               // LDA  1 
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|A_I|PC_E,              0,              0},                               // LDI  2
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_I|A_O|PC_E,  0},                               // STA  3
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_O|A_I|PC_E|F_I},              // ADD  4
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_C|ALU_IB|ALU_O|A_I|PC_E|F_I}, // SUB  5
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_C|A_I|PC_E|F_I,   0,              0},                               // INC  6
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_IB|A_I|PC_E|F_I,  0,              0},                               // DEC  7
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JMP  8
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JC   9
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JN   10
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JZ   11
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PX_I|PC_E,0,                          0,              0},                               // INX  12
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PY_I|PC_E,0,                          0,              0},                               // INY  13
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PX_O|PC_E,0,                          0,              0},                               // OUTX 14
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PY_O|PC_E,0,                          0,              0},                               // OUTY 15
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    PC_O|MD_I,                  SP_E|PC_O|MA_I, PC_I|MD_O},                       // CALL 16
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     MD_O|PC_I,      PC_E},                            // RET  17
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    A_O|MD_I|SP_E|PC_E,         0,              0},                               // PUSH 18
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     A_I|MD_O|PC_E,  0},                               // POP  19
    {0,         0,             0,            0,                          0,              0},                               // NULL 20
    {0,         0,             0,            0,                          0,              0},                               // NULL 21
    {0,         0,             0,            0,                          0,              0},                               // NULL 22
    {0,         0,             0,            0,                          0,              0},                               // NULL 23
    {0,         0,             0,            0,                          0,              0},                               // NULL 24
    {0,         0,             0,            0,                          0,              0},                               // NULL 25
    {0,         0,             0,            0,                          0,              0},                               // NULL 26
    {0,         0,             0,            0,                          0,              0},                               // NULL 27
    {0,         0,             0,            0,                          0,              0},                               // NULL 28
    {0,         0,             0,            0,                          0,              0},                               // NULL 29
    {0,         0,             0,            0,                          0,              0},                               // NULL 30
    {HLT,       0,             0,            0,                          0,              0},                               // HALT 31
    },
    { // Carry: 0 Negative: 1 Zero: 1
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // NOP  0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|A_I|PC_E,  0},                               // LDA  1 
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|A_I|PC_E,              0,              0},                               // LDI  2
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_I|A_O|PC_E,  0},                               // STA  3
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_O|A_I|PC_E|F_I},              // ADD  4
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_C|ALU_IB|ALU_O|A_I|PC_E|F_I}, // SUB  5
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_C|A_I|PC_E|F_I,   0,              0},                               // INC  6
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_IB|A_I|PC_E|F_I,  0,              0},                               // DEC  7
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JMP  8
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JC   9
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JN   10
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JZ   11
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PX_I|PC_E,0,                          0,              0},                               // INX  12
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PY_I|PC_E,0,                          0,              0},                               // INY  13
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PX_O|PC_E,0,                          0,              0},                               // OUTX 14
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PY_O|PC_E,0,                          0,              0},                               // OUTY 15
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    PC_O|MD_I,                  SP_E|PC_O|MA_I, PC_I|MD_O},                       // CALL 16
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     MD_O|PC_I,      PC_E},                            // RET  17
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    A_O|MD_I|SP_E|PC_E,         0,              0},                               // PUSH 18
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     A_I|MD_O|PC_E,  0},                               // POP  19
    {0,         0,             0,            0,                          0,              0},                               // NULL 20
    {0,         0,             0,            0,                          0,              0},                               // NULL 21
    {0,         0,             0,            0,                          0,              0},                               // NULL 22
    {0,         0,             0,            0,                          0,              0},                               // NULL 23
    {0,         0,             0,            0,                          0,              0},                               // NULL 24
    {0,         0,             0,            0,                          0,              0},                               // NULL 25
    {0,         0,             0,            0,                          0,              0},                               // NULL 26
    {0,         0,             0,            0,                          0,              0},                               // NULL 27
    {0,         0,             0,            0,                          0,              0},                               // NULL 28
    {0,         0,             0,            0,                          0,              0},                               // NULL 29
    {0,         0,             0,            0,                          0,              0},                               // NULL 30
    {HLT,       0,             0,            0,                          0,              0},                               // HALT 31
    },
    { // Carry: 1 Negative: 0 Zero: 0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // NOP  0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|A_I|PC_E,  0},                               // LDA  1 
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|A_I|PC_E,              0,              0},                               // LDI  2
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_I|A_O|PC_E,  0},                               // STA  3
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_O|A_I|PC_E|F_I},              // ADD  4
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_C|ALU_IB|ALU_O|A_I|PC_E|F_I}, // SUB  5
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_C|A_I|PC_E|F_I,   0,              0},                               // INC  6
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_IB|A_I|PC_E|F_I,  0,              0},                               // DEC  7
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JMP  8
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JC   9
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JN   10
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JZ   11
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PX_I|PC_E,0,                          0,              0},                               // INX  12
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PY_I|PC_E,0,                          0,              0},                               // INY  13
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PX_O|PC_E,0,                          0,              0},                               // OUTX 14
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PY_O|PC_E,0,                          0,              0},                               // OUTY 15
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    PC_O|MD_I,                  SP_E|PC_O|MA_I, PC_I|MD_O},                       // CALL 16
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     MD_O|PC_I,      PC_E},                            // RET  17
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    A_O|MD_I|SP_E|PC_E,         0,              0},                               // PUSH 18
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     A_I|MD_O|PC_E,  0},                               // POP  19
    {0,         0,             0,            0,                          0,              0},                               // NULL 20
    {0,         0,             0,            0,                          0,              0},                               // NULL 21
    {0,         0,             0,            0,                          0,              0},                               // NULL 22
    {0,         0,             0,            0,                          0,              0},                               // NULL 23
    {0,         0,             0,            0,                          0,              0},                               // NULL 24
    {0,         0,             0,            0,                          0,              0},                               // NULL 25
    {0,         0,             0,            0,                          0,              0},                               // NULL 26
    {0,         0,             0,            0,                          0,              0},                               // NULL 27
    {0,         0,             0,            0,                          0,              0},                               // NULL 28
    {0,         0,             0,            0,                          0,              0},                               // NULL 29
    {0,         0,             0,            0,                          0,              0},                               // NULL 30
    {HLT,       0,             0,            0,                          0,              0},                               // HALT 31
    },
    { // Carry: 1 Negative: 0 Zero: 1
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // NOP  0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|A_I|PC_E,  0},                               // LDA  1 
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|A_I|PC_E,              0,              0},                               // LDI  2
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_I|A_O|PC_E,  0},                               // STA  3
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_O|A_I|PC_E|F_I},              // ADD  4
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_C|ALU_IB|ALU_O|A_I|PC_E|F_I}, // SUB  5
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_C|A_I|PC_E|F_I,   0,              0},                               // INC  6
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_IB|A_I|PC_E|F_I,  0,              0},                               // DEC  7
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JMP  8
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JC   9
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JN   10
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JZ   11
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PX_I|PC_E,0,                          0,              0},                               // INX  12
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PY_I|PC_E,0,                          0,              0},                               // INY  13
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PX_O|PC_E,0,                          0,              0},                               // OUTX 14
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PY_O|PC_E,0,                          0,              0},                               // OUTY 15
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    PC_O|MD_I,                  SP_E|PC_O|MA_I, PC_I|MD_O},                       // CALL 16
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     MD_O|PC_I,      PC_E},                            // RET  17
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    A_O|MD_I|SP_E|PC_E,         0,              0},                               // PUSH 18
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     A_I|MD_O|PC_E,  0},                               // POP  19
    {0,         0,             0,            0,                          0,              0},                               // NULL 20
    {0,         0,             0,            0,                          0,              0},                               // NULL 21
    {0,         0,             0,            0,                          0,              0},                               // NULL 22
    {0,         0,             0,            0,                          0,              0},                               // NULL 23
    {0,         0,             0,            0,                          0,              0},                               // NULL 24
    {0,         0,             0,            0,                          0,              0},                               // NULL 25
    {0,         0,             0,            0,                          0,              0},                               // NULL 26
    {0,         0,             0,            0,                          0,              0},                               // NULL 27
    {0,         0,             0,            0,                          0,              0},                               // NULL 28
    {0,         0,             0,            0,                          0,              0},                               // NULL 29
    {0,         0,             0,            0,                          0,              0},                               // NULL 30
    {HLT,       0,             0,            0,                          0,              0},                               // HALT 31
    },
    { // Carry: 1 Negative: 1 Zero: 0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // NOP  0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|A_I|PC_E,  0},                               // LDA  1 
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|A_I|PC_E,              0,              0},                               // LDI  2
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_I|A_O|PC_E,  0},                               // STA  3
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_O|A_I|PC_E|F_I},              // ADD  4
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_C|ALU_IB|ALU_O|A_I|PC_E|F_I}, // SUB  5
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_C|A_I|PC_E|F_I,   0,              0},                               // INC  6
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_IB|A_I|PC_E|F_I,  0,              0},                               // DEC  7
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JMP  8
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JC   9
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JN   10
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // JZ   11
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PX_I|PC_E,0,                          0,              0},                               // INX  12
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PY_I|PC_E,0,                          0,              0},                               // INY  13
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PX_O|PC_E,0,                          0,              0},                               // OUTX 14
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PY_O|PC_E,0,                          0,              0},                               // OUTY 15
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    PC_O|MD_I,                  SP_E|PC_O|MA_I, PC_I|MD_O},                       // CALL 16
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     MD_O|PC_I,      PC_E},                            // RET  17
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    A_O|MD_I|SP_E|PC_E,         0,              0},                               // PUSH 18
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     A_I|MD_O|PC_E,  0},                               // POP  19
    {0,         0,             0,            0,                          0,              0},                               // NULL 20
    {0,         0,             0,            0,                          0,              0},                               // NULL 21
    {0,         0,             0,            0,                          0,              0},                               // NULL 22
    {0,         0,             0,            0,                          0,              0},                               // NULL 23
    {0,         0,             0,            0,                          0,              0},                               // NULL 24
    {0,         0,             0,            0,                          0,              0},                               // NULL 25
    {0,         0,             0,            0,                          0,              0},                               // NULL 26
    {0,         0,             0,            0,                          0,              0},                               // NULL 27
    {0,         0,             0,            0,                          0,              0},                               // NULL 28
    {0,         0,             0,            0,                          0,              0},                               // NULL 29
    {0,         0,             0,            0,                          0,              0},                               // NULL 30
    {HLT,       0,             0,            0,                          0,              0},                               // HALT 31
    },
    { // Carry: 1 Negative: 1 Zero: 1
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_E,         0,                          0,              0},                               // NOP  0
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|A_I|PC_E,  0},                               // LDA  1 
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|A_I|PC_E,              0,              0},                               // LDI  2
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_I|A_O|PC_E,  0},                               // STA  3
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_O|A_I|PC_E|F_I},              // ADD  4
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|MA_I,                  MD_O|B_I,       ALU_C|ALU_IB|ALU_O|A_I|PC_E|F_I}, // SUB  5
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_C|A_I|PC_E|F_I,   0,              0},                               // INC  6
    {PC_O|MA_I, PC_E|MD_O|I_I, B_C,          ALU_O|ALU_IB|A_I|PC_E|F_I,  0,              0},                               // DEC  7
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JMP  8
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JC   9
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JN   10
    {PC_O|MA_I, PC_E|MD_O|I_I, PC_O|MA_I,    MD_O|PC_I,                  0,              0},                               // JZ   11
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PX_I|PC_E,0,                          0,              0},                               // INX  12
    {PC_O|MA_I, PC_E|MD_O|I_I, A_I|PY_I|PC_E,0,                          0,              0},                               // INY  13
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PX_O|PC_E,0,                          0,              0},                               // OUTX 14
    {PC_O|MA_I, PC_E|MD_O|I_I, A_O|PY_O|PC_E,0,                          0,              0},                               // OUTY 15
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    PC_O|MD_I,                  SP_E|PC_O|MA_I, PC_I|MD_O},                       // CALL 16
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     MD_O|PC_I,      PC_E},                            // RET  17
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|MA_I,    A_O|MD_I|SP_E|PC_E,         0,              0},                               // PUSH 18
    {PC_O|MA_I, PC_E|MD_O|I_I, SP_O|A_I|B_C, ALU_IB|ALU_O|SP_I|MA_I,     A_I|MD_O|PC_E,  0},                               // POP  19
    {0,         0,             0,            0,                          0,              0},                               // NULL 20
    {0,         0,             0,            0,                          0,              0},                               // NULL 21
    {0,         0,             0,            0,                          0,              0},                               // NULL 22
    {0,         0,             0,            0,                          0,              0},                               // NULL 23
    {0,         0,             0,            0,                          0,              0},                               // NULL 24
    {0,         0,             0,            0,                          0,              0},                               // NULL 25
    {0,         0,             0,            0,                          0,              0},                               // NULL 26
    {0,         0,             0,            0,                          0,              0},                               // NULL 27
    {0,         0,             0,            0,                          0,              0},                               // NULL 28
    {0,         0,             0,            0,                          0,              0},                               // NULL 29
    {0,         0,             0,            0,                          0,              0},                               // NULL 30
    {HLT,       0,             0,            0,                          0,              0},                               // HALT 31
    }
    
};


void programEEPROM_control() {

  // Control Logic
  Serial.println("programming Large EEPROM");

 
  

  for (int address = 0; address < 8191; address += 1){
    int select =      (address & 0b1100000000000) >> 11;
    int flags =       (address & 0b0011100000000) >> 8;
    int instruction = (address & 0b0000011111000) >> 3;
    int cycle =       (address & 0b0000000000111);
 
    
    byte RIGHT_EEPROM =  pgm_read_dword(&(INSTRUCTIONS[flags][instruction][cycle])) & 0b11111111;
    byte MIDDLE_EEPROM =(pgm_read_dword(&(INSTRUCTIONS[flags][instruction][cycle])) >> 8) & 0b11111111;
    byte LEFT_EEPROM =   pgm_read_dword(&(INSTRUCTIONS[flags][instruction][cycle])) >> 16;

    switch (select) {
      case 0:
        writeEEPROM(address, RIGHT_EEPROM);
        break;
        
      case 1:
        writeEEPROM(address, MIDDLE_EEPROM);
        break;
        
      case 2:
        writeEEPROM(address, LEFT_EEPROM);
        break;
        
      case 3:
        continue;
    }
    
}
    

  
}



void programEEPROM_numbers() {
  
//  byte numbers[] = {0b01111110, 0b00110000, 0b01101101, 0b01111001, 0b00110011, 0b01011011, 0b01011111, 0b01110000, 0b01111111, 0b01111011};

  int numbers[] = {126, 48, 109, 121, 51, 91, 95, 112, 127, 123};


    
  Serial.println("Programming ones place");
  for (int adress = 0; adress <= 255; adress += 1) {
    writeEEPROM(adress, numbers[get_digit(adress, 0)]);
  }
  Serial.println("Programming tens place");
  for (int adress = 0; adress <= 255; adress += 1) {
    if (adress > 9) {
      writeEEPROM(adress+256, numbers[get_digit(adress, 1)]);
    }
    else {
      writeEEPROM(adress+256, 0);
    }
    
  }
  Serial.println("Programming hundreds place");
  for (int adress = 0; adress <= 255; adress += 1) {
     if (adress > 99) {
      writeEEPROM(adress+512, numbers[get_digit(adress, 2)]);
    }
    else {
      writeEEPROM(adress+512, 0);
    }
  }
  Serial.println("Programming sign");
  for (int adress = 0; adress <= 255; adress += 1) {
    writeEEPROM(adress + 768, 0);
  }

//  Serial.println("Programming ones place (twos complement)");
//  for (int adress = -128; adress <= 127; adress += 1) {
//    writeEEPROM(adress + 1024, numbers[get_digit(abs(adress), 0)]);
//  }
//  Serial.println("Programming tens place (twos complement)");
//  for (int adress = -128; adress <= 127; adress += 1) {
//    writeEEPROM(adress + 1280, numbers[get_digit(abs(adress), 1)]);
//  }
//  Serial.println("Programming hundreds place (twos complement)");
//  for (int adress = -128; adress <= 127; adress += 1) {
//    writeEEPROM(adress + 1536, numbers[get_digit(abs(adress), 2)]);
//  }
//  Serial.println("Programming sign (twos complement)");
//  for (int adress = -128; adress <= 127; adress += 1) {
//    if (adress < 0) {
//      writeEEPROM(adress + 1792, 1);
//    } else {
//      writeEEPROM(adress + 1792, 0);
//    }
//  }


  
  
  
}

void setup() {
  Serial.begin(57600);
  pinMode(DATA_CLOCK_PIN, OUTPUT);
  pinMode(DATA_SERIAL_PIN, OUTPUT);
  pinMode(ADRESS_CLOCK_PIN, OUTPUT);
  pinMode(ADRESS_SERIAL_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(SMALL_WRITE_PIN, OUTPUT);
  pinMode(LARGE_WRITE_PIN, OUTPUT);

  digitalWrite(SMALL_WRITE_PIN, HIGH);
  digitalWrite(LARGE_WRITE_PIN, HIGH);

  Serial.println("starting ...");
  if (RUN_PROGRAM == PROGRAM_LARGE_CODE) {
      SELECTED_EEPROM_PIN = LARGE_WRITE_PIN;
    Serial.println("program type: code, EEPROM size: large");
    programEEPROM_code();
  }
  else if (RUN_PROGRAM == PROGRAM_LARGE_CONTROL) {
     SELECTED_EEPROM_PIN = LARGE_WRITE_PIN;
    Serial.println("program type: control, EEPROM size: large");
    programEEPROM_control();
  }
  else if (RUN_PROGRAM == PROGRAM_SMALL_NUMBERS) {
    SELECTED_EEPROM_PIN = SMALL_WRITE_PIN;
    Serial.println("program type: numbers, EEPROM size: small");
    programEEPROM_numbers();
  }
  else if (RUN_PROGRAM == PROGRAM_SMALL_CODE) {
    SELECTED_EEPROM_PIN = SMALL_WRITE_PIN;
    Serial.println("program type: code, EEPROM size: small");
    programEEPROM_code();
  }

  else {
    Serial.println("ERROR: WRONG PROGRAM CODE!!!");
  }
  

  Serial.println("*---------- done ----------*");



}

void loop() {
}
