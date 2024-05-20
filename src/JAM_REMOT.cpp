#include <IRremote.h>
#include "Wire.h"
#include <EEPROM.h>
#include "PrayerTimes.h"
#include "Sodaq_DS3231.h"
#define led 13
#define relay 11
#define buzzer 12
#define up A0
#define ok A1
#define down A2
int RECV_PIN = A3;

String wadahremot = "";
int hasil_remot = 0;
byte tahan = 0;
double times[sizeof(TimeName) / sizeof(char *)];
byte value_ihti = 1, ims = 9;
int jame, menite, tanggal, bulan, tahun, har, yes;

#define LATCH_3 8
#define DATA_3 9
#define CLK_3 10

#define LATCH_2 5
#define DATA_2 6
#define CLK_2 7

#define LATCH_1 4
#define DATA_1 3
#define CLK_1 2

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long data;
boolean hidup = 0;
byte lanjut = 0;
byte position = 0;
byte blink_dots = 0;
boolean pinstate = true;
int imsakjam, imsakmen, subuhjam, subuhmen, dzuhurjam, dzuhurmen, asharjam, asharmen, maghribjam, maghribmen, isyajam, isyamen;
byte Uimsakjam, Uimsakmen, Usubuhjam, Usubuhmen, Udzuhurjam, Udzuhurmen, Uasharjam, Uasharmen, Umaghribjam, Umaghribmen, Uisyajam, Uisyamen;
byte Limsakjam, Limsakmen, Lsubuhjam, Lsubuhmen, Ldzuhurjam, Ldzuhurmen, Lasharjam, Lasharmen, Lmaghribjam, Lmaghribmen, Lisyajam, Lisyamen;
byte Ljam, Ujam, Lmenit, Umenit, Ltanggal, Utanggal, Lbulan, Ubulan, Ltahun, Utahun, waktusholat;
int jammati, jamhidup, menitmati, menithidup, saat_ini, saat_mati, saat_hidup, i = 0;
char wadah;
byte Lhtanggal, Uhtanggal, Lhbulan, Uhbulan, Lhtahun, Uhtahun, Lsuhu, Usuhu, roling, count, count1 = 0;

byte digitTgl[10] = {0b10000010, 0b10101111, 0b11000100, 0b10000101, 0b10101001, 0b10010001, 0b10010000, 0b10100111, 0b10000000, 0b10000001};
byte digitjam[10] = {0b10000001, 0b11101101, 0b01000010, 0b01001001, 0b00101101, 0b00011001, 0b00010001, 0b11001101, 0b00000001, 0b00001001};
byte digitdot[10] = {0b10000000, 0b10110111, 0b01000010, 0b00010011, 0b00110101, 0b00011001, 0b00001001, 0b10110011, 0b00000001, 0b00010001};

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Wire.begin();
  rtc.begin();

  pinMode(up, INPUT);
  pinMode(ok, INPUT);
  pinMode(down, INPUT);
  pinMode(relay, OUTPUT);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  digitalWrite(up, HIGH);
  digitalWrite(ok, HIGH);
  digitalWrite(down, HIGH);

  pinMode(led, OUTPUT);
  pinMode(LATCH_1, OUTPUT);
  pinMode(CLK_1, OUTPUT);
  pinMode(DATA_1, OUTPUT);

  pinMode(LATCH_2, OUTPUT);
  pinMode(CLK_2, OUTPUT);
  pinMode(DATA_2, OUTPUT);

  pinMode(LATCH_3, OUTPUT);
  pinMode(CLK_3, OUTPUT);
  pinMode(DATA_3, OUTPUT);
  digitalWrite(relay, LOW);
  bep();
  bep();
  bep();
  DateTime now = rtc.now();
}

