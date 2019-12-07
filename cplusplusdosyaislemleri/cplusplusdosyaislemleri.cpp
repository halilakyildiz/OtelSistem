// cplusplusdosyaislemleri.cpp: Konsol uygulaması için giriş noktasını tanımlar.
//

/****************************************************************************
** SAKARYA ÜNİVERSİTESİ
** BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
** BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
** NESNEYE DAYALI PROGRAMLAMA DERSİ
** 2014-2015 BAHAR DÖNEMİ
**
** ÖDEV NUMARASI..........PROJE 1...........:
** ÖĞRENCİ ADI............HALİL AKYILDIZ....:
** ÖĞRENCİ NUMARASI.......G171210043........:
** DERSİN ALINDIĞI GRUP...2 ÖĞRETİM C FRUBU.:
****************************************************************************/

#include <stdafx.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ocale.h>
#include <conio.h>
#include <vector>
#include <sstream>

using namespace std;

int islem[2]; // Global değişkenler tanımlanıyor
vector<vector<string>> oda_listesi;
vector<vector<string>> musteri_listesi;
vector<vector<string>> oda_kayit_listesi;

void musteriEkle() // Müşteri ekleme metodu
{
	system("CLS"); // Ekranı temizleme kodu
	cout << "<=====  Musteri Ekleme Sayfasi =====>" << endl;
	string id, adi, soyadi, tc;
	cout << "Musteri numarasini, adini,soyadi,tc kimlik numarasini aralarinda bosluk olacak sekilde giriniz \n";
	cin >> id >> adi >> soyadi >> tc; // Sırayla değişkenlere atanıyor
	ofstream dosya_yaz;
	dosya_yaz.open("C:\\Users\\AKYILDIZ\\Desktop\\musteriler.txt", ios::app);
	dosya_yaz.seekp(-0L, ios::end); // İmleci kaydedilen verinin sonuna getirme metodu
	dosya_yaz << id + "\t" + adi +"\t"+soyadi+"\t"+tc+ "\n";
	dosya_yaz.close();

	cout << "Musteri eklendi.. Kayit eklemeye devam etmek icin [e] tusuna basiniz...";
	string devam;
	cin >> devam;
	if (devam == "e") musteriEkle();
}


void musteriler() // Ouşturulan müşteri listesini okuma metodu
{
	musteri_listesi.clear();
	ifstream musteri_oku;
	musteri_oku.open("C:\\Users\\AKYILDIZ\\Desktop\\musteriler.txt", ios::app);
	if (musteri_oku.is_open() != true)
	{
		cout << "Dosya acilamadi!" << endl;
		exit(EXIT_FAILURE);
	}
	string record;
	while (getline(musteri_oku, record)) // Listeyi okuyup oluşturulan string değişkenine atıyor
	{
		string data;
		stringstream ss(record);
		vector<string> kayit; // Dizi benzeri string türünden değişkenler bulunduran vektör
		while (getline(ss, data, '\t')) // Kayıttaki verilerin arasındaki tab kadar boşluk baz alınarak kayit vektörüne atanıyor
		{
			kayit.push_back(data);
		}
		if (kayit.size() > 0) // Kayit değişkeni boş değilse
		{
			musteri_listesi.push_back(kayit); // Kayit vektörü veriler bir üst vektöre yazdırılıyor 
		}

	}

}
void musteri_listele() //  Oluşturulan müşteri listesini ekrana yazdıran metod
{
	musteriler();
	system("CLS"); // Ekranı temizleyen komut
	cout << "<===== Musteri Listesi =====>\n";
	for each (vector<string> musteri in musteri_listesi) // Müşteri listesindeki verileri başka bi vektöre aktarıyor
	{
		cout << musteri.at(0) + "\t" + musteri.at(1)+"\t" +musteri.at(2)+"\t"+musteri.at(3)+ "\n"; // Ve bu vektörü ekrana yazdırıyor
	}

	cout << "\nUst menuye donmek icin bir tusa basin...";
	system("pause>nul");
}

