/**
 * @file Proje1.c
 * @description Fonksiyonları içerir.
 * @assignment 1.Ödev
 * @date 15.12.2025
 * @author Murat
 */

#include "Proje1.h"

/**
 * Yeni bir Kitap yapısı (struct) oluşturur.
 * String alanlar (ad, yazar) için dinamik bellek (malloc) ayrılır.
 */
Kitap kitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil){
    Kitap yeniKitap;

    // String uzunluğu + 1 (NULL karakteri '\0' için) kadar yer ayırıyoruz.
    yeniKitap.kitapAdi = (char*)malloc(sizeof(char) * (strlen(ad) + 1));
    yeniKitap.yazar = (char*)malloc(sizeof(char) * (strlen(yazar) + 1));

    // Bellek hatası kontrolü (RAM dolduysa veya hata varsa)
    if (yeniKitap.yazar == NULL || yeniKitap.kitapAdi == NULL) {
        printf("Kitap oluşturulurken bellek ayrilamadi.\n");
        exit(1); // Programı güvenli şekilde sonlandırır.
    }

    // Verileri güvenli şekilde kopyalamak için strcpy kullanıyoruz. 
    // = ile atama yapmıyoruz. çünkü bu sadece adres ataması yapar.
    strcpy(yeniKitap.kitapAdi, ad);
    strcpy(yeniKitap.yazar, yazar);

    yeniKitap.kategoriKodu = kod;
    yeniKitap.fiyat = fiyat;
    yeniKitap.basimYili = yil;

    return yeniKitap;
}

/**
 * Yeni bir Kategori yapısı oluşturur.
 * Kitap dizisi için başlangıç kapasitesi kadar yer ayırır.
 */
Kategori kategoriOlustur(char *ad, unsigned short kod){
    Kategori yeniKategori;

    yeniKategori.kategoriKodu = kod;
    yeniKategori.kitapSayisi = 0; // Başlangıçta kitap yok

    // Kategori adı için dinamik bellek ayırma
    yeniKategori.kategoriAdi = (char*)malloc(sizeof(char) * (strlen(ad) + 1));

    if (yeniKategori.kategoriAdi == NULL || yeniKategori.kategoriKitaplar == NULL) {
         printf("Kategori olusturulurken bellek ayrilamadi.\n");
         free(yeniKategori.kategoriAdi);
         free(yeniKategori.kategoriKitaplar);
         exit(1);
    }

    strcpy(yeniKategori.kategoriAdi, ad);

    // Başlangıç kapasitesi kadar yer ayırıyoruz.
    yeniKategori.kapasite = 5;
    yeniKategori.kategoriKitaplar = (Kitap*)malloc(sizeof(Kitap) * yeniKategori.kapasite);

    return yeniKategori;
}

/**
 * Var olan bir kategoriye kitap ekler.
 * Eğer kapasite dolduysa 'realloc' ile diziyi genişletir.
 */
void kitapEkle(Kategori *kategoriDizi, int *kategoriSayisi, Kitap yeniKitap){
    int kategoriIndex = -1; 
    
    // Kitabın ait olduğu kategoriyi (kategoriKodu ile) bul
    for (int i = 0; i < *kategoriSayisi; i++) {
       if (kategoriDizi[i].kategoriKodu == yeniKitap.kategoriKodu) {
            kategoriIndex = i;
            break;
       }
    }
    
    // Kategori bulunamadıysa hata ver ve belleği temizle
    if (kategoriIndex == -1) {
        printf("%d kodlu kategori bulunamadi, kitap eklenemedi.\n", yeniKitap.kategoriKodu);
        free(yeniKitap.kitapAdi);
        free(yeniKitap.yazar);
        return;
    }

    Kategori *hedefKategori = &kategoriDizi[kategoriIndex];

    // Kapasite Kontrolü ve Genişletme (Realloc)
    if (hedefKategori->kitapSayisi >= hedefKategori->kapasite) {
       int yeniKapasite = hedefKategori->kapasite * 2; // Kapasiteyi 2 katına çıkar
       
       
    hedefKategori->kategoriKitaplar = (Kitap*)realloc(hedefKategori->kategoriKitaplar, yeniKapasite * sizeof(Kitap));
    
    hedefKategori->kapasite = yeniKapasite;
   
           
    }

    //Kitabı dizinin sonuna ekle
    hedefKategori->kategoriKitaplar[hedefKategori->kitapSayisi] = yeniKitap;
    hedefKategori->kitapSayisi++;
}

