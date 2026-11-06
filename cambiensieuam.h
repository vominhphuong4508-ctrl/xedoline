#ifndef CAMBIENSIEUAM_H
#define CAMBIENSIEUAM_H

#include <Arduino.h> // Bắt buộc phải có dòng này

extern const uint8_t TRIG_PIN;
extern const uint8_t ECHO_PIN;
extern const unsigned long ECHO_TIMEOUT_US;

void khoiTaoSieuAm(); // Hàm chứa pinMode
float dokhoancach();

#endif