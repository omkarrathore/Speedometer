 #include<LiquidCrystal.h>

 #include<Wire.h>

 #include<Rtc_Pcf8563.h>

 Rtc_Pcf8563 rtc;

 char * days[7] = {
   "Sun",
   "Mon",
   "Tue",
   "Wed",
   "Thu",
   "Fri",
   "Sat"
 };

 LiquidCrystal lcd(4, 5, 13, 12, 11, 10);

 long int sense = 3, rot = 0, d = 0, b = 0, tog = 6, x = 0, u = 0, tpin = A0, tempi = 0;

 float sp = 0, distance = 0, tmd = 0, asp = 0.00, temp;

 int fl = 0, msg = 0, i = 0, rad = 31;

 char h[42];

 boolean togvl = LOW, togv;

 boolean prev;

 void setup()

 {

   Serial.begin(9600);

   lcd.begin(16, 2);

   lcd.clear();

   pinMode(sense, INPUT);

   pinMode(tpin, INPUT);

   togv = digitalRead(tog);

   lcd.setCursor(3, 0);
   lcd.write("Welcome");
   lcd.setCursor(11, 0);
   lcd.write("to");
   lcd.setCursor(0, 1);
   lcd.write("Bicycle Computer");
   delay(4000);
   lcd.setCursor(0, 0);
   lcd.clear();
   lcd.write("Enter Radius(cm)");
   lcd.setCursor(0, 1);
   lcd.write("0 for default");

   while (1) {
     rad = Serial.read();
     if (togv != digitalRead(tog)) {
       goto xy;
     }
   }
   xy:
     if (rad == 0) {
       rad = 31;
     }

 }

 void loop()

 {

   if (Serial.available())

   {

     msg = 1;

     for (i = 0; i <= 41; i++)

     {

       h[i] = (char) 0;

     }

     i = 0;

     //    lcd.clear();

     while (Serial.available() > 0)

     {

       h[i] = Serial.read();

       i++;

     }
     //  i=0;

   }

   prev = digitalRead(tog);

   temp = analogRead(tpin); //from lm35

   temp = (temp * 500 / 1023.0);

   tempi = temp;

   attachInterrupt(1, det, RISING); //from hall effect sensor

   if ((millis() - b) > 7000)

   {
     sp = 0;

     asp = (distance * 1000) / (b - x);

     lcd.clear();

   }

   if (d > 0)

   {

     //  sp=(2*3.14*rad)/(millis()-timeold);

     // timeold=millis();

     //    d=0;

   }

   if (digitalRead(tog) == LOW)

   {

     //             if(prev==HIGH)

     {

       lcd.clear();

     }

     if (msg == 1)

     {

       lcd.setCursor(15, 1);

       lcd.print("!");
       //message indication

     }

     if (sp == 0)

     {

       lcd.setCursor(0, 0);

       lcd.print("Avg.speed");

       lcd.setCursor(10, 0);

       lcd.print(asp);

       lcd.setCursor(13, 0);

       lcd.print("m/s");

     } else

     {

       lcd.setCursor(0, 0);

       lcd.print("speed");

       lcd.setCursor(6, 0);

       lcd.print(sp);

       lcd.setCursor(13, 0);

       lcd.print("m/s");

     }

     lcd.setCursor(0, 1);

     lcd.print("dist(km)");

     lcd.setCursor(9, 1);

     lcd.print(distance);

     prev = digitalRead(tog);

   } else if (digitalRead(tog) == HIGH) //line no 111.

   {

     if (msg == 1)

     {

       lcd.clear();

       lcd.print(h);

       togvl = HIGH;

     } else

     {

       //                if(prev==LOW)

       {

         lcd.clear();

       }

       lcd.setCursor(0, 0);

       lcd.print("Temp");

       lcd.setCursor(5, 0);

       lcd.print(tempi);

       lcd.setCursor(7, 0);

       lcd.print("C");

       lcd.setCursor(11, 0);

       lcd.print(days[rtc.getWeekday()]);

       lcd.setCursor(0, 1);

       lcd.print(rtc.formatDate());

       lcd.setCursor(11, 1);

       lcd.print(rtc.formatTime());

     }

     prev = digitalRead(tog);

   }

   if (digitalRead(tog) == LOW && togvl == HIGH)

   {

     togvl = LOW;

     msg = 0;

   }

   Serial.println("dist");

   Serial.println(distance);

   if (sp == 0)

   {

     Serial.println("avg.speed");

     Serial.println(asp);

   } else

   {

     Serial.println("speed");

     Serial.println(sp);

   }

 }

 void det()

 {

   if (u == 4)

   {

     x = millis();

   }

   u++;

   rot = rot + 1;

   //  distance=(2*3.14*rad*rot)/100000 
   distance = rot;
   d = d + 1;

   tmd = millis() - b;

   b = millis();
   // sp=(2*3.14*rad)*1000/tmd;
   sp = 1000 / tmd;
 }
