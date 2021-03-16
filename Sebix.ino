#define NumberOfSeconds(_time_)((_time_/300-4))

#include <LiquidCrystal.h> // Biblioteca para usar o lcd
#include <EEPROM.h> // Biblioteca para salvar dados no arduino


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

 
#define melodyPin 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Onde as entradas do lcd estão no arduino

int pino_start = 1; // Pino do arduino ligado ao botão start
int estado_start = 0; 

int pulando = 0;

int address = 0;  
int value

// Underworld melody 
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};

int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
 

int song = 0;
 

// Pixels do dinossauro com dois pés
byte dino[8] = {
  B00111,
  B00101,
  B00111,
  B00110,
  B10111,
  B11110,
  B01010,
  B11111
};

byte dino_pulando[8] = {
  B00111,
  B00101,
  B00111,
  B00110,
  B10111,
  B11110,
  B01010,
  B00000
};
  
byte chao[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};

byte cacto[8] = {
  B00100,
  B10100,
  B10100,
  B11101,
  B00111,
  B00100,
  B00100,
  B11111
};

// Pixels da cobra
byte cobra[8] = {
  B00000,
  B00000,
  B01100,
  B01100,
  B00101,
  B00101,
  B00111,
  B11111
};

// Pixels do passáro

byte passaro[8] = {
    B00000,
    B00100,
    B00110,
    B01110,
    B11111,
    B00000,
    B00000,
    B00000
};

// Pixels do dino caido

byte dino_caido1[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00011,
    B00111,
    B00011,
    B00111
};
 
byte dino_caido2[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11101,
    B10111
};

void setup() {
  lcd.begin(16, 2);
  pinMode(8, OUTPUT);
	
  // Criação dos desenhos a serem utilizados
  lcd.createChar(0, dino);
  lcd.createChar(1, dino_caido1);
  lcd.createChar(2, dino_caido2);
  lcd.createChar(3, chao);
  lcd.createChar(4, cacto);
  lcd.createChar(5, cobra);
  lcd.createChar(6, passaro);
  lcd.createChar(7, dino_pulando);
  
  pinMode(pino_start, INPUT);
  estado_start = 0;
  pulando = 0;
}

void loop() {
  tela_inicial();
  
  estado_start = digitalRead(pino_start);
  if(estado_start == 1){ 
    long unsigned anterior = millis();
  	cenario();
  	scroll(anterior);
  }
}

int CasasDec(int seconds){ // Contar quantas casas decimais têm score
  int i = 1;
  while (seconds/10>0){
    seconds=seconds/10;
    i++;
  }
  return i;
}

int count(int seconds){ // Printar o score
 int score= seconds;
 value = EEPROM.read(address);
 if(score>=value){
    EEPROM.write(address,score);
    value=score;
 }
  
 int position=15;
 int quant = CasasDec(seconds);
 position=position - quant + 1;
 lcd.setCursor(position,0);
 lcd.print(seconds);
  
 return value;
}

void sing(int s) { // Toca as notas do Mario 
  
  song = s;
  if (song == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / underworld_tempo[thisNote];
      buzz(melodyPin, underworld_melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      buzz(melodyPin, 0, noteDuration);
 
    }
 
  } 
}
 
void buzz(int targetPin, long frequency, long length) { // Controla a frequência do buzzer
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; 
  long numCycles = frequency * length / 1000; 
  for (long i = 0; i < numCycles; i++) { 
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue); 
    digitalWrite(targetPin, LOW); 
    delayMicroseconds(delayValue); 
  }
  digitalWrite(13, LOW);
 
}

void tela_inicial() { // Cria a tela inicial do jogo
  lcd.setCursor(3,0);
  lcd.print("SEBIX GAME");
  
  lcd.setCursor(3,1);
  lcd.print("Press Start");
  
}

void cenario() { // Cria o cenário inical, dino e chão
  lcd.clear();
  delay(30);

  for(int i = 1; i <= 16; i++) {
    lcd.setCursor(i,1);
    lcd.write(3);
  }

  lcd.setCursor(0,1);
  lcd.write(byte(0));
  delay(1000);
}

