#include <Adafruit_NeoPixel.h>

#define PIN 4
#define POT 6

Adafruit_NeoPixel ring = Adafruit_NeoPixel(196, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.setBrightness(32);
  ring.clear(); // clear all pixels
  ring.show();  // show all pixels
}

void wipe(unsigned long color) {
  for(int i=49;i<ring.numPixels()/2;i++) {
    ring.setPixelColor(i, color);
    ring.show();
    //delay(100);
  }
}

void setCoord(int y, int z, int x){
  int layer = 49 * y;
  int row = 7 * z;
  int column = (z%2?6 - x:x);
  int i = layer + row + column;
  ring.setPixelColor(i, 0xFF0000);
  ring.show();
}

void setLayer(int y){
  for(int z = 0; z < 7; z++){
    for(int x = 0; x < 7;x++){
      setCoord(y, z, x);
      delay(50);
    }
  }
}

void getNeighbors(int y, int z, int x){
  for(int layer = y - 1; (layer < y + 2 || layer == 4); layer++){
    for(int row = z - 1; (row < z + 2 || row == 7); row++){
      for(int column = x - 1; (column < x + 2 || column == 7); column++){
        if(layer > -1 && row > -1 && column > -1)
          if(!(layer == y && row == z && column == x))
            setCoord(layer, row, column);
      }
    }
  }
}

void loop() {
 // wipe(0xFF0000); // red, 0xFF0000 is equivalent to ring.Color(255,0,0);
  //wipe(0x00FF00); // green
 // wipe(0x0000FF); // blue
 // rainbow();
  //rainbowCycle();
//  setCoord(0,1,6);
//  setLayer(0);
//  setLayer(1);
//  setLayer(2);
//  setLayer(3);
getNeighbors(0,0,3);
}

void rainbow() {
  int i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<ring.numPixels(); i++) {
      ring.setPixelColor(i, Wheel((i+j) & 255));
    }
    ring.show();
    delay(20);
  }
}

void rainbowCycle() {
  int i, j;
  for(j=0; j<256*3; j++) { // 3 cycles of all colors on wheel
    for(i=0; i< ring.numPixels(); i++) {
      ring.setPixelColor(i, Wheel(((i * 256 / ring.numPixels()) + j) & 255));
    }
    ring.show();
    delay(20);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return ring.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return ring.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return ring.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