/**
 * Tek bir kitabın detaylarını ekrana yazdırır.
 */
void kitapBilgileriniYazdir(Kitap *kitap){
    if (kitap == NULL){
        printf("Kitap bilgileri mevcut degil.\n");
        return;
    }  
    
    // %-30s: Sola dayalı 30 karakterlik alan
    // %.2f: Virgülden sonra 2 basamak (float için 150.50 gibi mesela)
    printf("\t * %-30s | Yazar: %-20s | Yil: %d | Fiyat: %.2f TL\n",
           kitap->kitapAdi, 
           kitap->yazar, 
           kitap->basimYili, 
           kitap->fiyat);
}
 
/**
 * Kategori başlığını ve kitap sayısını yazdırır.
 */
void kategoriBilgileriniYazdir(Kategori *kategori){
    if (kategori == NULL){
        printf("Kategori bilgileri mevcut degil.\n");
        return;
    }

    printf("KATEGORI: %-20s (Kod: %u) | Kitap Sayisi: %d\n", 
           kategori->kategoriAdi, 
           kategori->kategoriKodu, 
           kategori->kitapSayisi);
}

/**
 * Sistemdeki tüm kategorileri ve içindeki kitapları listeler.
 */
void tumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi){
    printf("\n=== TUM KATEGORILER VE KITAPLAR LISTELENIYOR ===\n");
    
    for (int i = 0; i < kategoriSayisi; i++) {
        kategoriBilgileriniYazdir(&kategoriDizi[i]);
        printf("----------------------------------------------------------------------------------\n");
        
        // İç içe döngü ile o kategorinin kitaplarını yazdır
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++) {
            kitapBilgileriniYazdir(&kategoriDizi[i].kategoriKitaplar[j]);
        }
        printf("----------------------------------------------------------------------------------\n\n");
    }
}

/**
 * Bir kategorideki kitapların fiyat ortalamasını hesaplar.
 */
float fiyatOrtalamasiHesapla(Kategori *kategori){
    // Sıfıra bölünme hatasını önle
    if (kategori->kitapSayisi == 0) return 0.0f;

    float toplam = 0.0f;
    for (int i = 0; i < kategori->kitapSayisi; i++) {
        toplam += kategori->kategoriKitaplar[i].fiyat;
    }
    return toplam / kategori->kitapSayisi;
}

/**
 * Ortalamanın üzerindeki fiyata sahip kitapları listeler.
 */
void ortalamaUstuKitaplariListele(Kategori *kategori){
    float ortalama = fiyatOrtalamasiHesapla(kategori); //ortalamayı al
    
    printf("----------------------------------------------------------------------\n");
    printf("KATEGORI: %-15s | ORTALAMA FIYAT: %.2f TL\n", kategori->kategoriAdi, ortalama);
    
    int ortalamaUstu = 0;
    for (int i = 0; i < kategori->kitapSayisi; i++) {
        // Fiyat karşılaştırması
        if (kategori->kategoriKitaplar[i].fiyat > ortalama) { //ortalamanın üstündeyse yazdır
            printf("\t* %-30s -> %.2f TL\n", 
                   kategori->kategoriKitaplar[i].kitapAdi, 
                   kategori->kategoriKitaplar[i].fiyat);
            ortalamaUstu++;
        }
    }
    if (ortalamaUstu == 0) { 
        printf("\t(Bu kategoride ortalama ustu kitap yok)\n");
    }
}

/**
 * Her kategorinin en pahalı kitabını bulur ve yazdırır.
 */
void enPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi){
    for (int i = 0; i < kategoriSayisi; i++) {

        Kategori *tempKat = &kategoriDizi[i];
        if (tempKat->kitapSayisi == 0) continue; //kitabı olmayan kategoriyi atla

        // ilk kitap en pahalıdır varsayımı
        Kitap *enPahali = &tempKat->kategoriKitaplar[0];
        
        // diğer kitaplarla karşılaştır
        for (int j = 1; j < tempKat->kitapSayisi; j++) {

            if (tempKat->kategoriKitaplar[j].fiyat > enPahali->fiyat) {

               enPahali = &tempKat->kategoriKitaplar[j];
            }
        }
        
        printf("Kategori: %-15s -> En Pahali: %-25s (%.2f TL)\n", 
               tempKat->kategoriAdi, enPahali->kitapAdi, enPahali->fiyat);
    }
}

