# Ajeware_Air_Cleaner_1.0
A firmware made by baksoo aje for air cleaner.

이 펌웨어는 다음의 제품들을 기반으로 만들어 졌습니다.
디스플레이: TFT LCD ST7735 1.8inch 160*120
먼지 센서: PMS7003
Fan : DC 12v 0.4A 12cm
아두이노: Nano, Uno, Mega.

이 펌웨어를 빌드하기 위해서는 다음의 라이브러리가 필요합니다.
Adafruint_7735_Library 1.10.0
Adafruit_GFX_Libarary 1.6.0
Adafruit_Unified_Sensor
DHT11_sensor_library 1.3.10
SoftwareSerial 1.0

작동 방식
Auto 1: 가장 먼지 량이 많은 것을 기반으로 팬속도를 조절합니다.
Auto 2: PM 0.1 이하 크기의 먼지랑을 기반으로 팬 속도를 조절합니다.
Auto 2: PM 2.5 이하 크기의 먼지랑을 기반으로 팬 속도를 조절합니다.
Auto 3: PM 10 이하 크기의 먼지량을 기반으로 팬 속도를 조절합니다.
Manual 1: 40%의 속도로 30분 가동 후 5분 휴식
Manual 2: 70%의 속도로 30분 가동 후 5분 휴식
Manual 3: 100%의 속도로 30분 가동후 5분 휴식

버튼: 위의 작동 방식증 하나를 순차적으로 번갈아 가며 선택 합니다
