#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1  // Reset pin not used
#define SCREEN_1_ADDRESS 0x3C // First OLED
#define SCREEN_2_ADDRESS 0x3D // Second OLED

#define MODE_BTN      35
#define INCREMENT_BTN 14
#define DECREMENT_BTN 27
#define PLAYER_BTN_1  32
#define PLAYER_BTN_2  33

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile int hours_1 = 0;
volatile int mins_1  = 10;
volatile int secs_1  = 0;

int increment_1_min = 0;
int increment_1_sec = 5;
int increment_2_min = 0;
int increment_2_sec = 5; 

volatile int hours_2 = 0;
volatile int mins_2  = 10;
volatile int secs_2  = 0;

char buffer1[15];
char buffer2[15];
char buffer3[15];
char buffer4[15];

int initial_state= 0;
int mode_counter =0 ;

volatile bool should_timer_1_be_on =false;
volatile bool should_timer_2_be_on =false;

volatile int flag=0;
enum TimeField { NONE, HOURS, MINUTES, SECONDS };

void display1_on(TimeField highlight = NONE);
void display1_increment_on(TimeField highlight);
void display2_increment_on(TimeField highlight);

void IRAM_ATTR player2Playing(){
  if(flag==0)
  {
    should_timer_2_be_on = true;
    should_timer_1_be_on = false;

  }
  else 
  {
    should_timer_2_be_on = false;
    should_timer_1_be_on = true;
  }
}
void IRAM_ATTR player1Playing(){
  if(flag==0)
  {
    should_timer_2_be_on = false;
    should_timer_1_be_on = true;

  }
  else 
  {
    should_timer_2_be_on = true;
    should_timer_1_be_on = false;
  }
}
void setup() {
  Serial.begin(115200);
  display1_init(); 
  display2_init();


  // Setting pin modes for various buttons 
  pinMode(PLAYER_BTN_1,INPUT);
  pinMode(PLAYER_BTN_2,INPUT);
  pinMode(MODE_BTN, INPUT);

  attachInterrupt(digitalPinToInterrupt(PLAYER_BTN_1), player2Playing, FALLING);
  attachInterrupt(digitalPinToInterrupt(PLAYER_BTN_2), player1Playing, FALLING); 
  pinMode(INCREMENT_BTN,INPUT);
  pinMode(DECREMENT_BTN,INPUT);;

  display1_on(NONE);
  display2_on(NONE);
  set_display1_time();
 
}
void loop() {
  if(should_timer_1_be_on == true)
  {
   should_timer_2_be_on = false;
    timer1_on();
  }
  if(should_timer_2_be_on == true)
  {
    
   should_timer_1_be_on = false;
    timer2_on();
  }



}

