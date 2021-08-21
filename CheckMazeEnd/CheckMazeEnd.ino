//Check Maze end

#define IRsensor A0

int Dist;
int WallDist = 200;
 
void setup() {
 Serial.begin(9600);
 pinMode(IRsensor, INPUT); 
}

//code only for one side
void loop() {
  Dist = analogRead(A0);
  if(Dist < WallDist){
    //move forward 
    //or proceed to drive autonomous car
    Serial.println("Not end of maze");
  }
  else{
    Serial.println("End of maze");
    //stop + unload function
  }

}