void loop()
{
  DateTime now = rtc.now();
  digitalWrite(relay, LOW);
  cektmenu();
  counteriqomah();
  dot();
  if (hidup == 0)
  {
    tampiljam();
    tampiljadwal();
    ganti();
  }
  else
  {
    mati();
  }
}
void counteriqomah()
{
  DateTime now = rtc.now();
  if (imsakjam == now.hour() && imsakmen == now.minute() && now.second() == 0)
  {
    imsaq();
  }
  if (subuhjam == now.hour() && subuhmen == now.minute() && now.second() == 0)
  {
    matikantanggal();
    waktusholat = 2;
    counter();
  }
  if (dzuhurjam == now.hour() && dzuhurmen == now.minute() && now.second() == 0)
  {
    matikantanggal();
    waktusholat = 3;
    counter();
  }
  if (asharjam == now.hour() && asharmen == now.minute() && now.second() == 0)
  {
    matikantanggal();
    waktusholat = 4;
    counter();
  }
  if (maghribjam == now.hour() && maghribmen == now.minute() && now.second() == 0)
  {
    matikantanggal();
    waktusholat = 5;
    counter();
  }
  if (isyajam == now.hour() && isyamen == now.minute() && now.second() == 0)
  {
    matikantanggal();
    waktusholat = 6;
    counter();
  }
}

void imsaq()
{

  digitalWrite(buzzer, HIGH);
  matikantanggal();
  tampilimsak();
  delay(1000);

  digitalWrite(buzzer, LOW);
  matikantanggal();
  matikanjadwal();
  delay(1000);
  digitalWrite(buzzer, HIGH);
  matikantanggal();
  tampilimsak();
  delay(1000);

  digitalWrite(buzzer, LOW);
  matikantanggal();
  matikanjadwal();
  delay(1000);
  digitalWrite(buzzer, HIGH);
  matikantanggal();
  tampilimsak();
  delay(1000);

  digitalWrite(buzzer, LOW);
  matikantanggal();
  matikanjadwal();
  delay(1000);
  digitalWrite(buzzer, HIGH);
  matikantanggal();
  tampilimsak();
  delay(1000);

  digitalWrite(buzzer, LOW);
  matikantanggal();
  matikanjadwal();
  delay(1000);
  digitalWrite(buzzer, HIGH);
  matikantanggal();
  tampilimsak();
  delay(1000);

  digitalWrite(buzzer, LOW);
  matikantanggal();
  matikanjadwal();
  delay(1000);
  digitalWrite(buzzer, HIGH);
  matikantanggal();
  tampilimsak();
  delay(1000);

  digitalWrite(buzzer, LOW);
  matikantanggal();
  matikanjadwal();
  delay(1000);
}

void counter()

{ // matikanjadwal();
  iqotext();
  digitalWrite(relay, HIGH);

  if (waktusholat == 2)
  {
    count = EEPROM.read(0);
  }
  if (waktusholat == 3)
  {
    count = EEPROM.read(1);
  }
  if (waktusholat == 4)
  {
    count = EEPROM.read(2);
  }
  if (waktusholat == 5)
  {
    count = EEPROM.read(3);
  }
  if (waktusholat == 6)
  {
    count = EEPROM.read(4);
  }
  digitalWrite(buzzer, HIGH);
  bacawaktusholat();
  delay(1000);
  digitalWrite(buzzer, LOW);
  matikanjadwal();
  delay(1000);
  digitalWrite(buzzer, HIGH);
  bacawaktusholat();
  delay(1000);
  digitalWrite(buzzer, LOW);
  matikanjadwal();
  delay(1000);
  digitalWrite(buzzer, HIGH);
  bacawaktusholat();
  delay(1000);
  digitalWrite(buzzer, LOW);
  matikanjadwal();
  delay(1000);

  bacawaktusholat();
  if (count == 0)
  {
    asm volatile("  jmp 0");
  }
  while (1)
  {
    bacawaktusholat();
    if (count == 0 && count1 == 0)
    {
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(100);
      padam();
      asm volatile("  jmp 0");
    }
    if (count1 == 0)
    {
      count--;
      count1 = 59;
    }
    count1--;
    delay(1000);

    Ljam = count / 10;
    Ujam = count - Ljam * 10;

    Lmenit = count1 / 10;
    Umenit = count1 - Lmenit * 10;

    digitalWrite(LATCH_1, LOW);
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Umenit]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitdot[Lmenit]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ujam]);   // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ljam]);   // digitTwo
    digitalWrite(LATCH_1, HIGH);
  }
}

