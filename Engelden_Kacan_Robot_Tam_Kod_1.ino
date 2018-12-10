//Engelden Kaçan Robot(Obstacle Avoiding Robot)
//Designed by @arif__mandall.
//You can use to find some information 'http://www.arduino.cc'
  
//değişkenlerimiz...

//Servo
#include<Servo.h>//servo kütüphanemizi dahil ettik.
Servo servo;//servo objesini oluşturuyoruz.

//ultrasonik sensor
const int trigPin = 5;//trigger pinini 5 olarak atadık.
const int echoPin = 6;//echo pinini 6 olarak atadık.

//motor sürücüsü
const int ln1 = 10;//motor sürücümüzün pinlerini atadık.
const int ln2 = 11;//motor sürücümüzün pinlerini atadık.
const int ln3 = 9;//motor sürücümüzün pinlerini atadık.
const int ln4 = 8;//motor sürücümüzün pinlerini atadık.

//diger değişkenler
int sure = 0;//ultrasonik sensorden gelen süreyi tutan süre değişkenimiz.
int mesafe = 0;//sabit olarak tutulan mesafe değişkenimiz.
int engel = 30;//robotumuzun kendi konumunu değiştireceği mesafe engel değişkeninde tutuldu.


//void setup başı...
void setup() {
  Serial.begin(9600);//Serial monitörümüzü başlattık.(Optional)
  
  servo.attach(7);//servo pinimizi 7 olarak atadık.
  
  servo.write(90);//ve motorumuzun yönünü 90 dereceye çevirdik.
  
  pinMode(trigPin, OUTPUT);//trigger pinini çıkış olarak.
  pinMode(echoPin, INPUT);//echo pinini giriş olarak atadık.
  pinMode(ln1, OUTPUT);//motor sürücümüzün pinlerini çıkış pini olarak atadık.
  pinMode(ln2, OUTPUT);//motor sürücümüzün pinlerini çıkış pini olarak atadık.
  pinMode(ln3, OUTPUT);//motor sürücümüzün pinlerini çıkış pini olarak atadık.
  pinMode(ln4, OUTPUT);//motor sürücümüzün pinlerini çıkış pini olarak atadık.

}
//void setup sonu...
//void loop başı...
void loop() {
  mesafe = mesafeOlc();//ilk 0 atadığımız mesafeyi mesafe Ölç foksiyonuyla değerini aldık.
  while (mesafe >= 0 && mesafe <= 10) {//mesafe 0'dan büyük ve 10'dan küçük ise sürekli mesafe Ölç foksiyonunu çalıştıracak.
    mesafe = mesafeOlc();
  }
  Serial.print("on= ");//monitöre öndeki uzaklığı yazdıracak.(optional)
  Serial.println(mesafe);//monitöre öndeki uzaklığı yazdıracak.(optional)
  if (mesafe <= engel) {//eğer mesafe engelden küçükse diğer tarafları kontrol ediyor .
    dur();//durmasını sağladık rahat kontrol etmesi için;
    servo.write(0);//ilk önce sağ tarafı kontrol edecek.Bu yüzden servoyu 0 dereceye getirdik.
    delay(500);//gecikmeler daha doğru kontrol etmesini sağlıyor.
    int sag = mesafeOlc();//sağ taraftan bilgileri alıyor.
    Serial.print("sag= ");//yazdırıyoruz.(optional)
    Serial.println(sag);//yazdırıyoruz.(optional)
    delay(500);//gecikme verdik.
    servo.write(180);//daha sonra sol tarafı kontrol edecek.Bu yüzden servoyu 180 dereceye getirdik.
    delay(500);//gecikme verdik.
    int sol = mesafeOlc();//sol taraftan bilgileri alıyor.
    Serial.print("sol= ");//yazdırıyoruz.(optional)
    Serial.println(sol);//yazdırıyoruz.(optional)
    delay(500);//gecikme verdik.
    servo.write(90);//tekrar servo yönümüzü 90 dereceye getiriyoruz.
    delay(500);//gecikme verdik.

    //aldığımız bilgiler ile karar verecek... 
    if (sol < engel && sag < engel) {//önü, sağ tarafı ve sol tarafı kapalı ise tam geri dönüş yapacak.
      geriDon();//geri dön foksiyonumuz.
      Serial.println("Tam geri donus yapti.");//yazdırdık.(optional)

    } else {//eğer buna uymuyorsa ve 
      if (sol < sag) {//sağ tarafta engel yoksa
        geriDon();//robotumuzun kenarlarına takılabilceği düşüncesiyle geri dön foksiyonunu çağırdık.
        sagaDon();//daha sonra rahat bir şekilde sağa dönebilmesini sağladık.
        Serial.println("Saga donus yapti.");//yazdırdık.(optional)

      } else {//sol tarafta engel yoksa.
        geriDon();//geri dön
        solaDon();//ve sol git foksiyonumuzu çağırdık.
        Serial.println("Sola donus yapti.");//yazdırdık.(optional)
      }

    }
    delay(50);//gecikme verdik.
    ileriGit();//ileriye gidip terkar kontrol etmesini sağladık. 

  } else {
    ileriGit();//eğer mesafe engelden büyükse ileri gidecek. 
  }
  delay(50);//gecikme verdik.

}
//void loop sonu...

