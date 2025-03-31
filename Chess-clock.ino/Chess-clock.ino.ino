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

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int hours_1 = 0;
int mins_1  = 0;
int secs_1  = 0;

int hours_2 = 0;
int mins_2  = 0;
int secs_2  = 0;

char buffer1[30];
char buffer2[30];

int iniial_state= 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // ESP32 I2C: SDA=21, SCL=22

  if (!display1.begin(SSD1306_SWITCHCAPVCC, SCREEN_1_ADDRESS)) {
    Serial.println(F("SSD1306 display 1 allocation failed"));
    for (;;);
  }
  
  if (!display2.begin(SSD1306_SWITCHCAPVCC, SCREEN_2_ADDRESS)) {
    Serial.println(F("SSD1306 display 2 allocation failed"));
    for (;;);
  }

  pinMode(INC_BTN_1, INPUT);

// Checking which side is initially on  so that we can start the clocks when the
// button position changes 
  if(digitalRead(PLAYER_1)==HGIH){
    initial_state= 0;
  }
  if(digitalRead(PLAYER_2)==HGIH){
    initial_state= 1;
  }

}

void loop() {
  
 
  
 screen1_activate();
 delay(1000);
 screen2_activate();
 delay(1000);
 screen1_off();
  
}

void screen1_activate(void)
{
  sprintf(buffer1, "%d: %d: %d",hours_1,mins_1,secs_1);
  display1.clearDisplay();
  display1.setTextSize(2);
  display1.setTextColor(WHITE);
  display1.setCursor(15, 20);
  display1.println(buffer1);
  display1.display();

  if()
}
void screen2_activate(void)
{
  sprintf(buffer2, "%d: %d: %d",hours_1,mins_1,secs_1);
  display2.clearDisplay();
  display2.setTextSize(2);
  display2.setTextColor(WHITE);
  display2.setCursor(15, 20);
  display2.println(buffer2);
  display2.display();
}
void screen1_off(void){
  display1.clearDisplay();
  display1.display();
}