void padam()

{
  while (1)
  {
    digitalWrite(relay, HIGH);
    mati();
    dot();
    i++;
    delay(1000);
    if (i > 240)
    {
      asm volatile("  jmp 0");
    }
  }
}
void dot()
{
  DateTime now = rtc.now();
  byte lowersec = now.second() / 10;
  byte uppersec = now.second() - lowersec * 10;
  if (blink_dots != uppersec)
  {
    pinstate = !pinstate; // toggle the dots state
    if (pinstate == 1)
    {
      digitalWrite(led, HIGH);
    }
    else
      digitalWrite(led, LOW);
    blink_dots = uppersec;
  }
}
void mati()
{
  digitalWrite(relay, HIGH);
  matikanjam();
  matikanjadwal();
  matikantanggal();
}
void ganti()
{
  DateTime now = rtc.now();
  if (now.second() <= 10)
  {
    tampilhari1();
  }
  if (now.second() > 10)
  {
    tampiltanggal();
  }
}
void cektmenu()
{
  if (irrecv.decode(&results))
  {

    data = results.value;
    Serial.println(results.value);
    irrecv.resume();

    switch (data)
    {
    case 16726215: // MENU / OK
      bep();
      cekmenu();
      break;
    case 16718055: // UP
      bep();
      cekiqo();
      break;
    case 16738455: // POWER
      bep();
      if (hidup == 0)
      {
        hidup = 1;
      }
      else
      {
        hidup = 0;
      }
      break;
    }
  }

  if (digitalRead(ok) == 0)
  {
    delay(500);
    bep();
    cekmenu();
  }

  if (digitalRead(up) == 0)
  {
    delay(500);
    bep();
    cekiqo();
  }
}

void cekmenu()
{
  DateTime now = rtc.now();
  digitalWrite(relay, HIGH);
  lanjut = 0;
  matikanjadwal();
  matikantanggal();
  jame = now.hour();
  roling = 2;
  wadahremot = String(jame);
  while (1)
  {
    bacaremot();
    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      jame++;
      delay(300);
      wadahremot = String(jame);
    }
    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      jame--;
      delay(300);
      wadahremot = String(jame);
    }
    jame = wadahremot.toInt();

    if (jame < 0)
    {
      jame = 23;
    }
    if (jame > 23)
    {
      jame = 0;
    }

    Ljam = jame / 10;
    Ujam = jame - Ljam * 10;

    digitalWrite(LATCH_1, LOW);
    shiftOut(DATA_1, CLK_1, MSBFIRST, 0b11111111);     // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, 0b11111111);     // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ujam]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ljam]); // digitTwo
    digitalWrite(LATCH_1, HIGH);

    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(500);
      aturmenit();
    }
  }
}

void aturmenit()
{
  DateTime now = rtc.now();
  lanjut = 0;
  matikanjadwal();
  matikantanggal();
  menite = now.minute();
  roling = 2;
  wadahremot = String(menite);
  while (1)
  {
    bacaremot();
    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      menite++;
      delay(300);
      wadahremot = String(menite);
    }

    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      menite--;
      delay(300);
      wadahremot = String(menite);
    }
    menite = wadahremot.toInt();
    if (menite > 59)
    {
      menite = 0;
    }
    if (menite < 0)
    {
      menite = 59;
    }
    Lmenit = menite / 10;
    Umenit = menite - Lmenit * 10;

    digitalWrite(LATCH_1, LOW);
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Umenit]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitdot[Lmenit]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, 0b11111111);       // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, 0b11111111);       // digitTwo
    digitalWrite(LATCH_1, HIGH);

    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(500);
      aturtanggal();
    }
  }
}

