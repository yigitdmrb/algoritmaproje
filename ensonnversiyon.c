#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h> 
#include<unistd.h>  
void oyunbasladi();
int main();
short rakiphasar[3] = {9, 12, 16};//diziler ve değişkenler global tanımladık ki fonksiyolarda değiştirebilelim
short rakipcan[3] = {60, 80, 100};
short canimiz = 80, hasarimiz = 1200, bolum = 0;

void rakipsaldiri()
{
    canimiz -= rakiphasar[bolum];
}
void rakipkarindesen()
{
    canimiz -= (rakiphasar[bolum] - 5);
}
void bizimsaldiri()
{
    rakipcan[bolum] -= hasarimiz;
}
void bizimkarindesen()
{
    rakipcan[bolum] -= (hasarimiz - 5);
}
void devamke()//kaldığmız yerden devam ettir
{

  FILE *file;
     file=fopen("stage.txt","r");
  fscanf(file, "%d", &bolum);//dosyadaki sayıyı alıp bölüm değişkenine atıyor.
  if(bolum==3)
  bolum=2;
  fclose(file);
    oyunbasladi();

}
void hikaye()
{
    char secimh;
    do
    {

        FILE *readwarrior;
        readwarrior = fopen("read.txt", "r"); // hikayeyi burda yazdırıyoruz
        char line[3400];
        fgets(line, sizeof(line), readwarrior);
        printf("%s", line);
        fclose(readwarrior);
        
        printf("\n\t\t\t\tOYUNA GEC(1) MENUYE DON(2)");
        secimh = getch();

        if (secimh == '1'){
            sleep(1);
            system("cls");
            oyunbasladi();}

        else if (secimh == '2')
        {
        system("cls");
            main();
        }
        else{
            printf("\n\t\t\t\tGecerli bir secim yapiniz.");
            sleep(1);
            system("cls");
        
        }
    } while (secimh != '1' && secimh != '2');

}

void kilavuz()//oyun oynanış
{
    char secimk;
    do
    {
        printf("SALDIR : Rakibin kafasini hedef alarak yuksek hasar vurur.\n");
        printf("KALKAN AC : Kalkan acarak kafasini korur eger ki rakip karindesen hamlesi yaparsa hasar alinir.\n");
        printf("KARINDESEN : rakibin karnini hedef alarak dusuk hasar vurur kalkana karsi etkili bir hamledir.\n");
        printf("\t\t\t\tOYUNA GEC(1) MENUYE DON(2)");
        secimk = getch();
        if (secimk == '1')
        {
        system("cls");
            oyunbasladi(); 
        }
        else if (secimk == '2')
        {
        system("cls");
            main();
        }
        else
            printf("\t\t\t\tgeçerli bir seçim yapiniz.");

    } while (secimk != '1' && secimk != '2');
}

void hamlesonrasi(short a, short b)
{
    if (a <= 0 && b <= 0)// aynı anda iki tarafta ölürse
    {
        printf("\n\t\t\t\tRakip ve sen birbirinizi ayni anda oldurdunuz.\n");
        printf("\n\n\n\t\t\t\t     Berabere\n\n\t\t\t\t O-<--<    O-<--<\n");
    }

    else if (a <= 0)// ölürsek
    {
        printf("\n\t\t\t\tOldunuz\n");
        printf("\t\t\t\t   #f        | O\n\t\t\t\t 	     T/|\\]\n\t\t\t\t O-<--<       / \\\n\n");
    }
    else if (b <= 0)//kazanırsak
    {
        printf("\n\t\t\t\tRakip katledildi\n");
        printf("\t\t\t\t  O |         #gg\n\t\t\t\t[/|\\T\n\t\t\t\t / \\         O-<--<\n\n");
            FILE *fp; // kaldığımız bolumu stage.txt dosyasına yazdılıyor.
            fp = fopen("stage.txt", "w");
            if (fp == NULL)
            {
                printf("Dosya acilamadi!\n");
            }
            fprintf(fp, "%d", (bolum+1)); // dosyaya bolum değişkenini yazdırır.
            fclose(fp);
        
    }
    else//berabere kalma durumu
    {
        printf("\n\t\t\t\t%d=<3            %d=<3", a, b); // canimiz  = rakipcan
        printf("\n\t\t\t\t  O              O\n\t\t\t\t[/|\\/	       \\/|\\]\n\t\t\t\t / \\            / \\ \n");
    }
}

