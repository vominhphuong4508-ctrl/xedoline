#include "dongco.h"
 const uint8_t AIN1 = 17; 
const uint8_t AIN2 = 16; 
const uint8_t PWMA = 4;  

const uint8_t BIN1 = 5;  
const uint8_t BIN2 = 18; 
const uint8_t PWMB = 19; 

void khoitaoMotor() {
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT); pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT); pinMode(PWMB, OUTPUT);
  setMotors(0, 0);
} // Đã thêm dấu } bị thiếu để đóng hàm khởi tạo

void setLeftMotor(int speed) {
  if (speed >= 0) {
    digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW); analogWrite(PWMA, speed);
  } else {
    digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH); analogWrite(PWMA, -speed); 
  }
}

void setRightMotor(int speed) {
  if (speed >= 0) {
    digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW); analogWrite(PWMB, speed);
  } else {
    digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH); analogWrite(PWMB, -speed); 
  }
}

// Hàm gộp điều khiển 2 bánh cùng lúc cho tiện
void setMotors(int leftSpeed, int rightSpeed) {
  setLeftMotor(leftSpeed);
  setRightMotor(rightSpeed);
}