void aturtanggal()
{
  DateTime now = rtc.now();
  lanjut = 0;
  tanggal = now.date();
  roling = 2;
  wadahremot = String(tanggal);
  matikanjam();
  matikanjadwal();
  while (1)
  {
    bacaremot();
    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      tanggal++;
      delay(300);
      wadahremot = String(tanggal);
    }

    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      tanggal--;
      delay(300);
      wadahremot = String(tanggal);
    }

    tanggal = wadahremot.toInt();

    if (tanggal > 31)
    {
      tanggal = 1;
    }
    if (tanggal < 1)
    {
      tanggal = 31;
    }

    Ltanggal = tanggal / 10;
    Utanggal = tanggal - Ltanggal * 10;
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);         // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);         // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);         // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);         // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);         // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);         // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Utanggal]); // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Ltanggal]); // digitTwo
    digitalWrite(LATCH_2, HIGH);

    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(500);
      aturbulan();
    }
  }
}

void aturbulan()
{
  DateTime now = rtc.now();
  lanjut = 0;
  bulan = now.month();
  roling = 2;
  wadahremot = String(bulan);
  matikanjadwal();
  while (1)
  {
    bacaremot();

    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      bulan++;
      delay(300);
      wadahremot = String(bulan);
    }

    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      bulan--;
      delay(300);
      wadahremot = String(bulan);
    }
    bulan = wadahremot.toInt();
    if (bulan > 12)
    {
      bulan = 1;
    }
    if (bulan < 1)
    {
      bulan = 12;
    }

    Lbulan = bulan / 10;
    Ubulan = bulan - Lbulan * 10;
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Ubulan]); // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Lbulan]); // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo
    digitalWrite(LATCH_2, HIGH);

    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(500);
      aturtahun();
    }
  }
}

void aturtahun()
{
  DateTime now = rtc.now();
  lanjut = 0;
  tahun = now.year() - 2000;
  roling = 2;
  wadahremot = String(tahun);
  matikanjadwal();
  while (1)
  {
    bacaremot();
    if (tahun < 0)
    {
      tahun = 99;
    }
    if (tahun > 99)
    {
      tahun = 0;
    }
    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      tahun++;
      delay(300);
      wadahremot = String(tahun);
    }

    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      tahun--;
      delay(300);
      wadahremot = String(tahun);
    }
    tahun = wadahremot.toInt();
    Ltahun = tahun / 10;
    Utahun = tahun - Ltahun * 10;
    digitalWrite(LATCH_2, LOW);

    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Utahun]); // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Ltahun]); // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[0]);      // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[2]);      // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);       // digitTwo

    digitalWrite(LATCH_2, HIGH);

    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(500);
      aturhari();
    }
  }
}

void aturhari()
{
  DateTime now = rtc.now();
  lanjut = 0;
  har = now.dayOfWeek();
  tampilhari();
  matikanjadwal();
  while (1)
  {
    bacaremot();
    if (har > 7)
    {
      har = 1;
    }
    if (har < 1)
    {
      har = 7;
    }
    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      har++;
      delay(300);
    }

    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      har--;
      delay(300);
    }

    tampilhari();
    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      // bep();
      delay(500);
      DateTime dt(tahun, bulan, tanggal, jame, menite, 55, har);
      rtc.setDateTime(dt);
      delay(500);
      asm volatile("  jmp 0");
    }
  }
}
void matikanjadwal()
{
  digitalWrite(LATCH_3, LOW);

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  digitalWrite(LATCH_3, HIGH);
}

void matikantanggal()
{
  digitalWrite(LATCH_2, LOW);
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); // digitTwo
  digitalWrite(LATCH_2, HIGH);
}

void iqotext()
{
  digitalWrite(LATCH_2, LOW);
  // shiftOut(DATA_2, CLK_2, MSBFIRST,  0b.cdbafge); // U
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10111000);  // h
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100);  // A
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100011);  // M
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11100010);  // M
  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[0]); // o
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100001);  // q
  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[1]); // i
  shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  // digitTwo
  digitalWrite(LATCH_2, HIGH);
}