void musteri_sil_islem(int i) // İstenilen müşteriyi sildiren metod
{
	musteri_listesi.erase(musteri_listesi.begin() + i); // Girilen müşteri numarasına göre vektör seçiliyor ve siliniyor
	ofstream dosya_yaz;
	dosya_yaz.open("C:\\Users\\AKYILDIZ\\Desktop\\musteriler.txt", ios::out); // Müşteriler dosyası güncel liste için boşaltılıyor
	for each (vector<string> item in musteri_listesi) // Güncel müşteri listesi item adlı vektöre aktarılıyor
	{
		dosya_yaz.seekp(-0L, ios::end); // İmleç sona getiriliyor
		dosya_yaz << item[0] + "\t" + item[1] + "\t" + item[2] + "\t" + item[3] + "\n"; // Kalan liste dosyaya tekrar yazdırılıyor
	}

	dosya_yaz.close();

}

void musteri_sil() 
{
	musteriler();
	string musteri_no;
	cout << "Silmek istediginiz musteri numarasini giriniz..\n";
	cin >> musteri_no;
	int sayac = 0;
	int sil_id = 0;
	int vector_size = musteri_listesi.size(); // Müşteri listesindeki verilerin boyutu bulunuyor
	for (int i = 0; i < vector_size; i++) // Bulunan boyuta kadar döndürülüyor
	{
		vector<string> item; // Tekrar bir vektör tanımlanıyor
		item = musteri_listesi[i]; // Müşteri listesi bu vektöre aktarılıyor
		if ( item [0]== musteri_no) // Girilen müşteri numarası eşleşmesi kontrol ettiriliyor
		{
			sayac++;
			sil_id = i;
		}
	}
	if (sayac>0)
	{
		string cvp;
		cout << "Silmek istediğinize emin misiniz? [e/h]";
		cin >> cvp;
		if (cvp == "e")
		{
			musteri_sil_islem(sil_id); // Eşleşen değer parametre olarak silme fonksiyonunda gönderiliyor
			musteri_listele(); // Yeni liste yazdırılıyor
			system("pause>nul");
		}
	}
	else {
		cout << "Boyle bir musteri yok! Devam icin bir tusa basin...";
		system("pause>nul");
		musteri_listele();
		system("pause>nul");
	}

}

void odaEkle()
{
	system("CLS");
	cout << "<=====  Oda Ekleme Sayfasi =====>" << endl;
	string id, odaAdi;
	cout << "Oda numarasini ve oda adini giriniz \n";
	cin >> id >> odaAdi; // Sırayla girilen veriler aktarılıyor
	ofstream dosya_yaz;
	dosya_yaz.open("C:\\Users\\AKYILDIZ\\Desktop\\odalar.txt", ios::app);
	dosya_yaz.seekp(-0L, ios::end); // İmleç sona getiriliyor
	dosya_yaz << id + "\t" + odaAdi +"\n"; // Dosyaya yazdırılıyor
	dosya_yaz.close();

	cout << "Oda eklendi.. Kayit eklemeye devam etmek icin [e] tusuna basiniz...";
	string devam;
	cin >> devam;
	if (devam == "e") 
		odaEkle();
	//system("pause>nul");
}

void odalar() // Odaları listeleyen metod
{
	oda_listesi.clear(); //Oda listesi siliniyor
	ifstream oda_oku;
	oda_oku.open("C:\\Users\\AKYILDIZ\\Desktop\\odalar.txt", ios::app); // Odalar dosyası okunuyor
	if (oda_oku.is_open() != true)
	{
		cout << "Dosya acilamadi!" << endl;
		exit(EXIT_FAILURE);
	}
	string record;
	while (getline(oda_oku,record)) // Dosyadaki veriler record değişkenine aktarılıyor
	{
		string data;
		stringstream ss(record); // Record değişkenindeki veriler vektöre atanıyor
		vector<string> kayit;
		while (getline(ss, data, '\t'))  // Vektördeki veriler tab boşluğuna göre ayrılıyor
		{
			kayit.push_back(data); // Ayrılan veriler kayit vektörüne aktarılıyor
		}
		if (kayit.size() >0) // Kayit doluysa
		{
			oda_listesi.push_back(kayit); // Oluşan liste oda listesine atanıyor
		}
		
	}

}

