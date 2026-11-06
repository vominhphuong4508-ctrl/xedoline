#include "cambiendoline.h"
#include <QTRSensors.h> // Bắt buộc phải có thư viện này

QTRSensors qtr; // Khởi tạo bộ não cho cảm biến

// Thay số chân thực tế của bạn
const uint8_t SENSOR_PINS[SENSOR_COUNT] = {12, 14, 27, 26, 25};
const uint8_t EN_PIN = 33; 
const uint16_t CENTER_POSITION = 2000;

uint16_t sensorValues[SENSOR_COUNT];
int currentPosition = 0; // Biến dùng chung để lưu vị trí hiện tại

void khoiTaoQTR() {
  pinMode(EN_PIN, OUTPUT);
  qtr.setTypeRC(); // Khai báo loại cảm biến RC
  qtr.setSensorPins(SENSOR_PINS, SENSOR_COUNT); // Nạp danh sách chân vào thư viện
}

void hieuchinhqtr() {
  Serial.begin(115200);
  
  digitalWrite(EN_PIN, HIGH); // Sửa chữ A thành a thường, thêm dấu chấm phẩy
  
  for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();
  }
}

// Chú ý: Dùng 'int' thay vì 'voidt'
int docvitri() {
  digitalWrite(EN_PIN, HIGH); 
  
  // Đọc và lưu vào biến chung currentPosition
  uint16_t currentPosition = qtr.readLineBlack(sensorValues);
 
  return currentPosition;
}

// Chú ý: Dùng 'int' thay vì 'void'
int saiso() {
  int error = currentPosition - CENTER_POSITION;
  return error;
}


bool kiemTraNhacBong() {
  bool allBlack = true;
  // Đã sửa cú pháp for chuẩn C++ (dùng dấu chấm phẩy)
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    if (sensorValues[i] < 600) {
      allBlack = false; // Chỉ cần 1 mắt thấy trắng là xe vẫn đang dưới đất
    }
  }
  return allBlack;
}

// Hàm kiểm tra xe bị văng ra khỏi vạch (Cả 5 mắt đều trắng toát)
bool kiemTraMatLine() {
  bool allWhite = true;
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    if (sensorValues[i] > 400) {
      allWhite = false; // Chỉ cần 1 mắt thấy đen là vẫn còn trên line
    }
  }
  return allWhite;
}

LoaiNgaRe nhanDienNgaRe() {
  // Trích xuất trạng thái 5 mắt
  bool m1 = sensorValues[0] > 500;
  bool m2 = sensorValues[1] > 500;
  bool m3 = sensorValues[2] > 500;
  bool m4 = sensorValues[3] > 500;
  bool m5 = sensorValues[4] > 500;

  bool gocVuongPhai = (m3 && m4 && m5);
  bool gocVuongTrai = (m1 && m2 && m3) && !m5; 
  bool ngaBaChuy  = (m1 && m5) || (m1 && m2 && m4 && m5) || (m1 && m3) || (m3 && m5);

  // Phân loại và trả kết quả về cho file chính
  if (ngaBaChuy) {
    return NGA_BA_CHU_Y;
  } 
  else if (gocVuongPhai) {
    return GOC_VUONG_PHAI;
  } 
  else if (gocVuongTrai) {
    return GOC_VUONG_TRAI;
  } 
  
  return DUONG_THANG; // Nếu không rơi vào 3 trường hợp trên thì là đang đi bình thường
}