void matikanjam()

{
  digitalWrite(LATCH_1, LOW);
  shiftOut(DATA_1, CLK_1, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_1, CLK_1, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_1, CLK_1, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_1, CLK_1, MSBFIRST, 0b11111111); // digitTwo
  digitalWrite(LATCH_1, HIGH);
}

void tampiljam()
{
  DateTime now = rtc.now();
  konversijam();
  digitalWrite(LATCH_1, LOW);
  shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Umenit]); // digitTwo
  shiftOut(DATA_1, CLK_1, MSBFIRST, digitdot[Lmenit]);
  shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ujam]); // digitTwo
  shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ljam]); // digitTwo
  digitalWrite(LATCH_1, HIGH);
}
void JadwalSholat()
{

  DateTime now = rtc.now();

  int tahun1 = now.year();
  int bulan1 = now.month();
  int tanggal1 = now.date();

  int dst = 7;

  set_calc_method(ISNA);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);

  float latitude = -7.67;
  float longitude = 109.66083;

  get_prayer_times(tahun1, bulan1, tanggal1, latitude, longitude, dst, times);
}
void bacajadwal()
{
  JadwalSholat();

  get_float_time_parts(times[0], imsakjam, imsakmen);
  imsakmen = imsakmen - ims;
  if (imsakmen < 0)
  {
    imsakmen = imsakmen + 60;
    imsakjam--;
  }

  get_float_time_parts(times[0], subuhjam, subuhmen);
  subuhmen = subuhmen + value_ihti;
  if (subuhmen >= 60)
  {
    subuhmen = subuhmen - 60;
    subuhjam++;
  }

  get_float_time_parts(times[2], dzuhurjam, dzuhurmen);
  dzuhurmen = dzuhurmen + value_ihti;
  if (dzuhurmen >= 60)
  {
    dzuhurmen = dzuhurmen - 60;
    dzuhurjam++;
  }

  get_float_time_parts(times[3], asharjam, asharmen);
  asharmen = asharmen + value_ihti;
  if (asharmen >= 60)
  {
    asharmen = asharmen - 60;
    asharjam++;
  }

  get_float_time_parts(times[5], maghribjam, maghribmen);
  maghribmen = maghribmen + value_ihti;
  if (maghribmen >= 60)
  {
    maghribmen = maghribmen - 60;
    maghribjam++;
  }

  get_float_time_parts(times[6], isyajam, isyamen);
  isyamen = isyamen + value_ihti;
  if (isyamen >= 60)
  {
    isyamen = isyamen - 60;
    isyajam++;
  }
}
void tampiljadwal()
{
  bacajadwal();
  konversijadwal();
  digitalWrite(LATCH_3, LOW);

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uisyamen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lisyamen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uisyajam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lisyajam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Umaghribmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lmaghribmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Umaghribjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lmaghribjam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uasharmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lasharmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uasharjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lasharjam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Udzuhurmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Ldzuhurmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Udzuhurjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Ldzuhurjam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Usubuhmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lsubuhmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Usubuhjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lsubuhjam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uimsakmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Limsakmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uimsakjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Limsakjam]); // digitTwo

  digitalWrite(LATCH_3, HIGH);
}
void konversijam()
{
  DateTime now = rtc.now();
  Ljam = now.hour() / 10;
  Ujam = now.hour() - Ljam * 10;

  Lmenit = now.minute() / 10;
  Umenit = now.minute() - Lmenit * 10;
}
void tampiltanggal()
{
  konversitanggal();
  digitalWrite(LATCH_2, LOW);

  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Utahun]);   // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Ltahun]);   // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[0]);        // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[2]);        // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Ubulan]);   // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Lbulan]);   // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Utanggal]); // digitTwo
  shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[Ltanggal]); // digitTwo

  digitalWrite(LATCH_2, HIGH);
}
void konversijadwal()