void set_display1_time(void){
  while(true)
  {
    if(digitalRead(MODE_BTN) == HIGH)
  {
    delay(500);
    mode_counter++;
    
  }

  // HOURS INCREMENT AND DECREMENT
  if(mode_counter==1)
  { 
    display1_on(HOURS);
    if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      hours_1++; 
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(hours_1 != 0){
      delay(500);
      hours_1--;
      }
    }
  }
  // MINUTES INCREMENT DECREMENT 
  if(mode_counter==2)
  {
    display1_on(MINUTES);
    if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      mins_1++;
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(mins_1 != 0){
      delay(500);
      mins_1--;
      }
    }
  }
   // SET seconds for timer 1
   if(mode_counter==3)
  { display1_on(SECONDS);
    if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      secs_1++;
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(secs_1 != 0){
      delay(500);
      secs_1--;
      }
    }
  }

  // Ability to set increment of minutes 

  if(mode_counter==4)
  {
    display1_increment_on(MINUTES);
    if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      increment_1_min++;
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(increment_1_min != 0){
      delay(500);
      increment_1_min--;
      }
    }
  } 

  // set increment seconds 
  if(mode_counter==5)
  {
    display1_increment_on(SECONDS);
    if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      increment_1_sec++;
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(increment_1_sec != 0){
      delay(500);
      increment_1_sec--;
      }
    }
  } 
  

  if(mode_counter==6)
  {
    display1_on();
    display2_on(HOURS);
   if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      hours_2++;
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(hours_2 != 0){
      delay(500);
      hours_2--;
      }
    }
  } 
  if(mode_counter==7)
  {
    display2_on(MINUTES);
   if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      mins_2++;
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(mins_2 != 0){
      delay(500);
      mins_2--;
      }
    }
  } 

   if(mode_counter==8)
  {
    display2_on(SECONDS);
   if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      secs_2++;
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(secs_2 != 0){
      delay(500);
      secs_2--;
      }
    }
  } 



  if(mode_counter==9)
  {
    display2_increment_on(MINUTES);
    if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      increment_2_min++;
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(increment_2_min != 0){
      delay(500);
      increment_2_min--;
      }
    }
  }


  if(mode_counter==10)
  {
    display2_increment_on(SECONDS);
    if(digitalRead(INCREMENT_BTN)==HIGH)
    {
      delay(500);
      increment_2_sec++;
    }
    if(digitalRead(DECREMENT_BTN)==HIGH)
    {
      if(increment_2_sec != 0){
      delay(500);
      increment_2_sec--;
      }
    }
  }

  if (mode_counter >10)
  {
    display2_on(NONE);
    mode_counter = 0 ;
    return;
  }
  }
}
void display1_init(void){
  if (!display1.begin(SSD1306_SWITCHCAPVCC, SCREEN_1_ADDRESS)) {
    Serial.println(F("SSD1306 display 1 allocation failed"));
    for (;;);
  }
}
void display2_init(void){
  if (!display2.begin(SSD1306_SWITCHCAPVCC, SCREEN_2_ADDRESS)) {
    Serial.println(F("SSD1306 display 2 allocation failed"));
    for (;;);
  }
}
void display1_on(TimeField highlight ){
  display1.clearDisplay();
  display1.setTextSize(3);
  display1.setTextColor(WHITE);
  display1.setCursor(0, 30);
  
  sprintf(buffer1, "%d:%02d:%02d", hours_1, mins_1, secs_1);
  display1.println(buffer1); 

  // HEADING
  display1.setTextSize(1);
  display1.setCursor(45, 5);
  display1.println("TIMER 1");

  // UNDERLINE
  if (highlight != NONE) {
    int underlineY = 60; // bottom Y of text line
    int xStart = 0;
    int xEnd = 0;

    switch (highlight) {
      case HOURS:
        xStart = 0;
        xEnd = 30;  // Width of hours part at size 3
        break;
      case MINUTES:
        xStart = 44;
        xEnd = 75;
        break;
      case SECONDS:
        xStart = 88;
        xEnd = 123;
        break;
    }
    display1.drawLine(xStart, underlineY, xEnd, underlineY, WHITE);
  }

  display1.display();
}
void display2_on(TimeField highlight )
{
  
  display2.clearDisplay();
  display2.setTextSize(3);
  display2.setTextColor(WHITE);
  display2.setCursor(0, 30);
  
 
  sprintf(buffer2, "%d:%02d:%02d",hours_2,mins_2,secs_2);
  display2.println(buffer2);
  // HEADING

  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(45,5);
  display2.println("TIMER 2");
  
  if (highlight != NONE) {
    int underlineY = 60; // bottom Y of text line
    int xStart = 0;
    int xEnd = 0;

    switch (highlight) {
      case HOURS:
        xStart = 0;
        xEnd = 30;  // Width of hours part at size 3
        break;
      case MINUTES:
        xStart = 44;
        xEnd = 75;
        break;
      case SECONDS:
        xStart = 88;
        xEnd = 123;
        break;
    }
    display2.drawLine(xStart, underlineY, xEnd, underlineY, WHITE);
  }

  display2.display();
}
void timer1_on(void){
 if(should_timer_1_be_on ==true)
 {
    while (hours_1 > 0 || mins_1 > 0 || secs_1 >= 0) 
    {
      display1_on(NONE);
        delay(1000);
        secs_1--;

        if (secs_1 < 0) 
        {
            if (mins_1 > 0) 
            {
                mins_1--;
                secs_1 = 59;
            } else if (hours_1 > 0) 
            {
                hours_1--;
                mins_1 = 59;
                secs_1 = 59;
            }
          }
          if(should_timer_1_be_on ==true)
          continue;
          else
          break;
        } 
  }

  if(should_timer_1_be_on ==false){
    secs_1 += increment_1_sec;
    if (secs_1 > 59) {
    mins_1 += secs_1 / 59;
    secs_1 = (secs_1 % 59);
    }
    mins_1 += increment_1_min;
    if (mins_1 > 59) {
        hours_1 += mins_1 / 59;
        mins_1 = (mins_1 % 59);
      }
      display1_on(NONE);
      return;
  }
  

}
void timer2_on(void){
  if(should_timer_2_be_on ==true)
 {
    while (hours_2 > 0 || mins_2 > 0 || secs_2 >= 0) 
    {
      display2_on(NONE);
        delay(1000);
        secs_2--;

        if (secs_2 < 0) 
        {
            if (mins_2 > 0) 
            {
                mins_2--;
                secs_2 = 59;
            } else if (hours_2 > 0) 
            {
                hours_2--;
                mins_2 = 59;
                secs_2 = 59;
            }
          }
          if(should_timer_2_be_on ==true)
          continue;
          else
          break;
        } 
  }

  if(should_timer_2_be_on ==false){
    secs_2 += increment_2_sec;
    if (secs_2 >= 60) {
    mins_2 += secs_2 / 60;
    secs_2 = (secs_2 % 60)+1;
    }
    mins_2 += increment_2_min;
    if (mins_2 >= 60) {
        hours_2 += mins_2 / 60;
        mins_2 = (mins_2 % 60)+1;
      }
      display2_on(NONE);
      return;
  }
  

}
void display1_off(void){
  display1.clearDisplay();
  display1.display();

}
void display2_off(void){
  display2.clearDisplay();
  display2.display();
}

