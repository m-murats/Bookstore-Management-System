# 📚 Kitabevi Yönetim Sistemi (Bookstore Management System)

Bu proje, **Bilgisayar Programlama III** dersi kapsamında geliştirilmiştir. 
C programlama dili kullanılarak, kitap ve kategori bilgilerini dinamik bellek yönetimi ile tutan, dosyalama işlemleri yapabilen ve istatistiksel veriler sunan bir sistemdir.

## 🎯 Projenin Amacı
Projenin temel amacı; `struct` yapıları, işaretçiler (pointers) ve dinamik bellek fonksiyonlarını (`malloc`, `calloc`, `realloc`, `free`) kullanarak karmaşık veri yapılarını yönetme becerisini geliştirmektir.

## 📂 Proje Yapısı

Proje aşağıdaki dosyalardan oluşmaktadır:

* **`main.c`**: Programın giriş noktasıdır. Verilerin dosyadan okunmasını tetikler, fonksiyonları test eder ve kapanışta belleği temizler.
* **`Proje1.h`**: `Kitap` ve `Kategori` struct tanımlarını ve fonksiyon prototiplerini içerir.
* **`Proje1.c`**: Fonksiyonların gövdelerini (implementasyonlarını) içerir. Bellek yönetimi işlemleri burada yapılır.
* **`Makefile`**: Projeyi derlemek ve çalıştırmak için gerekli komutları içerir.
* **`kategoriler.txt` & `kitaplar.txt`**: Verilerin saklandığı metin dosyalarıdır.

## 🏗️ Veri Yapıları

Sistem iki ana yapı üzerine kurulmuştur:

1.  **`Kitap`**: Kitabın adı, yazarı, fiyatı, basım yılı ve kategori kodunu tutar. (Ad ve Yazar dinamik stringlerdir).
2.  **`Kategori`**: Kategori adını ve o kategoriye ait kitapları tutan dinamik bir diziyi (`Kitap *kategoriKitaplar`) barındırır.

## ⚙️ Özellikler ve Fonksiyonlar

Proje 5 ana modülden oluşur:

### 1. Yapı Oluşturma
* `KategoriOlustur`: Yeni bir kategori struct'ı oluşturur.
* `KitapOlustur`: Yeni bir kitap struct'ı oluşturur.

### 2. Dizi Yönetimi
* `KitapEkle`: Kitabı ilgili kategoriye ekler. Eğer kategori kapasitesi dolduysa `realloc` ile hafıza alanını genişletir.

### 3. Görüntüleme
* `KitapBilgileriniYazdir`: Tek bir kitabın detaylarını yazar.
* `KategoriBilgileriniYazdir`: Kategorinin özet bilgisini yazar.
* `TumKategorileriYazdir`: Tüm hiyerarşiyi (Kategoriler ve içindeki kitaplar) listeler.

### 4. İstatistik ve Sorgulama
* `FiyatOrtalamasiHesapla`: Bir kategorideki kitapların fiyat ortalamasını bulur.
* `OrtalamaUstuKitaplariListele`: Ortalamanın üzerindeki kitapları listeler.
* `EnPahaliKitaplariYazdir`: Her kategorinin en pahalı kitabını bulur.
* `EskiKitapFiyatGuncelle`: Belirli bir yıldan eski kitapların fiyatını günceller.

### 5. Dosya İşlemleri
* `DiziyiDosyayaYaz`: Program kapanırken verileri `.txt` dosyalarına kaydeder.
* `DosyadanDiziyeAktar`: Program açılışında verileri dosyalardan okuyup dinamik dizilere yükler.

## 🚀 Derleme ve Çalıştırma

Projeyi derlemek için terminalde proje dizinine gidip `make` komutunu kullanabilirsiniz (Eğer Makefile oluşturduysanız):

```bash
make
./program