{
  Limsakjam = imsakjam / 10;
  Uimsakjam = imsakjam - Limsakjam * 10;
  Limsakmen = imsakmen / 10;
  Uimsakmen = imsakmen - Limsakmen * 10;

  Lsubuhjam = subuhjam / 10;
  Usubuhjam = subuhjam - Lsubuhjam * 10;
  Lsubuhmen = subuhmen / 10;
  Usubuhmen = subuhmen - Lsubuhmen * 10;

  Ldzuhurjam = dzuhurjam / 10;
  Udzuhurjam = dzuhurjam - Ldzuhurjam * 10;
  Ldzuhurmen = dzuhurmen / 10;
  Udzuhurmen = dzuhurmen - Ldzuhurmen * 10;

  Lasharjam = asharjam / 10;
  Uasharjam = asharjam - Lasharjam * 10;
  Lasharmen = asharmen / 10;
  Uasharmen = asharmen - Lasharmen * 10;

  Lmaghribjam = maghribjam / 10;
  Umaghribjam = maghribjam - Lmaghribjam * 10;
  Lmaghribmen = maghribmen / 10;
  Umaghribmen = maghribmen - Lmaghribmen * 10;

  Lisyajam = isyajam / 10;
  Uisyajam = isyajam - Lisyajam * 10;
  Lisyamen = isyamen / 10;
  Uisyamen = isyamen - Lisyamen * 10;
}

void konversitanggal()

{
  DateTime now = rtc.now();
  yes = now.year() - 2000;
  Ltanggal = now.date() / 10;
  Utanggal = now.date() - Ltanggal * 10;

  Lbulan = now.month() / 10;
  Ubulan = now.month() - Lbulan * 10;

  Ltahun = yes / 10;
  Utahun = yes - Ltahun * 10;
}
void tampilhari()
{
  switch (har)
  {

  case 1:
    digitalWrite(LATCH_2, LOW);
    // shiftOut(DATA_2, CLK_2, MSBFIRST,  0b.cdbafge); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001100); // d
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100); // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10111000); // h
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100); // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 2:
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100010);  // N
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[1]); // I
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100010);  // N
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11000000);  // E
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 3:
    digitalWrite(LATCH_2, LOW);
    // shiftOut(DATA_2, CLK_2, MSBFIRST,  0b.cdbafge); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100);  // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100);  // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11011010);  // L
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11000000);  // E
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 4:
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001010); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10011000); // B
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100); // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11110010); // R
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 5:
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[1]); // I
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100011);  // M
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11100010);  // M
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100);  // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10110000);  // K
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 6:
    digitalWrite(LATCH_2, LOW);
    // shiftOut(DATA_2, CLK_2, MSBFIRST,  0b.cdbafge); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11011000); // T
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100); // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100011); // M
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11100010); // M
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001010); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001111); // J
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 7:
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001010);  // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11011000);  // T
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10011000);  // B
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100);  // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    digitalWrite(LATCH_2, HIGH);
    break;
  }
}
void tampilhari1()
{
  DateTime now = rtc.now();
  switch (now.dayOfWeek())
  {

  case 1:
    digitalWrite(LATCH_2, LOW);
    // shiftOut(DATA_2, CLK_2, MSBFIRST,  0b.cdbafge); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001100); // d
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100); // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10111000); // h
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100); // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 2:
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100010);  // N
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[1]); // I
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100010);  // N
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11000000);  // E
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 3:
    digitalWrite(LATCH_2, LOW);
    // shiftOut(DATA_2, CLK_2, MSBFIRST,  0b.cdbafge); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100);  // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100);  // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11011010);  // L
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11000000);  // E
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 4:
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001010); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10011000); // B
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100); // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11110010); // R
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 5:
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[1]); // I
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100011);  // M
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11100010);  // M
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100);  // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10110000);  // K
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 6:
    digitalWrite(LATCH_2, LOW);
    // shiftOut(DATA_2, CLK_2, MSBFIRST,  0b.cdbafge); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11011000); // T
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100); // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10100011); // M
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11100010); // M
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001010); // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001111); // J
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111); //
    digitalWrite(LATCH_2, HIGH);
    break;

  case 7:
    digitalWrite(LATCH_2, LOW);
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10001010);  // U
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11011000);  // T
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10011000);  // B
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b10000100);  // A
    shiftOut(DATA_2, CLK_2, MSBFIRST, digitTgl[5]); // S
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    shiftOut(DATA_2, CLK_2, MSBFIRST, 0b11111111);  //
    digitalWrite(LATCH_2, HIGH);
    break;
  }
}
void bep()
{
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
}

