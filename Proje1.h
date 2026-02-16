/**
 * @file Proje1.h
 * @description Kitap ve Kategori yapılarını , fonksiyon prototiplerini tanımladım.
 * @assignment 1.Ödev
 * @date 15.12.2025
 * @author Murat
 */


#ifndef PROJE1_H
#define PROJE1_H 
 /* ifndef -> bu dosya daha önce eklendi mi diye kontrol eder, çoklu eklemeyle çakışmayı önler.
    define -> dosyanın eklendiğini sisteme işaretler
 */ 

#include <stdio.h> //standart input output işlemleri için
#include <stdlib.h> //memory allocation için
#include <string.h> //string işlemleri için strcpy , strlen vs.


typedef struct{
    char *kitapAdi; //kiap adı
    char *yazar;    //yazar adı
    unsigned short int kategoriKodu;    //Hangi kategoriye ait olduğunu belirten kod
    float fiyat;    // Kitabın fiyatı 
    int basimYili;  // Kitabın basım yılı
}Kitap;

typedef struct{
    char *kategoriAdi;      // Kategorinin adı 
    unsigned short int kategoriKodu;    // Kategorinin benzersiz kodu
    Kitap *kategoriKitaplar; // Bu kategoriye ait kitapların dinamik dizisi
    int kitapSayisi; // Dizideki mevcut kitap sayısı
    int kapasite;   // Dizinin o anki maksimum kapasitesi 
}Kategori;

//Fonksiyon prototipleri --->

Kategori kategoriOlustur(char *ad, unsigned short kod);
Kitap kitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil);

void kitapEkle(Kategori *kategoriDizi, int *kategoriSayisi, Kitap yeniKitap);

void kitapBilgileriniYazdir(Kitap *kitap);
void kategoriBilgileriniYazdir(Kategori *kategori);
void tumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi);

float fiyatOrtalamasiHesapla(Kategori *kategori);
void ortalamaUstuKitaplariListele(Kategori *kategori);
void enPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi);
void eskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat);

void diziyiDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi);
//pointerın pointerı gönderdik çünkü dizi ve sayı içeride değişecek
void dosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr);

 #endif