void dino_pula() { // Função do pulo, vai apagando e desenhando o dino nos devidos locais
  estado_start = digitalRead(pino_start);
  
  if(estado_start == HIGH) {
    pulando = 1;
    
    lcd.setCursor(0,1);
    lcd.write(3);

    lcd.setCursor(0,0);
    lcd.write(7);
    
    unsigned long tempo = millis();
  	while(millis() < tempo + 200) {}
  }
}
  
void dino_caindo() {
    lcd.setCursor(0,0);
    lcd.print(" ");

    lcd.setCursor(0,1);
    lcd.write(byte(0));
    
    pulando = 0;
}

int obstaculo_aparece() { // Switch case que seleciona um obstaculo aleatoriamente
  int obstaculo;
  
  randomSeed(analogRead(A0));
  
  switch(random(4,7)) {
    case 4:
    	obstaculo = 4;
    	break;
    case 5:
    	obstaculo = 5;
    	break;
    case 6:
    	obstaculo = 6;
    	break;
  }
  return(obstaculo);
}  

void scroll(long unsigned anterior) { //Função que move o cenário, tanto o chao quanto os obstáculos
  int aux1 = obstaculo_aparece();
  int aux2 = obstaculo_aparece();
  int aux3 = obstaculo_aparece();
  int flag = 0;

  for(int i = 15, j = 21, k = 27; i >= -1; i--,j--,k--) {
    
    if(aux1 == 6){
    	lcd.setCursor(i,0);
    	lcd.write(byte(aux1));
      
      	lcd.setCursor(i + 1,0);
    	lcd.write(' '); 
    } else {
		lcd.setCursor(i,1);
    	lcd.write(byte(aux1));
      
      	lcd.setCursor(i + 1,1);
    	lcd.write(3); 
	}
       
    if(aux2==6){
    	lcd.setCursor(j,0);
    	lcd.write(byte(aux2));
      
      	lcd.setCursor(j + 1,0);
    	lcd.write(' '); 
    } else {
	lcd.setCursor(j,1);
    	lcd.write(byte(aux2));
      
      	lcd.setCursor(j + 1,1);
    	lcd.write(3); 
	}
    
    if(aux3==6){
    	lcd.setCursor(k,0);
    	lcd.write(byte(aux3));
      
      	lcd.setCursor(k + 1,0);
    	lcd.write(' '); 
    } else {
	lcd.setCursor(k,1);
    	lcd.write(byte(aux3));
      
      	lcd.setCursor(k + 1,1);
    	lcd.write(3); 
	}
    
    unsigned long time= millis();
    unsigned long teste= time-anterior;
    int seconds = NumberOfSeconds(teste);
    int high = count(seconds); // Função para rodar o score no display
    
    if (i == -1){ // Permite o aparecimento de novos obstáculos
	 i = j;
     aux1 = aux2;
     
     j = k;
     aux2 = aux3;
     
     k = 16;
     aux3 = obstaculo_aparece();
   
     flag = 0;
    }
    
    // O conjunto a seguir verifica a condição de derrota
    unsigned long tempo = millis();
  	while(millis() < tempo + 300) {
      dino_pula();
      if(aux1==6){
        if(i == 1 && pulando == 1) {
          flag = 1;
        }
        if(i == 0 && flag == 1) {
          perdeu(high);
        }
      } else {
        if(i == 1 && pulando == 1) {
          flag = 1;
        }
        if(i == 0 && flag == 0) {
          perdeu(high);
        }
      }
      dino_caindo();
	}
  }
}

void perdeu(int high) { // Configuração da tela final após perder
  lcd.clear();
  delay(50);
  tela_game_over();
  delay(1000);
  tela_best_score(high);
}

void tela_game_over() { // Print da tela game over
  lcd.setCursor(5,0);
  lcd.print("TOMBOU!");
  
  lcd.setCursor(1,1);
  lcd.write(1);
  
  lcd.setCursor(2,1);
  lcd.write(2);
}

void tela_best_score(int high) { // Print tela final com o top score
  lcd.clear();
  
  lcd.setCursor(1,0);
  lcd.print("TOP SCORE: ");
  
  lcd.setCursor(13,0);
  lcd.print(high);
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  
  lcd.setCursor(3,1);
  lcd.print("Press Reset");
  
  sing(2);
  while(1);
}