void oda_listele() // Odaları listeleyen metod 
{
	odalar(); 
	system("CLS"); // Ekran temizleme komutu
	cout << "<===== Oda Listesi =====>\n";
	for each (vector<string> oda in oda_listesi) // Oda listesindeki veriler oda vektörüne aktarılıyor
	{
		cout << oda.at(0) + "\t" + oda.at(1) + "\n"; // Listedeki veriler boşluk olacak şekilde yazdırılıyor
	}

	cout << "\nUst menuye donmek icin bir tusa basin...";
	system("pause>nul");
}

void oda_sil_islem(int i)
{
	oda_listesi.erase(oda_listesi.begin() + i); // Girilen değerdeki vektör siliniyor
	ofstream dosya_yaz;
	dosya_yaz.open("C:\\Users\\AKYILDIZ\\Desktop\\odalar.txt", ios::out); // Odalar dosyası temizleniyor
	for each (vector<string> item in oda_listesi) // Kalan oda listesi bir vektöre aktarılıyor
	{
		dosya_yaz.seekp(-0L, ios::end); // İmleç sona getirliyor
		dosya_yaz << item[0] + "\t" + item[1] + "\n"; // Vektördeki veriler aralarında boşluk olacak şekilde yazdırılıyor
	}

	dosya_yaz.close();

}

void oda_sil() // Silinecek oda numasını girdirip parametre olarak gönderen metod
{
	odalar();
	string oda_no;
	cout << "Silmek istediginiz oda numarasini giriniz..\n";
	cin >> oda_no;
	int sayac = 0;
	int sil_id = 0;
	int vector_size = oda_listesi.size(); // Oda listesi boyutu hesaplanıyor
	for (int i = 0; i < vector_size; i++) // Boyut kadar döndürülüyor
	{
		vector<string> item;
		item = oda_listesi[i];
		if (item[0] == oda_no)
		{
			sayac++;
			sil_id = i;
		}
	}
	if (sayac>0)
	{
		string cvp;
		cout << "Silmek istediğinize emin misiniz? [e/h]";
		cin >> cvp;
		if (cvp == "e")
		{
			oda_sil_islem(sil_id);
			oda_listele();
			system("pause>nul");
		}
	}
	else {
		cout << "Boyle bir oda yok! Devam icin bir tusa basin...";
		system("pause>nul");
		oda_listele();
		system("pause>nul");
	}
	
}




void odaKayitEkle() // Odalara kayıt ekleyen metod
{
	system("CLS"); 
	cout << "<=====  Oda Kaydi Olusturma Sayfasi =====>\n" << endl;

	musteriler();
	cout << "<===== Musteri Listesi =====>\n";
	for each (vector<string> musteri in musteri_listesi) // Müşteri listesini ekrana getiren metod
	{
		cout << musteri.at(0) + "\t" + musteri.at(1) + "\t" + musteri.at(2) + "\t" + musteri.at(3) + "\n";
	}

	cout << endl;
	cout << endl;

	odalar();
	cout << "<===== Oda Listesi =====>\n";
	for each (vector<string> oda in oda_listesi) // Oda listesini ekrana getiren metod
	{
		cout << oda.at(0) + "\t" + oda.at(1) + "\n";
	}
	cout << endl;
	cout << endl;
	
	string id, oda_no, musteri_no;
	cout << "Kayit numarasi, Oda numarasi ve musteri numarasini aralarinda bosluk olacak sekilde giriniz... \n";
	cin >> id >> oda_no >> musteri_no;
	ofstream dosya_yaz;
	dosya_yaz.open("C:\\Users\\AKYILDIZ\\Desktop\\oda_kayitlari.txt", ios::app);
	dosya_yaz.seekp(-0L, ios::end);
	dosya_yaz << id + "\t" + oda_no + "\t" + musteri_no + "\n";
	dosya_yaz.close();

	cout << "Kayit olusturuldu... Kayit eklemeye devam etmek icin [e] tusuna basiniz...";
	string devam;
	cin >> devam;
	if (devam == "e") odaKayitEkle();

}

