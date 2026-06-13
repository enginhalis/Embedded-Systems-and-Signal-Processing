# Embedded Systems & Sensor Fusion Developments

Bu depo; lisans eğitimim ve profesyonel gelişim süreçlerim kapsamında ARM Cortex-M4 mimarisi üzerinde gerçekleştirdiğim register seviyesinde (bare-metal) sürücü geliştirmelerini, özel zamanlayıcı (task scheduler) tasarımlarını ve C tabanlı dijital sinyal işleme/sensör füzyonu simülasyonlarımı içermektedir.

---

## 🛠️ Proje İçerikleri

### 1. STM32 Bare-Metal Workspace (`STM32-Bare-Metal-Workspace`)
STM32F407G-DISC1 geliştirme kartı üzerinde, hiçbir harici donanım soyutlama kütüphanesi (HAL/LL) kullanılmadan tamamen register seviyesinde geliştirilmiş projeleri barındırır.
* **003TaskScheduler:** İşlemcinin SysTick kesmesini (interrupt) referans alarak, görevler arası geçişi (context switching) donanım seviyesinde yöneten hafif bir **Round-Robin Task Scheduler** mimarisi.
* **000Sp_to_Psp:** Thread ve Handler modları arasındaki geçişleri yönetmek adına Main Stack Pointer (MSP) ve Process Stack Pointer (PSP) dönüşümlerinin low-level assembly ve C entegrasyonuyla kontrolü.
* **001PeripheralInterrupt & USART3_Int:** Donanım kesme mimarileri, NVIC önceliklendirmeleri ve UART çevre birimi üzerinden kesme tabanlı veri iletişimi.
* **002FaultGen & FaultAnalysis:** Kritik aviyonik sistemlerde sistem kararlılığını ölçmek adına HardFault, UsageFault ve BusFault gibi işlemci istisnalarının yakalanması ve analiz edilmesi.

### 2. Custom Makefile Build System (`Custom-Makefile-Build-System`)
Bir IDE'ye veya hazır arayüze bağımlı kalmadan, GNU araç zinciri (GCC compiler) kullanarak gömülü bir sistemin sıfırdan nasıl derlendiğini gösteren altyapı çalışmasıdır.
* **`stm32_startup.c`:** İşlemci ilk açıldığında çalışan, vektör tablosunu (vector table) haritalandıran, veri kopyalama (.data) ve BSS temizleme işlemlerini yürüten özgün başlatma dosyası.
* **`stm32_ls.ld`:** Flash ve SRAM hafıza bölgelerini, segment sınırlarını ve yığın (stack) konumunu belirleyen özel Linker Script dosyası.
* **`Makefile`:** Projenin bağımlılıklarını yöneten, ara obje dosyalarını (.o) derleyen ve son çıktıyı (.elf/.map) üreten derleme scripti.

### 3. Sensor Fusion Simulation (`Sensor-Fusion-Simulation`)
Savunma sanayii ve otonom araç platformlarındaki seyrüsefer (navigation) algoritmalarına hazırlık niteliğinde geliştirilmiş, yazılımsal bir vaka çalışmasıdır.
* Gürültülü ve bias (kayma) içeren ivmeölçer ve jiroskop (IMU) verilerini üreten dinamik bir simülasyon altyapısı.
* Sinyal üzerindeki yüksek frekanslı gürültüleri temizlemek ve kararlı yönelim (orientation) bilgisi elde etmek amacıyla **Moving Average (Hareketli Ortalama)**, **Low-Pass (Alçak Geçiren)** ve **Complementary (Tamamlayıcı)** filtre algoritmalarının C dilinde modüler implementasyonu.
* Proje detaylarını ve algoritma başarımlarını içeren teknik analiz raporu (`Rapor.pdf`) klasör içerisinde yer almaktadır.

---

## 🧰 Kullanılan Teknolojiler ve Araçlar
* **Diller:** C, Embedded C, Assembly (ARM)
* **Donanım/Mimari:** ARM Cortex-M4 (STM32F407VGT6)
* **Araçlar:** STM32CubeIDE, GCC Toolchain, GNU Make, Git