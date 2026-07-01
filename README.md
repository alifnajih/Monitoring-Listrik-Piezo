# Monitoring-Listrik-Piezo
⚡ SIPEKA V2.0
Sistem Pemanen Energi Langkah Kaki Berbasis ESP32 dengan Monitoring IoT

SIPEKA (Sistem Pemanen Energi Langkah Kaki) merupakan perangkat monitoring energi listrik yang dihasilkan dari piezoelektrik menggunakan ESP32 sebagai mikrokontroler utama. Sistem ini mampu memantau tegangan, arus, daya, dan energi secara real-time melalui LCD 16×2 maupun dashboard berbasis web yang dapat diakses melalui jaringan WiFi.

✨ Fitur Utama
Monitoring tegangan (Voltage)
Monitoring arus (Current)
Monitoring daya (Power)
Monitoring energi (Energy)
LCD 16×2 sebagai tampilan lokal
Dashboard Web responsif
Realtime Monitoring menggunakan AJAX
Grafik realtime menggunakan Chart.js
Dual Mode WiFi
AP Mode
Online Mode (Station Mode)
Pengaturan WiFi melalui Web Interface
Penyimpanan konfigurasi WiFi menggunakan Preferences ESP32
Tombol Reset WiFi
Monitoring dapat dilakukan tanpa koneksi internet.
🛠 Hardware
Komponen	Keterangan
ESP32 DevKit V1	Mikrokontroler utama
INA219	Sensor tegangan dan arus
LCD 16×2 I2C	Tampilan lokal
Push Button	Power dan Reset WiFi
Modul Charger USB Type-C	Pengisian baterai
Baterai Li-Ion 18650	Catu daya sistem
Piezoelectric Array	Sumber energi listrik
📌 Fungsi Bagian Alat
Input Piezo

Digunakan untuk menghubungkan rangkaian piezoelektrik sebagai sumber energi listrik yang akan dipantau oleh sistem.

Port Charger USB Type-C

Digunakan untuk mengisi daya baterai internal perangkat.

Tombol Power

Menyalakan atau mematikan perangkat.

Tombol Reset WiFi

Tekan dan tahan sekitar 5 detik untuk menghapus konfigurasi WiFi yang tersimpan. Setelah proses reset selesai, perangkat akan kembali ke AP Mode.

LCD 16×2

Menampilkan informasi sistem secara langsung, meliputi:

Status WiFi
Tegangan
Arus
Daya
Energi
Alamat IP
📊 Parameter Monitoring
Parameter	Keterangan
Voltage (V)	Tegangan listrik yang dihasilkan sistem
Current (mA)	Arus listrik yang mengalir
Power (W)	Daya listrik sesaat
Energy (Wh)	Akumulasi energi listrik
WiFi Status	Status koneksi jaringan
IP Address	Alamat dashboard perangkat
🌐 Mode Operasi
AP Mode

Perangkat akan membuat hotspot WiFi sendiri apabila belum memiliki konfigurasi jaringan.

SSID

SIPEKA

Password

12345678

Dashboard dapat diakses melalui:

http://192.168.4.1
Online Mode

Setelah SSID dan Password WiFi disimpan, perangkat akan otomatis terhubung ke jaringan yang dipilih.

Alamat dashboard dapat diakses melalui IP Address yang ditampilkan pada LCD.

Contoh:

http://192.168.100.123
📈 Dashboard

Dashboard menyediakan informasi secara real-time mengenai:

Voltage
Current
Power
Energy
Status WiFi
IP Address
Grafik realtime Voltage
Grafik realtime Current
Grafik realtime Power
📷 Tampilan Sistem
Dashboard AP Mode
Dashboard Online Mode
Halaman WiFi Settings
LCD Monitoring
LCD AP Mode
LCD Online Mode
