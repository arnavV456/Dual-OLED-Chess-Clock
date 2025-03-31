#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1  // Reset pin not used
#define SCREEN_1_ADDRESS 0x3C // First OLED
#define SCREEN_2_ADDRESS 0x3D // Second OLED

#define INC_BTN_1     35
#define PLAYER_1      32
#define PLAYER_2      33
#define LED           25

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int hours_1 = 1;
int mins_1  = 1;
int secs_1  = 10;

int hours_2 = 0;
int mins_2  = 0;
int secs_2  = 10;

char buffer1[30];
char buffer2[30];

int initial_state= 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // ESP32 I2C: SDA=21, SCL=22

  display1_init(); 
  display2_init();

  // Setting the initial state of the main button so we can start the game when this state changes 
  initial_state = set_initial_state();

  // Setting pin modes for various buttons 
  pinMode(PLAYER_1,INPUT);
  pinMode(PLAYER_2,INPUT);
  pinMode(INC_BTN_1, INPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  display1_on();
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
void display1_on(void)
{

  sprintf(buffer1, "%d: %d: %d",hours_1,mins_1,secs_1);
  display1.clearDisplay();
  display1.setTextSize(2);
  display1.setTextColor(WHITE);
  display1.setCursor(15, 20);
  display1.println(buffer1);
  display1.display();  
  delay(1000);
  secs_1--;
  if(secs_1<0)
  {
    if(mins_1>0)
    {
    mins_1--;
    secs_1=59;
    }
  }
  if(mins_1<0 && hours_1>0)
  {
    hours_1--;
    mins_1=59;
  }
  if(hours_1==0 && mins_1==0 && secs_1==0)
  {
    return;
  }
}
void display2_on(void)
{
  sprintf(buffer2, "%d: %d: %d",hours_1,mins_1,secs_1);
  display2.clearDisplay();
  display2.setTextSize(2);
  display2.setTextColor(WHITE);
  display2.setCursor(15, 20);
  display2.println(buffer2);
  display2.display();
}
void display1_off(void){
  display1.clearDisplay();
  display1.display();

}
void display2_off(void){
  display2.clearDisplay();
  display2.display();
}
int set_initial_state(){
  if(digitalRead(PLAYER_1)==HIGH)
  {
    return PLAYER_1;
  }
  else{
    return PLAYER_2;
  }
}