void bolumbaslangici(int bolum){// bolum baslangic animasyonu
    system("cls");
    for(int i=0;i<1;i++){   
        printf("\n\n\t\t\t\t%d. bolume geciyoruz.\n\n", bolum + 1);
        sleep(1);system("cls");
        printf("\n\n\t\t\t\t%d. bolume geciyoruz..\n\n", bolum + 1);
        sleep(1);system("cls");
        printf("\n\n\t\t\t\t%d. bolume geciyoruz...\n\n", bolum + 1);
        sleep(1);system("cls");
}
}
void oyunsonlandi(){// oyun bitince tekrar oynama menüsü 
            
            char c;
            system("cls");
            printf("\n\n\n\n\t\t\t\tOYUN BITTI :( ");
            sleep(2);
            system("cls");
            printf("\n\n\n\n\t\t\t\tBASTAN BASLA(1) BOLUMU TEKRAR OYNA(2) CIKIS(3)");
            c=getch();
            switch(c){            
            case '1':
                bolum=0;
            for(int i=0;i<3;i++){//for döngüleri rakip canları eski haline getirmek icin
                rakipcan[i]=60+i*20;
            }
                oyunbasladi();
                break;
            
            case '2':

            for(int i=0;i<3;i++){
                rakipcan[i]=60+i*20;
            
            }
                oyunbasladi();
                break;

            case '3':
            for(int i=0;i<3;i++){
            rakipcan[i]=60+i*20;
            }
                bolum=3;
                break;
            }
            
}

