#include <SPI.h>
#include <SD.h>
#include <string.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include "Keyboard.h"

File root;
File myFile;

String fileList[5];
int count = 0;

int index = 0;

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

const int buttonDown = 10;
const int buttonUp = 11;
const int buttonSelect = 12;

int buttonDownState = 0;
int buttonUpState = 0;
int buttonSelectState = 0;

void setup() {

  if (!SD.begin(10)) {
    return;
  }

  Serial.begin(9600);

  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonSelect, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);

  delay(100);

  lcd.print("Loading Files...");

  root = SD.open("/");

  printDirectory(root, 0);
  
}

void executePayload(String filename){
  myFile = SD.open(filename);
  if (myFile) {
    Keyboard.begin();

    String line = "";
    while (myFile.available()) {
      char m = myFile.read();
      if (m == '\n'){
        Line(line);
        line = "";
        }
        else if((int) m != 13)
        {
          line += m;
        }
    }
    Line(line);
    
    myFile.close();
  } else {
  }

  Keyboard.end();
}

// Gestion des fichiers sur la carte SD
void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (!entry) {
      // Plus d'autres fichiers
      break;
    }
    String file_name = entry.name();
    
    if ( isFileType(entry.name()) && file_name.indexOf('_') != 0 ) { // Gestion du type de fichier
      char *tempname = entry.name();
      fileList[count] = file_name; // On ajoute le fichier à la liste
      tempname = "";
      Serial.println(fileList[count]); 
      count++;
    }

    delay(1000);
    entry.close();
  }
}

// Vérification si le fichier est un fichier et si c'est bien un .txt
bool isFileType(char* filename) {
  int8_t len = strlen(filename);
  bool result;
  if (  strstr(strlwr(filename + (len - 4)), ".txt")
    ) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

void Line(String l)
{
  int space_1 = l.indexOf(" ");
  if (space_1 == -1)
  {
    Press(l);
  }
  else if (l.substring(0,space_1) == "STRING")
  {
    Keyboard.print(l.substring(space_1 + 1));
  }
  else if (l.substring(0,space_1) == "DELAY")
  {
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  }
  else if(l.substring(0,space_1) == "REM"){}
  else
  {
      String remain = l;

      while(remain.length() > 0)
      {
        int latest_space = remain.indexOf(" ");
        if (latest_space == -1)
        {
          Press(remain);
          remain = "";
        }
        else
        {
          Press(remain.substring(0, latest_space));
          remain = remain.substring(latest_space + 1);
        }
        delay(5);
      }
  }

  Keyboard.releaseAll();
}


void Press(String b)
{
  if(b.length() == 1)
  {
    char c = b[0];
    Keyboard.press(c);
  }
  else if (b.equals("ENTER"))
  {
    Keyboard.press(KEY_RETURN);
  }
  else if (b.equals("CTRL"))
  {
    Keyboard.press(KEY_LEFT_CTRL);
  }
    else if (b.equals("SHIFT"))
  {
    Keyboard.press(KEY_LEFT_SHIFT);
  }
    else if (b.equals("ALT"))
  {
    Keyboard.press(KEY_LEFT_ALT);
  }
    else if (b.equals("GUI"))
  {
    Keyboard.press(KEY_LEFT_GUI);
  }
    else if (b.equals("UP") || b.equals("UPARROW"))
  {
    Keyboard.press(KEY_UP_ARROW);
  }
    else if (b.equals("DOWN") || b.equals("DOWNARROW"))
  {
    Keyboard.press(KEY_DOWN_ARROW);
  }
    else if (b.equals("LEFT") || b.equals("LEFTARROW"))
  {
    Keyboard.press(KEY_LEFT_ARROW);
  }
    else if (b.equals("RIGHT") || b.equals("RIGHTARROW"))
  {
    Keyboard.press(KEY_RIGHT_ARROW);
  }
    else if (b.equals("DELETE"))
  {
    Keyboard.press(KEY_DELETE);
  }
    else if (b.equals("PAGEUP"))
  {
    Keyboard.press(KEY_PAGE_UP);
  }
    else if (b.equals("PAGEDOWN"))
  {
    Keyboard.press(KEY_PAGE_DOWN);
  }
    else if (b.equals("HOME"))
  {
    Keyboard.press(KEY_HOME);
  }
    else if (b.equals("ESC"))
  {
    Keyboard.press(KEY_ESC);
  }
    else if (b.equals("INSERT"))
  {
    Keyboard.press(KEY_INSERT);
  }
    else if (b.equals("TAB"))
  {
    Keyboard.press(KEY_TAB);
  }
    else if (b.equals("END"))
  {
    Keyboard.press(KEY_END);
  }
    else if (b.equals("CAPSLOCK"))
  {
    Keyboard.press(KEY_CAPS_LOCK);
  }
    else if (b.equals("F1"))
  {
    Keyboard.press(KEY_F1);
  }
    else if (b.equals("F2"))
  {
    Keyboard.press(KEY_F2);
  }
    else if (b.equals("F3"))
  {
    Keyboard.press(KEY_F3);
  }
    else if (b.equals("F4"))
  {
    Keyboard.press(KEY_F4);
  }
    else if (b.equals("F5"))
  {
    Keyboard.press(KEY_F5);
  }
    else if (b.equals("F6"))
  {
    Keyboard.press(KEY_F6);
  }
    else if (b.equals("F7"))
  {
    Keyboard.press(KEY_F7);
  }
    else if (b.equals("F8"))
  {
    Keyboard.press(KEY_F8);
  }
    else if (b.equals("F9"))
  {
    Keyboard.press(KEY_F9);
  }
    else if (b.equals("F10"))
  {
    Keyboard.press(KEY_F10);
  }
    else if (b.equals("F11"))
  {
    Keyboard.press(KEY_F11);
  }
    else if (b.equals("F12"))
  {
    Keyboard.press(KEY_F12);
  }
    else if (b.equals("SPACE"))
  {
    Keyboard.press(' ');
  } 
}

void loop() {
  // On lit les états de chacun des boutons
  buttonUpState = digitalRead(buttonUp);
  buttonDownState = digitalRead(buttonDown);
  buttonSelectState = digitalRead(buttonSelect);

  lcd.clear();

  // On écrit la liste des fichiers à afficher sur l'écran
  lcd.setCursor(0,0);
  lcd.print(fileList[index]);
  lcd.setCursor(0,1);
  lcd.print(fileList[index + 1]);

  if (buttonUpState == LOW) {
    Serial.println("UP");
    if(index > 0){
      index--;
    }
  } 

  if (buttonDownState == LOW) {
    Serial.println("DOWN");
    if(index < count - 2){
      index++;
    }
  } 

  // Si on appuie sur la selection, on éxecute le payload
  if (buttonSelectState == LOW) {
    Serial.println("SELECT");
    executePayload(fileList[index]);
  } 

  delay(100);
}


