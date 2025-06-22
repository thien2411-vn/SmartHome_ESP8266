# 🌟 Chào mừng bạn đến với thiên đường ESP 🌟

Đây là một ứng dụng đơn giản sử dụng **ESP8266** để biến ngôi nhà của bạn trở nên **thông minh và hiện đại hơn**.

Thông qua việc kết nối các **LED** (đại diện cho các thiết bị điện trong nhà) và cảm biến **DHT11** với **Firebase** và **Dashboard**, mình đã mô phỏng lại một mô hình **Smart Home** với các tính năng:

- 🌡️ Đo và hiển thị **nhiệt độ - độ ẩm** lên biểu đồ theo **thời gian thực** trên Dashboard.
- 💡 Điều khiển các thiết bị thông qua thao tác **bật/tắt** trên Dashboard.
- 🔄 Đồng bộ dữ liệu với **Firebase Realtime Database**.

---

## 🚀 Các bước để sở hữu cho mình một Smart Home:

### 🔧 Bước 1: Chuẩn bị và chạy giao diện Dashboard

1. Tải các file sau về máy:
   - `config.json`
   - `index.html`
   - `styles.css`

2. Mở chúng bằng **Visual Studio Code** (hoặc bất kỳ trình soạn thảo nào).
3. Chạy file `index.html` để hiển thị **giao diện Dashboard**.

---

### ☁️ Bước 2: Cấu hình Firebase

1. Tạo một **Realtime Database** mới trên Firebase. Ví dụ:
   
   ![image](https://github.com/user-attachments/assets/9ecf4578-e305-4126-80d0-371779003ce1)

3. Truy cập vào `Authentication` → Bấm **Start** → Bật **Anonymous**.
4. Lấy địa chỉ **Firebase Realtime Database URL** và thay vào file `index.html`.

---

### 🔌 Bước 3: Nạp code vào ESP8266

1. Mở file `SmartHome.ino` bằng Arduino IDE.
2. **Chỉnh sửa** các thông tin sau trong code:
   - Tên WiFi và mật khẩu (`SSID`, `PASSWORD`)
   - Địa chỉ Firebase của bạn
3. Nạp code vào bo mạch **ESP8266**.

📌 *Mình đã để hướng dẫn chi tiết trong phần chú thích của code nhé!*

---

### 🎉 Bước 4: Tận hưởng thành quả!

Bây giờ bạn đã có một hệ thống **nhà thông minh đơn giản** sử dụng ESP8266, giao tiếp **Realtime** với Firebase và Dashboard.

Link dashboard của mình: https://thien2411-vn.github.io/SmartHome_ESP8266/
---

## 📽 Video demo

[![image](https://github.com/user-attachments/assets/be582830-b69b-4fd5-b1ca-08d1df2a9774)](https://youtu.be/GCs6wj8Q9Ko?si=Lc_H9QL5wANIVDOi)

Nếu bạn thấy dự án hữu ích, hãy ⭐ star để ủng hộ mình nhé!

