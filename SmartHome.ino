#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <DHT.h>

// WiFi và Firebase
#define WIFI_SSID "92" // thay đổi thành wifi nhà bạn
#define WIFI_PASSWORD "1234567891011" // thay đổi mật khẩu
#define API_KEY "AIzaSyDmXc6zHfDBcxGlx4V5J-tWW2RB4oS3__Q" // thay đổi địa chỉ firebase của bạn
#define DATABASE_URL "https://smartcity-cfef9-default-rtdb.firebaseio.com/" // thay đổi đường link trong realtime database của bạn

// Firebase
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signUp = false;

// Cảm biến và thiết bị
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Chân thiết bị
#define LED_CALL D5    
#define LED_LIGHT D6     
#define LED_SPEAKER D7      

void setup()
{
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_CALL, OUTPUT);
  pinMode(LED_LIGHT, OUTPUT);
  pinMode(LED_SPEAKER, OUTPUT);

  // Kết nối WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nKết nối WiFi thành công");
  Serial.println(WiFi.localIP());

  // Cấu hình Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", ""))
  {
    Serial.println("Đăng ký Firebase thành công");
    signUp = true;
  }
  else
  {
    Serial.printf("Lỗi đăng ký: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void capNhatFirebase(const String &path, int value)
{
  if (Firebase.RTDB.setInt(&fbdo, path, value))
  {
    Serial.printf("Cập nhật %s = %d\n", path.c_str(), value);
  }
  else
  {
    Serial.printf("Lỗi cập nhật %s: %s\n", path.c_str(), fbdo.errorReason().c_str());
  }
}

void hienTrangThaiThietBi(const String &path, int pin)
{
  if (Firebase.RTDB.getBool(&fbdo, path))
  {
    bool trangThai = fbdo.boolData();
    digitalWrite(pin, trangThai ? HIGH : LOW);
    Serial.printf("%s = %s\n", path.c_str(), trangThai ? "ON" : "OFF");
  }
  else
  {
    Serial.printf("Lỗi đọc %s: %s\n", path.c_str(), fbdo.errorReason().c_str());
  }
}

void loop()
{
  if (Firebase.ready() && signUp)
  {
    // Đọc dữ liệu từ cảm biến
    float doam = dht.readHumidity();
    float nhietdo = dht.readTemperature();

    if (isnan(doam) || isnan(nhietdo))
    {
      Serial.println("Không đọc được dữ liệu từ DHT11");
      return;
    }

    // Gửi lên Firebase
    capNhatFirebase("/weather/temperature", (int)nhietdo);
    capNhatFirebase("/weather/humidity", (int)doam);

    // Đọc trạng thái các thiết bị
    hienTrangThaiThietBi("/call/callStatus", LED_CALL);
    hienTrangThaiThietBi("/light/lightStatus", LED_LIGHT);
    hienTrangThaiThietBi("/speaker/speakerStatus", LED_SPEAKER);

    Serial.println("----------");
  }

  delay(1000);
}