string odaAdiGetir(int oda_no) // Kayıt için seçilen oda adını veren metod
{
	odalar();
	for each (vector<string> item in oda_listesi)
	{
		if (std::stoi(item[0]) == oda_no)
		{
			return item[1];
		}
	}
}

string musteriAdiGetir(int musteri_no) // Kayıt için müşteri adını getiren metod
{
	musteriler();
	for each (vector<string> item in musteri_listesi)
	{
		int m_no = std::stoi(item[0]);
		if ( m_no == musteri_no)
		{
			return item[1] + "\t"+ item[2];
		}
	}
	
}

void odaKayitlari() // Oda kayıt listesi için yazdıran metod
{


	oda_kayit_listesi.clear();

	ifstream oda_kayitlari_oku;
	oda_kayitlari_oku.open("C:\\Users\\AKYILDIZ\\Desktop\\oda_kayitlari.txt", ios::app);
	if (oda_kayitlari_oku.is_open() != true)
	{
		cout << "Dosya acilamadi!" << endl;
		exit(EXIT_FAILURE);
	}
	string record;
	while (getline(oda_kayitlari_oku, record))
	{
		string data;
		stringstream ss(record);
		vector<string> kayit;
		int sayac = 0;
		while (getline(ss, data, '\t'))
		{

			kayit.push_back(data);
			if (sayac == 1)
			{
				string oda = odaAdiGetir(std::stoi(data));
				kayit.push_back(oda);
			}
			else if (sayac == 2)
			{
				string musteri = musteriAdiGetir(std::stoi(data));
				kayit.push_back(musteri);
			}
			sayac++;
		}
		if (kayit.size() >0)
		{
			oda_kayit_listesi.push_back(kayit);
		}

	}

}

void odaKayitlariListele() // Oda kayıt listesini ekrana yazdıran metod
{
	odaKayitlari();
	system("CLS");
	cout << "<===== Oda Kayit Listesi =====>\n";
	for each (vector<string> oda_kaydi in oda_kayit_listesi) // Oda listesi vektöre aktarılıyor
	{
		cout << oda_kaydi.at(0) + "\t" + oda_kaydi.at(1) + "\t" + oda_kaydi.at(2) + "\t" + oda_kaydi.at(3) + "\t" + oda_kaydi.at(4) + "\n";
	}

	cout << "\nUst menuye donmek icin bir tusa basin...";
	system("pause>nul");
}


