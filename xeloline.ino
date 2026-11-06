#include "cambiensieuam.h"
#include "cambiendoline.h"
#include "dongco.h"
#include <Arduino.h>
#include <QTRSensors.h>
#include <esp_wifi.h>

float Kp = 0.08;   
float Ki = 0.0001; 
float Kd = 0.6;    

int baseSpeed = 160;  
int maxSpeed  = 200;

int lastError = 0;
float integral = 0;

int tocDoGiam = 90;      
int tocDoRePhai = 110;   
int tocDoReTrai = 110;   

void setup() {
  Serial.begin(115200);
  khoiTaoSieuAm();
  khoiTaoQTR();
  hieuchinhqtr();
  khoitaoMotor();
  delay(2000);
}
void loop() {

 docvitri();
 if (kiemTraNhacBong() == true) {
    delay (700);
    setMotors(0, 0);
    return; // Bỏ qua PID
  }
  
  if (kiemTraMatLine() == true) {
    setMotors(60, 60);
    delay(20);
  
    docvitri(); 
    
    while (kiemTraMatLine() == true) {
      if (lastError > 0) {
      
      } else {
        setMotors(-130, 130); 
      }
      
      docvitri(); 
    }
  }


  LoaiNgaRe tinhTrangDuong = nhanDienNgaRe();

 
  if (tinhTrangDuong == NGA_BA_CHU_Y || tinhTrangDuong == GOC_VUONG_PHAI) {
    
    setMotors(tocDoGiam, tocDoGiam);
    delay(25); // Nhích tới tâm ngã rẽ
    
    while (true) {
      setMotors(tocDoRePhai, -tocDoRePhai); // Xoay compass sang phải
      docvitri(); // Chớp mắt đọc liên tục
      
      // Thoát kịch bản nếu mắt giữa (3) thấy đen và mắt trái (1) thoát line
      if (sensorValues[2] > 500 && sensorValues[0] < 400) break; 
    }
    
    lastError = saiso(); 
    return; // Nhường quyền lại cho PID
  }
  
  // KỊCH BẢN 2: Chỉ có đường rẽ trái (Góc vuông trái)
  else if (tinhTrangDuong == GOC_VUONG_TRAI) {
    Serial.println("Phat hien Goc Trai -> Re Trai!");
    
    setMotors(tocDoGiam, tocDoGiam);
    delay(25); 
    
    while (true) {
      setMotors(-tocDoReTrai, tocDoReTrai); // Xoay compass sang trái
      docvitri();
      
      // Thoát kịch bản nếu mắt giữa (3) thấy đen và mắt phải (5) thoát line
      if (sensorValues[2] > 500 && sensorValues[4] < 400) break; 
    }
    
    lastError = saiso();
    return;
  }

/// khung pid 
  int error = saiso();
  float P = error;
  integral += error;
  integral = constrain(integral, -10000, 10000); // Tránh tràn biến tích phân
  float D = error - lastError;

  float motorSpeedDifference = (Kp * P) + (Ki * integral) + (Kd * D);
  lastError = saiso();

  int leftmotorspeed = baseSpeed + motorSpeedDifference;
  int rightmotorspeed = baseSpeed - motorSpeedDifference;
  
  setMotors(leftmotorspeed, rightmotorspeed);
  delay(20);
}
  
 