void display1_increment_on(TimeField highlight){
  
  display1.clearDisplay();
  display1.setTextSize(3);
  display1.setTextColor(WHITE);
  display1.setCursor(0, 30);
  
  sprintf(buffer3, "X:%02d:%02d",increment_1_min,increment_1_sec);
  display1.println(buffer3); 
  // HEADING
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(45,5);
  display1.println("INCREMENT");

  if (highlight != NONE) {
    int underlineY = 60; // bottom Y of text line
    int xStart = 0;
    int xEnd = 0;

    switch (highlight) {
      case HOURS:
        xStart = 0;
        xEnd = 30;  // Width of hours part at size 3
        break;
      case MINUTES:
        xStart = 44;
        xEnd = 75;
        break;
      case SECONDS:
        xStart = 88;
        xEnd = 123;
        break;
    }
    display1.drawLine(xStart, underlineY, xEnd, underlineY, WHITE);
  }

  display1.display();
}

void display2_increment_on(TimeField highlight){
  
  display2.clearDisplay();
  display2.setTextSize(3);
  display2.setTextColor(WHITE);
  display2.setCursor(0, 30);

  sprintf(buffer4, "X:%02d:%02d",increment_2_min,increment_2_sec);
  display2.println(buffer4);
  // HEADING
  display2.setTextSize(1);
  display2.setTextColor(WHITE);
  display2.setCursor(45,5);
  display2.println("INCREMENT");


  if (highlight != NONE) {
    int underlineY = 60; // bottom Y of text line
    int xStart = 0;
    int xEnd = 0;

    switch (highlight) {
      case HOURS:
        xStart = 0;
        xEnd = 30;  // Width of hours part at size 3
        break;
      case MINUTES:
        xStart = 44;
        xEnd = 75;
        break;
      case SECONDS:
        xStart = 88;
        xEnd = 123;
        break;
    }
    display2.drawLine(xStart, underlineY, xEnd, underlineY, WHITE);
  }

  display2.display();
}