void oyunbasladi()// oyun bu fonksiyonda oynatılıyor
{
    srand(time(NULL));
    short rakiphamle = 0;
    short bizimhamlemiz = 0;

    while (bolum < 3)
    {
        
        canimiz = 80;
        bolumbaslangici(bolum);
        
        system("cls");

        while (canimiz > 0 && rakipcan[bolum] > 0)
        { // burayı direkt fonksiyon yapabiliriz while ın tamamını
            rakiphamle = rand() % 3 + 1;
            printf("\n\n\n\n\t\t\t\tHAMLE ICIN PARANTEZ ICINDEKI SAYIYI GIRINIZ.\n");
            printf("\n\n\t\t\t\t  O |          | O\n\t\t\t\t[/|\\T	       T/|\\]\n\t\t\t\t / \\            / \\\n");
            printf("\t\t\t\tSALDIR(1)  KALKAN AC(2)  KARINDESEN(3)   HAMLENIZ: \n");
            hamlesonrasi(canimiz, rakipcan[bolum]);
            bizimhamlemiz = getch();
            system("cls");
            switch (rakiphamle)//rakip hamlesi rastgele veriyolor ve olası tüm durumların animasyonu veriliyor.
            {
            case 1:                       // rakip saldırıyor
                if (bizimhamlemiz == '1') // saldırı saldırı
                {
                    printf("\n\n\n\n\t\t\t\tSaldiriyoruz\n");
                    printf("\n\n\t\t\t\t         O    O\n\t\t\t\t       [/|\\/\\/|\\]\n\t\t\t\t        / \\  / \\\n");
                    printf("\t\t\t\tRakip de saldiriyor.\n");
                    rakipsaldiri();
                    bizimsaldiri();
                    hamlesonrasi(canimiz, rakipcan[bolum]);
                }
                else if (bizimhamlemiz == '2')
                { // Kalkan-saldırı
                    printf("\n\n\n\n\t\t\t\tKalkan actik\n");
                    printf("\n\n\t\t\t\t     | O    O\n\t\t\t\t     T/|\\]\\/|\\]\n\t\t\t\t      / \\  / \\\n");
                    printf("\t\t\t\tKalkan rakibin saldirisini engelledik\n");
                    hamlesonrasi(canimiz, rakipcan[bolum]);
                    
                }
                else if (bizimhamlemiz == '3')
                {
                    printf("\n\n\n\n\t\t\t\tRakibin karnina saldirdik\n");
                    printf("\n\n\t\t\t\t       O     O\n\t\t\t\t     [/|\\__\\/|\\]\n\t\t\t\t      / \\   / \\\n");
                    printf("\n\t\t\t\tRakipse duz saldirdi\n");
                    rakipsaldiri();
                    bizimkarindesen();
                    hamlesonrasi(canimiz, rakipcan[bolum]);
                }
                else
                    printf("\n\t\t\t\tTekrar hamle giriniz\n");
                break;
            case 2: // rakip kalkan
                if (bizimhamlemiz == '1')
                {
                    printf("\n\n\n\n\t\t\t\tSaldiriyoruz\n");
                    printf("\n\n\t\t\t\t       O    O |\n\t\t\t\t     [/|\\/[/|\\T\n\t\t\t\t      / \\  / \\\n");
                    printf("\t\t\t\tRakibin kalkani saldirimizi engelledi\n");
                    hamlesonrasi(canimiz, rakipcan[bolum]);
                }
                else if (bizimhamlemiz == '2')
                {
                    printf("\n\n\n\n\t\t\t\tKalkan actik\n");
                    printf("\n\n\t\t\t\t     | O    O |\n\t\t\t\t     T/|\\][/|\\T\n\t\t\t\t      / \\  / \\\n");
                    printf("\t\t\t\tRakipte kalkan acti (bakisiyorsunuz :D)\n");
                    hamlesonrasi(canimiz, rakipcan[bolum]);
                }
                else if (bizimhamlemiz == '3')
                {
                    printf("\n\n\n\n\t\t\t\tRakibin karnina saldiriyoruz\n");
                    printf("\n\n\t\t\t\t       O     O |\n\t\t\t\t     [/|\\__[/|\\T\n\t\t\t\t      / \\   / \\\n");
                    printf("\t\t\t\tRakip kalkan acti fakat kalkani asip karnina saldirdik\n");
                    bizimkarindesen();
                    hamlesonrasi(canimiz, rakipcan[bolum]);
                }
                else
                    printf("\n\n\n\n\t\t\t\tTekrar hamle giriniz\n");
                break;

            case 3: // rakip karındesen
                if (bizimhamlemiz == '1')
                {
                    printf("\n\n\n\n\t\t\t\tSaldiriyoruz\n");
                    printf("\n\n\t\t\t\t       O     O\n\t\t\t\t     [/|\\/__/|\\]\n\t\t\t\t      / \\   / \\\n");
                    printf("\t\t\t\tRakip karnimiza saldirdi bizse duz saldirdik\n");
                    rakipkarindesen();
                    bizimsaldiri();
                    hamlesonrasi(canimiz, rakipcan[bolum]);
                }
                else if (bizimhamlemiz == '2')
                {
                    printf("\n\n\n\n\t\t\t\tKalkan actik\n");
                    printf("\n\n\t\t\t\t     | O     O\n\t\t\t\t     T/|\\]__/|\\]\n\t\t\t\t      / \\   / \\\n");
                    printf("\t\t\t\tRakip kalkanimizi asip karnimiza saldirdi\n");
                    rakipkarindesen();
                    hamlesonrasi(canimiz, rakipcan[bolum]);
                }
                else if (bizimhamlemiz == '3')
                {
                    printf("\n\n\n\n\t\t\t\tRakibin karnina saldiriyoruz\n");
                    printf("\n\n\t\t\t\t       O       O\n\t\t\t\t     [/|\\__ __/|\\]\n\t\t\t\t      / \\     / \\\n");
                    printf("\t\t\t\tRakipte karnimiza saldirdi\n");
                    bizimkarindesen();
                    rakipkarindesen();
                    hamlesonrasi(canimiz, rakipcan[bolum]);
                }
                else
                    printf("\n\n\n\n\t\t\t\tTekrar hamle giriniz\n");
                break;
            }
            sleep(3);
            system("cls");
        }
        if (canimiz > 0)
        {
            if (bolum == 2)//bölüm 3 bitince olucaklar yani bitiş ekranı
            {
                   for(int i = 0;i<4;i++){
    system("cls");
    printf(" \n\n\n\n \t\t\t\t<OYUNU KAZANDINIZ>\n  \t\t\t\t   ***** _ *****\n \t\t\t\t   *     O     *\n \t\t\t\t   *    /|\\    *\n  \t\t\t\t   *    / \\    *\n \t\t\t\t   *************");
    sleep(1);
    system("cls");
    printf(" \n\n\n\n \t\t\t\t<OYUNU KAZANDINIZ>\n  \t\t\t\t   ***** _ *****\n \t\t\t\t   *    \\O/    *\n \t\t\t\t   *     |     *\n \t\t\t\t   *    / \\    *\n \t\t\t\t   *************");
    sleep(1);    
     }
              oyunsonlandi();
            }
            else
                bolum++;
        }
        
            

    }
}

int main()//burda seçim yapılcak oyun fonksiyonları yukarıdakiler
{
    char secim;
    do
    {
        printf("\n\t\t\t\tHIKAYEYI DINLE(1)  KILAVUZ(2)  OYUNA GEC(3)  KALDIGIN YERDEN DEVAM ET(4) \n\t\t\t\t  SECIM YAPMAK ICIN PARANTEZ ICINDEKI SAYIYI GIRINIZ : \n");
        secim = getch();
        switch (secim)
        {
        case '1':
                sleep(1);
                system("cls");
            hikaye();
            break;

        case '2':
            sleep(1);
            system("cls");
            kilavuz();
            break;

        case '3':
            sleep(1);
            system("cls");
            oyunbasladi();
            break;

        case '4':
            sleep(1);
            system("cls");
            devamke(); 
            break;
        default:
            sleep(1);
            system("cls");
            printf("\n\t\t\t\tGecerli bir sayi giriniz.\n");
            break;
        }
    } while ((secim != '1' && secim != '2') && (secim != '3' && secim != '4'));
}