void bacaremot()
{
  if (irrecv.decode(&results))
  {
    bep();
    data = results.value;
    Serial.println(results.value);
    irrecv.resume();

    switch (data)
    {
    case 16726215: // MENU / OK
      lanjut = 1;
      break;
    case 16718055: // UP
      lanjut = 2;
      break;
    case 16730805: // DOWN
      lanjut = 3;
      break;

    case 16750695: // 0

      roling++;
      wadah = '0';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;
    case 16753245: // 1

      roling++;
      wadah = '1';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;
    case 16736925: // 2

      roling++;
      wadah = '2';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;
    case 16769565: // 3

      roling++;
      wadah = '3';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;
    case 16720605: // 4

      roling++;
      wadah = '4';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;
    case 16712445: // 5

      roling++;
      wadah = '5';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;
    case 16761405: // 6

      roling++;
      wadah = '6';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;
    case 16769055: // 7

      roling++;
      wadah = '7';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;
    case 16754775: // 8

      roling++;
      wadah = '8';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;
    case 16748655: // 9

      roling++;
      wadah = '9';
      if (roling >= 3)
      {
        roling = 1;
        wadahremot = "";
      }
      wadahremot += wadah;
      break;

    case 16738455: // POWER

      if (hidup == 0)
      {
        hidup = 1;
      }
      else
      {
        hidup = 0;
      }
      break;
    }
    Serial.print(wadahremot);
  }
}

void tampilimsak()
{
  digitalWrite(LATCH_3, LOW);

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uimsakmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Limsakmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uimsakjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Limsakjam]); // digitTwo

  digitalWrite(LATCH_3, HIGH);
}
void tampilsubuh()
{
  digitalWrite(LATCH_3, LOW);

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Usubuhmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lsubuhmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Usubuhjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lsubuhjam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  digitalWrite(LATCH_3, HIGH);
}
void tampildzuhur()
{
  digitalWrite(LATCH_3, LOW);

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Udzuhurmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Ldzuhurmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Udzuhurjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Ldzuhurjam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  digitalWrite(LATCH_3, HIGH);
}

void tampilashar()
{
  digitalWrite(LATCH_3, LOW);

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uasharmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lasharmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uasharjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lasharjam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  digitalWrite(LATCH_3, HIGH);
}

void tampilmaghrib()
{
  digitalWrite(LATCH_3, LOW);

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Umaghribmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lmaghribmen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Umaghribjam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lmaghribjam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  digitalWrite(LATCH_3, HIGH);
}

void tampilisya()
{
  digitalWrite(LATCH_3, LOW);

  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uisyamen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lisyamen]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Uisyajam]); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, digitTgl[Lisyajam]); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo

  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  shiftOut(DATA_3, CLK_3, MSBFIRST, 0b11111111); // digitTwo
  digitalWrite(LATCH_3, HIGH);
}
void bacawaktusholat()
{
  switch (waktusholat)
  {
  case 1:
    tampilimsak();
    break;
  case 2:
    tampilsubuh();
    break;
  case 3:
    tampildzuhur();
    break;
  case 4:
    tampilashar();
    break;
  case 5:
    tampilmaghrib();
    break;
  case 6:
    tampilisya();
    break;
  }
}

void cekiqo()