//foksiyonlar...
void dur() {//dur foksiyonu 
  digitalWrite(ln1, LOW);//bütün motorlarımız low yani 0 konumunda.
  digitalWrite(ln2, LOW);
  digitalWrite(ln3, LOW);
  digitalWrite(ln4, LOW);
  delay(300);//gecikme verdik.
}

void geriDon() {//geri dön foksiyonu
  digitalWrite(ln1, LOW);//geri yön(ln2,ln4) pinlerimiz high, ileri yön(ln1,ln3) pinlerimiz low konumunda.
  digitalWrite(ln2, HIGH);
  digitalWrite(ln3, LOW);
  digitalWrite(ln4, HIGH);
  delay(300);//gecikme verdik.
}

void ileriGit() {//ileri git foksiyonu
  digitalWrite(ln1, HIGH);//geri yön(ln2,ln4) pinlerimiz low, ileri yön(ln1,ln3) pinlerimiz high konumunda.
  digitalWrite(ln2, LOW);
  digitalWrite(ln3, HIGH);
  digitalWrite(ln4, LOW);
  delay(300);//gecikme verdik.
}
void solaDon() {//sola dön foksiyonu
  digitalWrite(ln1, LOW);
  digitalWrite(ln2, LOW);
  digitalWrite(ln3, HIGH);//ln3 pinimizi high konumuna getirip diğer pinleri low konumuna getirip sola dönmesi sağladık.
  digitalWrite(ln4, LOW);
  delay(800);//gecikme verdik.
}
void sagaDon() {//sağ dön foksiyonu
  digitalWrite(ln1, HIGH);//ln1 pinimizi high konumuna getirip diğer pinleri low konumuna getirip sağa dönmesi sağladık.
  digitalWrite(ln2, LOW);
  digitalWrite(ln3, LOW);
  digitalWrite(ln4, LOW);
  delay(800);//gecikme verdik.
}

int mesafeOlc() {//mesafe ölç foksiyonu
  digitalWrite(trigPin, LOW); //trigger pinimizi low konumuna getirdik-->veri 0
  delayMicroseconds(5);//5 mikrosaniye bekledik.
  digitalWrite(trigPin, HIGH); //trigger pinimizi high konumuna getirdik-->veri 1(veri gönderdik.)
  delayMicroseconds(10);//10 mikrosaniye bekledik.
  digitalWrite(trigPin, LOW); //tekrar low konumuna getirdik-->veri 0(veri gönderimini kestik.)
  sure = pulseIn(echoPin, HIGH); //echo pini ile veri gelip gitme süresini hesapladık.(pulseIn komutunu kullandık.)
  int uzaklik = (sure / 2) / 28.5;//hesapladığımız süre ile uzaklık değişkenimizi hesapladık.
  //Ayrıntılı bilgiyi arduino derslerimde bulabilirsiniz.

  Serial.println(uzaklik);//uzaklığı yazdırdık.(optional)
  if (uzaklik < 0) {//eğer uzaklık sıfırdan küçükse 0 değerini yani değişkenlerde atadığımız 0 değerini dönecek.
    return mesafe;

  } else {//büyükse uzaklık değerini alacağız.
    return uzaklik;

  }

}
//foksiyonlar sonu...

//dinlediğiniz, okuduğuz ve vakit ayırdığınız için teşekkür ederim...İyi Çalışmalar...@arif__mandall
