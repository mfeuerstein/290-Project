#include <Adafruit_NeoPixel.h>

#define PIN 4
#define POT 6

Adafruit_NeoPixel ring = Adafruit_NeoPixel(196, PIN, NEO_GRB + NEO_KHZ800);

int maze[4][7][7];
int player = (0,0,0);

void setup() {
  ring.begin();
  ring.setBrightness(32);
  ring.clear(); // clear all pixels
  ring.show();  // show all pixels
  for(int layer = 0; layer < 4; layer++){
    for(int row = 0; row < 7; row++){
      for(int column = 0; column < 7; column++){
        maze[layer][row][column] = 0x000000;
      }
    }
  }

  maze[0][0][0] = 0x0000FF;
  maze[0][0][1] = 0x0000FF;
  maze[0][0][2] = 0x0000FF;
  maze[0][0][3] = 0x0000FF;
  maze[0][0][4] = 0x0000FF;
  maze[0][1][0] = 0x00F00F;
  maze[0][2][0] = 0x0000FF;
  maze[0][2][1] = 0x0000FF;
  maze[0][2][2] = 0x0000FF;
  maze[0][1][4] = 0x0000FF;
  player = (0,1,1);
  Serial.begin(9600);
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
  int row = (y%2?6 - z:z) * 7;
  int column = (y%2?(z%2?x:6 - x):(z%2?6 - x:x));
  int i = layer + row + column;
  ring.setPixelColor(i, 0xFF0000);
  ring.show();
}

void setCoord(int y, int z, int x, int color){
  int layer = 49 * y;
  int row = 7 * z;
  int column = (z%2?6 - x:x);
  int i = layer + row + column;
  ring.setPixelColor(i, color);
  ring.show();
}

void setMaze(int m[][7][7]){
  for(int layer = 0; layer < 4; layer++){
    for(int row = 0; row < 7; row++){
      for(int column = 0; column < 7; column++){
        setCoord(layer, row, column, m[layer][row][column]);
      }
    }
  }
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
  int y = 0, z = 1, x = 0;
void loop() {
 // wipe(0xFF0000); // red, 0xFF0000 is equivalent to ring.Color(255,0,0);
  //wipe(0x00FF00); // green
 // wipe(0x0000FF); // blue
 // rainbow();
  //rainbowCycle();
//  setCoord(0,1,6);
  setLayer(0);
  setLayer(1);
//  setLayer(2);
//  setLayer(3);

//setMaze(maze);
//  delay(500);
//
//  if(hitWall(0, 1, 1, maze)){
//    maze[y][z][x] = 0x00FF00;
//  }
//  else
//  {
//    maze[y][z][x] = 0x000000;
//    x = 1;
//    maze[y][z][x] = 0x00F00F;
//    
//  }
  
//  maze[1][2][2] = 0x0000FF;
//  maze[2][2][2] = 0x0000FF;
//  maze[3][2][2] = 0x0000FF;

//  setMaze(maze);
//getNeighbors(0,0,3);

//  movePlayer();
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

boolean hitWall(int y, int z, int x, int m[][7][7]){
  return m[y][z][x] == 0x0000FF;
}

void movePlayer(){
 char receivedChar;
 if (Serial.available() > 0) {
  receivedChar = Serial.read();
  
  if(receivedChar=='l'){
    if(!hitWall(y, z+1, x, maze) && z < 6){
      maze[y][z][x] = 0x000000;
      z=z+1;
    }
  }
  else if(receivedChar=='r'){
    if(!hitWall(y, z-1, x, maze) && z > 0){
      maze[y][z][x] = 0x000000;
      z=z-1;
    }
  }
  else if(receivedChar=='f'){
    if(!hitWall(y, z, x+1, maze) && x < 6){
      maze[y][z][x] = 0x000000;
      x=x+1;
    }
  }
  else if(receivedChar=='b'){
    if(!hitWall(y, z, x-1, maze) && x > 0){
      maze[y][z][x] = 0x000000;
      x=x-1;
    }
  }
  else if(receivedChar=='u'){
    if(!hitWall(y+1, z, x, maze) && y < 3){
      maze[y][z][x] = 0x000000;
      y=y+1;
    }
  }
  else if(receivedChar=='d'){
    if(!hitWall(y-1, z, x, maze) && y > 0){
      maze[y][z][x] = 0x000000;
      y=y-1;
    }
  }
  maze[y][z][x] = 0x00F00F;
 }
 setMaze(maze);
}


