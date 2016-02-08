#ifndef WORDSON7S_H
#define WORDSON7S_H

void loop();
void digressionTimer();
bool screenOff();
void userInput();
void setup();
void displayLetter(int digit, int *letter);
void displayWord(int *statement[]);
void scrollSentence(int *sentence[], int sentence_len);
void displayInt(int number);
void displayInt(int number, bool DP);
void countdown(unsigned long seconds, unsigned long start);
void countup(unsigned long start);
int secondsToMinutesSeconds(unsigned long seconds);
unsigned long timeSince(unsigned long time);

// Timer times in seconds
unsigned long DIGRESS_TIME = 100;
unsigned long STUDY_TIME = 300; 
unsigned long SCREEN_TIMEOUT = 15;

/* 
 * Each segment is connected to digital output on the arduino board
 * the segment variables are assigned the digital output pin number
 * The corresponding pin on the seven segment display should be connected
 * to the given pin
 */
int segA = 1;   //Display pin 11
int segB = 10;  //Display pin 7
int segC = 4;   //Display pin 4
int segD = 5;   //Display pin 2
int segE = 6;   //Display pin 1
int segF = 3;   //Display pin 10
int segG = 0;   //Display pin 5
int segDP = 11; //Display pin 3
int segs[8] = {segA, segB, segC, segD, segE, segF, segG, segDP};


// DIGITS is an array of the digital output pin to which the corresponding display pin is connected
//          Display pin-> GPIO map
// Display pin: 12    9     8     6
//             ___   ___   ___   ___
//            |   | |   | |   | |   |
//            |___| |___| |___| |___|
//            |   | |   | |   | |   |
//            |___| |___| |___| |___|
int DIGITS[4]= {7,    8,    9,   12}; //DigitalIO pin on Arduino connected to corresponding display pin

// The digital outpin pin connected to the button
int button = 2;

// These arrays hold the correct output to display the given letters
//            1: turn on segment
//            0: turn off segment
//            {A, B, C, D, E, F, G}
int A[]     = {1, 1, 1, 0, 1, 1, 1};
int a[]     = {0, 0, 1, 1, 1, 0, 1};
int B[]     = {1, 1, 1, 1, 1, 1, 1};
int b[]     = {0, 0, 1, 1, 1, 1, 1};
int C[]     = {1, 0, 0, 1, 1, 1, 0};
int c[]     = {0, 0, 0, 1, 1, 0, 1};
int D[]     = {1, 1, 1, 1, 1, 1, 0};
int d[]     = {0, 1, 1, 1, 1, 0, 1};
int E[]     = {1, 0, 0, 1, 1, 1, 1};
int e[]     = {1, 1, 0, 1, 1, 1, 1};
int F[]     = {1, 0, 0, 0, 1, 1, 1};
int G[]     = {1, 0, 1, 1, 1, 1, 1};
int g[]     = {1, 1, 1, 1, 0, 1, 1};
int H[]     = {0, 1, 1, 0, 1, 1, 1};
int h[]     = {0, 0, 1, 0, 1, 1, 1};
int I[]     = {0, 0, 0, 0, 1, 1, 0};
int i[]     = {0, 0, 1, 0, 0, 0, 0};
int J[]     = {0, 1, 1, 1, 1, 0, 0};
int j[]     = {0, 1, 1, 1, 1, 0, 0};
int K[]     = {0, 1, 1, 0, 1, 1, 1};
int L[]     = {0, 0, 0, 1, 1, 1, 0};
int l[]     = {0, 1, 1, 0, 0, 0, 0};
int ll[]    = {0, 1, 1, 0, 1, 1, 0};
int M[]     = {1, 0, 1, 0, 1, 0, 0};
int M1[]    = {1, 1, 0, 0, 1, 1, 0};
int M2[]    = {1, 1, 1, 0, 0, 1, 0};
int m1[]    = {0, 0, 1, 0, 1, 0, 1};
int m2[]    = {0, 0, 1, 0, 1, 0, 1};
int N[]     = {1, 1, 1, 0, 1, 1, 0};
int n[]     = {0, 0, 1, 0, 1, 0, 1};
int O[]     = {1, 1, 1, 1, 1, 1, 1};
int o[]     = {0, 0, 1, 1, 1, 0, 1};
int R[]     = {1, 1, 1, 0, 1, 1, 1};
int r[]     = {0, 0, 0, 0, 1, 0, 1};
int S[]     = {1, 0, 1, 1, 0, 1, 1};
int s[]     = {1, 0, 1, 1, 0, 1, 1};
int T[]     = {1, 1, 1, 0, 0, 0, 0};
int t[]     = {0, 0, 0, 1, 1, 1, 1};
int u[]     = {0, 0, 1, 1, 1, 0, 0};
int w1[]    = {0, 0, 1, 1, 1, 0, 0};
int w2[]    = {0, 0, 1, 1, 1, 0, 0};
int Y[]     = {0, 1, 1, 1, 0, 1, 1};
int blank[] = {0, 0, 0, 0, 0, 0, 0};
int ZERO[]  = {1, 1, 1, 1, 1, 1, 0};
int ONE[]   = {0, 1, 1, 0, 0, 0, 0};
int TWO[]   = {1, 1, 0, 1, 1, 0, 1};
int THREE[] = {1, 1, 1, 1, 0, 0, 1};
int FOUR[]  = {0, 1, 1, 0, 0, 1, 1};
int FIVE[]  = {1, 0, 1, 1, 0, 1, 1};
int SIX[]   = {1, 0, 1, 1, 1, 1, 1};
int SEVEN[] = {1, 1, 1, 0, 0, 0, 0};
int EIGHT[] = {1, 1, 1, 1, 1, 1, 1};
int NINE[]  = {1, 1, 1, 1, 0, 1, 1};

int *NUMBERS[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
unsigned long previousMillis = 0;


#endif