/**
 * Belirli bir yıldan eski kitapların fiyatını günceller.
 */
void eskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat) {
    int guncellenenAdet = 0;

    for (int i = 0; i < kategoriSayisi; i++) {
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++) {

            // Yıl kontrolü
            if (kategoriDizi[i].kategoriKitaplar[j].basimYili < yil) {
                kategoriDizi[i].kategoriKitaplar[j].fiyat = yeniFiyat;
                guncellenenAdet++;
            }
        }
    }
    printf("\nBILGI: %d yili oncesi %d kitap %.2f TL yapildi.\n", yil, guncellenenAdet, yeniFiyat);
}

/**
 * Tüm verileri dosyalara kaydeder (Persistence).
 * Mod: "w" (Write - Dosyayı sıfırlar ve yazar)
 */
void diziyiDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi) {

    //kategorileri yaz (Format: Ad [TAB] Kod)
    FILE *fpKategori = fopen("kategoriler.txt", "w");

    if (fpKategori != NULL) {
        for (int i = 0; i < kategoriSayisi; i++)
            fprintf(fpKategori, "%s\t%d\n", kategoriDizi[i].kategoriAdi, kategoriDizi[i].kategoriKodu);
        fclose(fpKategori);
        printf("%d kategori dosyaya yazildi.\n", kategoriSayisi);
    } else {
        printf("kategoriler.txt oluşturulamadi.\n");
    }

    // kitapları yaz (Format: Ad [TAB] Yazar [TAB] Kod [TAB] Fiyat [TAB] Yıl)
    FILE *fpKitap = fopen("kitaplar.txt", "w");
    if (fpKitap != NULL) {
        int toplam = 0;
        for (int i = 0; i < kategoriSayisi; i++) {
            for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++) {
                Kitap *k = &kategoriDizi[i].kategoriKitaplar[j];
                // fiyat hassasiyeti (%.2f) korunarak yazdım
                fprintf(fpKitap, "%s\t%s\t%d\t%.2f\t%d\n", 
                        k->kitapAdi, k->yazar, k->kategoriKodu, k->fiyat, k->basimYili);
                toplam++;
            }
        }
        fclose(fpKitap);
        printf("%d kitap dosyaya yazildi.\n", toplam);
    } else {
        printf("kitaplar.txt oluşturulamadi.\n");
    }
}

/**
 * Program başında dosyalardan verileri okur ve belleğe yükler.
 * Buffer boyutu: 256 (Uzun satırlar için güvenlik önlemi)
 */
void dosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr) {
    // kategorileri Oku
    FILE *fpKategori = fopen("kategoriler.txt", "r");
    if (fpKategori != NULL) {
        char tempAd[256]; 
        unsigned short tempKod;
        
        // TAB karakterine kadar okuma yapar (%[^\t])
        // dönüş değeri 2 ise (Ad ve Kod) okuma başarılıdır.
        while (fscanf(fpKategori, "%[^\t]\t%hu\n", tempAd, &tempKod) == 2) {
            *kategoriDiziPtr = (Kategori *)realloc(*kategoriDiziPtr, (*kategoriSayisiPtr + 1) * sizeof(Kategori));
            (*kategoriDiziPtr)[*kategoriSayisiPtr] = kategoriOlustur(tempAd, tempKod);
            (*kategoriSayisiPtr)++;
        }
        fclose(fpKategori);
        printf("%d kategori dosyadan yuklendi.\n", *kategoriSayisiPtr);
    } else {
        printf("'kategoriler.txt' bulunamadi (Ilk calistirma olabilir).\n");
    }

    // kitapları Oku
    FILE *fpKitap = fopen("kitaplar.txt", "r");
    if (fpKitap != NULL) {
        char tAd[256];    
        char tYazar[256]; 
        unsigned short tKod; float tFiyat; int tYil;
        
        // 5 değişkenin tamamının başarıyla okunduğunu kontrol et
        while (fscanf(fpKitap, "%[^\t]\t%[^\t]\t%hu\t%f\t%d\n", tAd, tYazar, &tKod, &tFiyat, &tYil) == 5) {
            Kitap k = kitapOlustur(tAd, tYazar, tKod, tFiyat, tYil);
            kitapEkle(*kategoriDiziPtr, kategoriSayisiPtr, k);
        }
        fclose(fpKitap);
    } else {
        printf("'kitaplar.txt' bulunamadi.\n");
    }
}