{
  count = EEPROM.read(0);
  iqotext();
  tampilsubuh();
  digitalWrite(relay, HIGH);
  wadahremot = String(count);
  lanjut = 0;
  roling = 2;
  while (1)
  {
    bacaremot();
    if (count > 25)
    {
      count = 0;
    }
    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      count++;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(0, count);
    }
    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      count--;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(0, count);
    }
    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(1000);
      EEPROM.write(0, count);
      cekiqo1();
    }
    count = wadahremot.toInt();
    Ljam = count / 10;
    Ujam = count - Ljam * 10;

    digitalWrite(LATCH_1, LOW);
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitdot[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ujam]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ljam]); // digitTwo
    digitalWrite(LATCH_1, HIGH);
  }
}

void cekiqo1()

{
  count = EEPROM.read(1);
  iqotext();
  tampildzuhur();
  wadahremot = String(count);
  lanjut = 0;
  roling = 2;
  while (1)
  {
    bacaremot();
    if (count > 25)
    {
      count = 0;
    }

    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      count++;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(1, count);
    }
    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      count--;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(1, count);
    }
    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(1000);
      EEPROM.write(1, count);
      cekiqo2();
    }
    count = wadahremot.toInt();
    Ljam = count / 10;
    Ujam = count - Ljam * 10;

    digitalWrite(LATCH_1, LOW);
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitdot[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ujam]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ljam]); // digitTwo
    digitalWrite(LATCH_1, HIGH);
  }
}

void cekiqo2()

{
  count = EEPROM.read(2);
  iqotext();
  tampilashar();

  wadahremot = String(count);
  lanjut = 0;
  roling = 2;
  while (1)
  {
    bacaremot();

    if (count > 25)
    {
      count = 0;
    }
    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      count++;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(2, count);
    }
    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      count--;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(2, count);
    }
    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(1000);
      EEPROM.write(2, count);
      cekiqo3();
    }
    count = wadahremot.toInt();
    Ljam = count / 10;
    Ujam = count - Ljam * 10;

    digitalWrite(LATCH_1, LOW);
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitdot[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ujam]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ljam]); // digitTwo
    digitalWrite(LATCH_1, HIGH);
  }
}

void cekiqo3()

{
  count = EEPROM.read(3);
  iqotext();
  tampilmaghrib();

  wadahremot = String(count);
  lanjut = 0;
  roling = 2;
  while (1)
  {
    bacaremot();

    if (count > 25)
    {
      count = 0;
    }
    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      count++;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(3, count);
    }
    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      count--;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(3, count);
    }
    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(1000);
      EEPROM.write(3, count);
      cekiqo4();
    }
    count = wadahremot.toInt();
    Ljam = count / 10;
    Ujam = count - Ljam * 10;

    digitalWrite(LATCH_1, LOW);
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitdot[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ujam]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ljam]); // digitTwo
    digitalWrite(LATCH_1, HIGH);
  }
}

void cekiqo4()

{
  count = EEPROM.read(4);
  iqotext();
  tampilisya();

  wadahremot = String(count);
  lanjut = 0;
  roling = 2;
  while (1)
  {
    bacaremot();

    if (count > 25)
    {
      count = 0;
    }
    if (digitalRead(up) == 0 || lanjut == 2)
    {
      bep();
      lanjut = 0;
      count++;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(4, count);
    }
    if (digitalRead(down) == 0 || lanjut == 3)
    {
      bep();
      lanjut = 0;
      count--;
      wadahremot = String(count);
      delay(100);
      EEPROM.write(4, count);
    }
    if (digitalRead(ok) == 0 || lanjut == 1)
    {
      bep();
      delay(1000);
      EEPROM.write(4, count);
      asm volatile("  jmp 0");
    }
    count = wadahremot.toInt();
    Ljam = count / 10;
    Ujam = count - Ljam * 10;

    digitalWrite(LATCH_1, LOW);
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitdot[0]);    // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ujam]); // digitTwo
    shiftOut(DATA_1, CLK_1, MSBFIRST, digitjam[Ljam]); // digitTwo
    digitalWrite(LATCH_1, HIGH);
  }
}
