/* AUTHOR: Marin Gudelj
 *  CO-AUTHOR: Bruno Borić
 *  MENTOR: Danko Marušić
 */


int speed_value,input_length;
String frequency,input_info;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600,SERIAL_7E1);
  pinMode(8,OUTPUT);
      Serial.println("1 - 100: CW");
      Serial.println("-100 - -1: CCW");
      Serial.println("0: STOP");
      Serial.println("Unesi brzinu: ");
}

//function for calculating the part of the VFD code for wanted frequency + 2 end bytes

String F(int j){
  String y=":FF062001"; //first part of VFD code
  int z[4],w=1,q=38;
  j=abs(j)*50;
  for(int v=3;v>=0;v--){
    z[v]=j%16;
    j/=16;
  }
  for(int v=0;v<4;v++){
    if(z[v]<10){
    y+=z[v];
    }
    else if(z[v]==10){
      y+="A";
    }
    else if(z[v]==11){
      y+="B";
    }
    else if(z[v]==12){
      y+="C";
    }
    else if(z[v]==13){
      y+="D";
    }
    else if(z[v]==14){
      y+="E";
    }
    else if(z[v]==15){
      y+="F";
    }
    if (w%2 !=0){
    q+=(z[v]*16);
    }else{
    q+=z[v];
    }
    w++;
  }
  //2 end bytes
  if(q<=256){
  q=256-q;
  }else{
    q=256-(q-256);
  }
  for(int v=1;v>=0;v--){
    z[v]=q%16;
    q/=16;
  }
  for(int v=0;v<2;v++){
    if(z[v]<10){
    y+=z[v];
    }
    else if(z[v]==10){
      y+="A";
    }
    else if(z[v]==11){
      y+="B";
    }
    else if(z[v]==12){
      y+="C";
    }
    else if(z[v]==13){
      y+="D";
    }
    else if(z[v]==14){
      y+="E";
    }
    else if(z[v]==15){
      y+="F";
    }
  }
  return y;
}


//main code
void loop() {
  if(Serial.available()>0){
   input_info=Serial.readString();
      Serial.println("1 - 100: CW");
      Serial.println("-100 - -1: CCW");
      Serial.println("0: STOP");
      Serial.println("Unesi brzinu: ");
  input_length=input_info.length();
  for(int c=0;c<input_length-1;c++){
    if(c!=0){
    speed_value=(speed_value*10)+((int)input_info[c]-48);
    }else if (input_info[c]!='-'){
      speed_value=(int)input_info[c]-48;
  }else if (input_info[c]=='-'){
    speed_value=0;
  } 
  }
  if(input_info[0]=='-'){
    speed_value=(-speed_value);
  }
  frequency=F(speed_value);
  if(speed_value<0){
      digitalWrite(8,HIGH);
      Serial1.print(":FF0620000022B9\r\n");
      delay(20);
      digitalWrite(8,LOW);
      delay(20);
      delay(20);
      digitalWrite(8,HIGH);
      Serial1.println(frequency);
      delay(20);
      digitalWrite(8,LOW);
      delay(20);
  }else if (speed_value>=0){
      digitalWrite(8,HIGH);
      Serial1.println(frequency);
      delay(20);
      digitalWrite(8,LOW);
      delay(20);
      delay(20);
    digitalWrite(8,HIGH);
      Serial1.print(":FF0620000012C9\r\n");
      delay(20);
      digitalWrite(8,LOW);
      delay(20);
  }
}}
