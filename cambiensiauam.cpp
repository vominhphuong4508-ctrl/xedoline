#include "cambiensieuam.h"

// Thay số chân thực tế của bạn
const uint8_t TRIG_PIN = 32; 
const uint8_t ECHO_PIN = 35;
const unsigned long ECHO_TIMEOUT_US = 23200UL;

void khoiTaoSieuAm() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

// Chú ý: Dùng 'float' thay vì 'void' vì hàm này trả về kết quả
float dokhoancach() {
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
  unsigned long  realduration = (duration  * (1000 + 2000))/ 2000;
  if (realduration == 0) return 0;
  return realduration * 0.034 / 2;
}