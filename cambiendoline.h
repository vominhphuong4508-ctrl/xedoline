#ifndef cambiendoine
#define cambiendoine
#include <Arduino.h>

#define SENSOR_COUNT 5
extern const uint8_t SENSOR_PINS[SENSOR_COUNT]; 
extern const uint8_t EN_PIN;
extern const uint16_t CENTER_POSITION;

extern uint16_t sensorValues[SENSOR_COUNT]; // Đảm bảo mảng này được extern để file chính xài được

void khoiTaoQTR();
void hieuchinhqtr();
int docvitri();
int saiso();

bool kiemTraNhacBong(); 
bool kiemTraMatLine();  

// ================= THÊM MỚI TỪ ĐÂY =================
// Định nghĩa các loại hình thái đường đi
enum LoaiNgaRe {
  DUONG_THANG,
  GOC_VUONG_PHAI,
  GOC_VUONG_TRAI,
  NGA_BA_CHU_Y
};

LoaiNgaRe nhanDienNgaRe();
// ===================================================

#endif