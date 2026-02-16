/**
 * @file main.c
 * @description Ana test ve akış dosyası.
 * @assignment 1.Ödev
 * @date 15.12.2025
 * @author Murat
 */

#include "Proje1.h"

int main()
{
    printf("*************************\n");
    printf("*****..HOSGELDINIZ..*****\n");
    printf("*************************\n\n");

    
    Kategori *kategoriDizisi = NULL; //ana kategori dizisi başta null
    int kategoriSayisi = 0;
    
    dosyadanDiziyeAktar(&kategoriDizisi, &kategoriSayisi); //Dosyadan verileri oku.

    // Eğer dosya boşsa veya test etmek için yeni veri ekleyelim

    if (kategoriSayisi == 0)
    {
        printf("Test verileri olusturuluyor...\n\n");

        char *katAdlari[] = {"Bilim Kurgu", "Edebiyat", "Polisiye"};
        unsigned short katKodlari[] = {50, 60, 70};
        int katAdet = 3;

        for (int i = 0; i < katAdet; i++)
        {
            Kategori yeniKategori = kategoriOlustur(katAdlari[i], katKodlari[i]);

            // Ana diziyi genişlet (realloc)
            kategoriDizisi = (Kategori *)realloc(kategoriDizisi, (kategoriSayisi + 1) * sizeof(Kategori));

            kategoriDizisi[kategoriSayisi] = yeniKategori;
            kategoriSayisi++;
            printf("Kategori Eklendi: %s\n", katAdlari[i]);
        }

        Kitap b1 = kitapOlustur("Fahrenheit 451", "Ray Bradbury", 50, 60.50, 1953);
        kitapEkle(kategoriDizisi, &kategoriSayisi, b1);

        Kitap b2 = kitapOlustur("Patasana", "Ahmet Umit", 70, 110.00, 2000);
        kitapEkle(kategoriDizisi, &kategoriSayisi, b2);

        Kitap b3 = kitapOlustur("Saatleri Ayarlama Enstitüsü", "Ahmet Hamdi Tanpinar", 60, 220.50, 1961);
        kitapEkle(kategoriDizisi, &kategoriSayisi, b3);

        Kitap b4 = kitapOlustur("Dune", "Frank Herbert", 50, 180.75, 1965);
        kitapEkle(kategoriDizisi, &kategoriSayisi, b4);

        Kitap b5 = kitapOlustur("Kanli Ay", "Joe Nesbo", 70, 345.30, 2010);
        kitapEkle(kategoriDizisi, &kategoriSayisi, b5);

        Kitap b6 = kitapOlustur("Bekle Beni", "Zulfu Livaneli", 60, 184.75, 1965);
        kitapEkle(kategoriDizisi, &kategoriSayisi, b6);

        Kitap b7 = kitapOlustur("Cesur Yeni Dünya", "Aldous Huxley", 50, 130.10, 1932);
        kitapEkle(kategoriDizisi, &kategoriSayisi, b7);

        Kitap b8 = kitapOlustur("Gece Yarisi Kütüphanesi", "Matt Haig", 60, 190.75, 2020);
        kitapEkle(kategoriDizisi, &kategoriSayisi, b8);

        Kitap b9 = kitapOlustur("Beyoglu'nun En Güzel Abisi", "Ahmet Umit", 70, 270.50, 2014);
        kitapEkle(kategoriDizisi, &kategoriSayisi, b9);

        printf("\nKitaplar eklendi.\n");
    }
    else
    {
        printf("Sistemde %d kategori mevcut, manuel ekleme atlandi.\n", kategoriSayisi);
    }

    tumKategorileriYazdir(kategoriDizisi, kategoriSayisi);

    printf("\n*****************************************\n");
    printf("*****Ortalama Üstü Kitaplar Listesi.*****\n");
    printf("*****************************************\n\n");

    for (int i = 0; i < kategoriSayisi; i++)
    {
        ortalamaUstuKitaplariListele(&kategoriDizisi[i]);
    }
    printf("\n-------------------------------------------\n");

    printf("\n*****************************************\n");
    printf("*****En Pahali Kitaplar Listesi.*****\n");
    printf("*****************************************\n\n");

    enPahaliKitaplariYazdir(kategoriDizisi, kategoriSayisi);

    printf("\n\n***********************************************************\n");
    printf("*****Güncellemeler yapiliyor ve Dosyalar kaydediliyor.*****\n");
    printf("***********************************************************\n");

    eskiKitapFiyatGuncelle(kategoriDizisi, kategoriSayisi, 1960, 99.99);

    diziyiDosyayaYaz(kategoriDizisi, kategoriSayisi);

    for (int i = 0; i < kategoriSayisi; i++)
    {
        Kategori *kat = &kategoriDizisi[i];

        //Kitapların içindeki dinamik stringleri temizle
        for (int j = 0; j < kat->kitapSayisi; j++)
        {
            free(kat->kategoriKitaplar[j].kitapAdi);
            free(kat->kategoriKitaplar[j].yazar);
        }

        //Kategorinin kitap dizisini temizle
        free(kat->kategoriKitaplar);

        //Kategori adını temizle
        free(kat->kategoriAdi);
    }

    //Ana kategori dizisini temizle
    free(kategoriDizisi);

    printf("\n*****************************************************\n");
    printf("*****Tum bellekler iade edildi. Program kapaniyor.*****\n");
    printf("*******************************************************\n\n");

    return 0;
}