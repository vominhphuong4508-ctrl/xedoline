#ifndef dongco
#define dongco 
#include <Arduino.h>

// Bổ sung dấu chấm phẩy (;) bị thiếu ở cuối khai báo extern
extern const uint8_t AIN1;
extern const uint8_t AIN2;
extern const uint8_t PWMA;
extern const uint8_t BIN1;
extern const uint8_t BIN2;
extern const uint8_t PWMB;

void khoitaoMotor(); 
void setLeftMotor(int speed);
void setRightMotor(int speed);
void setMotors(int leftSpeed, int rightSpeed);
#endif