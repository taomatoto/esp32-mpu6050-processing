import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
import processing.sound.*;

Serial myPort;
SoundFile backsound;//50s
SoundFile leftscansound;//15s
SoundFile leftcoinsound;//1s
SoundFile rightscansound;//15s
SoundFile rightcoinsound;//1s
String data="";
float froll, fpitch, yaw;//just use froll,fpitch
int roll, pitch;
float backvol = 0.1;//sound volume
float scanvol = 0.0;
int sd = 0;

void setup() {
  size (300, 300, P3D);
  // starts the serial communication
  myPort = new Serial(this, "/dev/cu.usbserial-0001", 115200);
  myPort.bufferUntil('\n');
  //read soundfile
  backsound = new SoundFile(this, "mixkit-sea-waves-loop-1196.mp3");
  leftscansound = new SoundFile(this, "Leftmixkit-sci-fi-waves-scanner-907.mp3");
  leftcoinsound = new SoundFile(this, "Leftmixkit-winning-a-coin-video-game-2069.mp3");
  
  rightscansound = new SoundFile(this, "Rmixkit-sci-fi-waves-scanner-907.mp3");
  rightcoinsound = new SoundFile(this, "Rightmixkit-winning-a-coin-video-game-2069.mp3");
  backsound.play();
  backsound.loop();
  backsound.amp(backvol);
  leftscansound.play();
  leftscansound.loop();
  leftscansound.amp(scanvol);
  
  rightscansound.play();
  rightscansound.loop();
  rightscansound.amp(scanvol);
}

void draw() {
  if (sd > 2) return;

  if (sd == 0 ) {
    if (roll>40) {
      rightcoinsound.play();
      rightcoinsound.amp(0.5);
      if (++sd == 1)
        rightscansound.stop();
    } else if (roll > 5) {
      scanvol=abs(roll)/100f;
      rightscansound.amp(scanvol);
      println(scanvol);
    } else {
    }
  } else if (sd==1) {
    if (roll< -40) {
      leftcoinsound.play();
      leftcoinsound.amp(0.5);
      if (++sd == 2)
        leftscansound.stop();
    } else if (roll < -5) {
      scanvol=abs(roll)/100f;
      leftscansound.amp(scanvol);
      println(scanvol);
    } else {
    }
  } else {
    rightscansound.amp(0);
    leftscansound.amp(0);
  }
}

// Read data from the Serial Port
void serialEvent (Serial myPort) { 
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('\n');
  //got any bytes other than the linefeed:
  if (data != null) {
    data = trim(data);
    // split the string at "/"
    String items[] = split(data, '/');
    if (items.length == 1 ) {
      froll = float(items[0]);
      //fpitch = float(items[1]);
      roll = int(froll);
      //pitch = int(fpitch);
    }
    //println(roll);// work successful
    //println(pitch);//do not work, maybe related ro the items.length
  }
}