void MenuYaz() // Ekrana gelen menuleri yazdıran metod
{
	system("CLS");
	string menu_ogesi[4];
	if (islem[0] == 0)
	{
		menu_ogesi[0] = "[1] - Oda Islemleri";
		menu_ogesi[1] = "[2] - Musteri ISlemleri";
		menu_ogesi[2] = "[3] - Oda Kayit Islemleri";
		menu_ogesi[3] = "[99] - Cikis";
	}
	else
	{
		if (islem[0] == 1) 
		{
			menu_ogesi[0] = "[1] - Oda Ekle";
			menu_ogesi[1] = "[2] - Oda Sil";
			menu_ogesi[2] = "[3] - Odalari Listele";
			menu_ogesi[3] = "[99] - Ust Menu";
		}
		else if (islem[0] == 2)
		{
			menu_ogesi[0] = "[1] - Musteri Ekle";
			menu_ogesi[1] = "[2] - Musteri Sil";
			menu_ogesi[2] = "[3] - Musterileri Listele";
			menu_ogesi[3] = "[99] - Ust Menu";
		}
		else if (islem[0] == 3)
		{
			menu_ogesi[0] = "[1] - Kayit Olustur";
			menu_ogesi[1] = "[2] - Kayitlari Listele";
			menu_ogesi[3] = "[99] - Ust Menu";
		}
	}
	switch (islem[0])
	{
	case 0: cout << "Otel Islemleri" << endl;
		cout << "--------------" << endl;
		break;
	case 1: cout << "Oda Islemleri" << endl;
		    cout << "-------------" << endl;
		break;
	case 2: cout << "Musteri Islemleri" << endl;
		cout << "-------------" << endl;
		break;
	case 3: cout << "Oda Kayit Islemleri" << endl;
		cout << "-------------" << endl;
		break;
	}

	for each (string item in menu_ogesi)
	{
		if (item != "") 
		{
			cout << item << endl;
		}
	}
}

void islemSec()  // Kulanıcının girdiği değerlere göre yönlendiren metod
{
	if (islem[1] == 0)
	{
		switch (islem[0])
		{
		case 1:
			MenuYaz();
			cout << "Seciminiz: ";
			cin >> islem[1];
			islemSec();
			break;
		case 2: 
			MenuYaz();
			cout << "Seciminiz: ";
			cin >> islem[1];
			islemSec();
			break;
		case 3: 
			MenuYaz();
			cout << "Seciminiz: ";
			cin >> islem[1];
			islemSec();
			break;
		case 99: 
			exit(0);
			break;
		default:
			cout << "Hatali secim!!\n";
			cout << "Seciminiz:";
			cin >> islem[0];
			islemSec();
			
			break;
		}
	}
	else {
		if (islem[0] == 1)
		{
			switch (islem[1])
			{
			case 1: 
				odaEkle();
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[1];
				islemSec();
				break;
			case 2: oda_sil();
				oda_listele();
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[1];
				islemSec(); break;
			case 3:
				oda_listele();
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[1];
				islemSec();
				break;
			case 99: 
				islem[0] = 0;
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[0];
				islemSec();
				break;
				default:
					cout << "Hatali secim!!\n";
					cout << "Seciminiz:";
					cin >> islem[1];
					islemSec();
					break;
			}
		}
		else if (islem[0] ==2)
		{
			switch (islem[1])
			{
			case 1: 
				musteriEkle();
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[1];
				islemSec();
				break;
			case 2: musteri_sil(); 
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[1];
				islemSec(); break;
			case 3: 
				musteri_listele();
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[1];
				islemSec();
				break;
			case 99:
				islem[0] = 0;
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[0];
				islemSec();
				break;
			default:
				cout << "Hatali secim!!\n";
				cout << "Seciminiz:";
				cin >> islem[1];
				islemSec();
				break;
			}
		}
		else if (islem[0] == 3)
		{
			switch (islem[1])
			{
			case 1:
				odaKayitEkle();
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[1];
				islemSec();
				break;
			case 2:
				odaKayitlariListele();
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[1];
				islemSec();
				break;

			case 99:
				islem[0] = 0;
				islem[1] = 0;
				MenuYaz();
				cout << "Seciminiz: ";
				cin >> islem[0];
				islemSec();
				break;
			default:
				cout << "Hatali secim!!\n";
				cout << "Seciminiz:";
				cin >> islem[1];
				islemSec();
				break;
			}
		}
	}
}


	

void AnaMenu() // Programı başlatan metod
{
	MenuYaz();
	cout << "Seciminiz: ";
	cin >> islem[0];
	islemSec();
}

	

int main()
{
	setlocale(LC_ALL, "Turkish");

	AnaMenu();
	//odaEkle();
    return 0;
}


