  import processing.serial.*;
Serial port;
/* change serialName to match yours */
String serialName = "COM4";


int rectX, rectY;      // Position of square button
int rectX2, rectY2;
int rectX3, rectY3;
int rectX4, rectY4;
int rectX5, rectY5;
int rectX6, rectY6;
int circleX, circleY;  // Position of circle button
int rectSize = 90;     // Diameter of rect
int circleSize = 93;   // Diameter of circle
color rectColor, circleColor, baseColor;
color rectHighlight, circleHighlight;
color currentColor;
boolean rectOver = false;
boolean rectOver2 = false;
boolean rectOver3 = false;
boolean rectOver4 = false;
boolean rectOver5 = false;
boolean rectOver6 = false;
boolean circleOver = false;

void setup() {
  size(640, 360);
  rectColor = color(0);
  rectHighlight = color(51);
  circleColor = color(255);
  circleHighlight = color(204);
  baseColor = color(102);
  currentColor = baseColor;
  circleX = width/2+circleSize/2+10;
  circleY = height/2;
  rectX = 100;
  rectY = 100;
  rectX2 = 200;
  rectY2 = 10;
  rectX3 = 300;
  rectY3 = 100;
  rectX4 = 200;
  rectY4 = 200;
  rectX5 = 500;
  rectY5 = 30;
  rectX6 = 500;
  rectY6 = 170;
  

  port = new Serial(this, serialName, 9600);

  
  ellipseMode(CENTER);
}

void draw() {
  update(mouseX, mouseY);
  background(currentColor);
  fill(rectColor);
  if (rectOver) {
    fill(rectHighlight);
  } else {
    fill(rectColor);
  }
  stroke(255);
  rect(rectX, rectY, rectSize, rectSize);
  rect(rectX2, rectY2, rectSize, rectSize);
  rect(rectX3, rectY3, rectSize, rectSize);
  rect(rectX4, rectY4, rectSize, rectSize);
  rect(rectX5, rectY5, rectSize, rectSize);
  rect(rectX6, rectY6, rectSize, rectSize);
  
  
  //ellipse(circleX, circleY, circleSize, circleSize);
}

void update(int x, int y) {
  if ( overRect(rectX, rectY, rectSize, rectSize) ) {
    rectOver = true;
    circleOver = false;
    rectOver2 = false;
    rectOver3 = false;
    rectOver4 = false;
    rectOver5 = false;
    rectOver6 = false;
  } else if ( overRect(rectX2, rectY2, rectSize, rectSize) ) {
    rectOver2 = true;
    rectOver = false;
    rectOver3 = false;
    rectOver4 = false;
    circleOver = false;
    rectOver5 = false;
    rectOver6 = false;
  } else if ( overRect(rectX3, rectY3, rectSize, rectSize) ) {
    rectOver2 = false;
    rectOver = false;
    rectOver3 = true;
    rectOver4 = false;
    circleOver = false;
    rectOver5 = false;
    rectOver6 = false;
  } else if ( overRect(rectX4, rectY4, rectSize, rectSize) ) {
    rectOver2 = false;
    rectOver = false;
    rectOver3 = false;
    rectOver4 = true;
    circleOver = false;
    rectOver5 = false;
    rectOver6 = false;
  } else if ( overRect(rectX5, rectY5, rectSize, rectSize) ) {
    rectOver2 = false;
    rectOver = false;
    rectOver3 = false;
    rectOver4 = false;
    circleOver = false;
    rectOver5 = true;
    rectOver6 = false;
  } else if ( overRect(rectX6, rectY6, rectSize, rectSize) ) {
    rectOver2 = false;
    rectOver = false;
    rectOver3 = false;
    rectOver4 = false;
    circleOver = false;
    rectOver5 = false;
    rectOver6 = true;
  } else {
    circleOver = rectOver = rectOver2 = rectOver3 = rectOver4 = rectOver5 = rectOver6 = false;
  }
}

void mousePressed() {
  //if (circleOver) {
  //  currentColor = circleColor;
  //}
  if (rectOver) {
    currentColor = rectColor;
    println("left");
    port.write("l");
  }
  if (rectOver2) {
    currentColor = rectColor;
    println("forward");
    port.write("f");
  }
  if (rectOver3) {
    currentColor = rectColor;
    println("right");
    port.write("r");
  }
  if (rectOver4) {
    currentColor = rectColor;
    println("backward");
    port.write("b");
  }
  if (rectOver5) {
    currentColor = rectColor;
    println("up");
    port.write("u");
  }
  if (rectOver6) {
    currentColor = rectColor;
    println("down");
    port.write("d");
  }
}

boolean overRect(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}

boolean overCircle(int x, int y, int diameter) {
  float disX = x - mouseX;
  float disY = y - mouseY;
  if (sqrt(sq(disX) + sq(disY)) < diameter/2 ) {
    return true;
  } else {
    return false;
  }
}
