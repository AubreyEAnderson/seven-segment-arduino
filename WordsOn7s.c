#include "WordsOn7s.h"

void loop() {
	digressionTimer();
}

void digressionTimer() {	
	if (screenOff()) {
		displayWord(blanks);
	}
	else if (timeSince(lastDigression) < DIGRESS_TIME*1000) {
		countdown(DIGRESS_TIME, timeSince(lastDigression));
	}
	else {
		countdown(STUDY_TIME, timeSince(lastDigression+DIGRESS_TIME*1000));
	}

	if (timeSince(lastDigression)/1000 > DIGRESS_TIME+STUDY_TIME) {
		digressed = false;
	}
	digitalWrite(13, digressed);
}

/*
 * returns whether the screen should be off
 *
 */

bool screenOff() {
	return (!digressed || timeSince(lastDigression) > DIGRESS_TIME*1000
	        && timeSince(lastPressed) > SCREEN_TIMEOUT*1000);
}
	

/*
 * ensures digressed is set to true
 * resets the time since the button was last pressed to the current time
 */
void userInput() {
	if (!digressed) {
		lastDigression = millis();
	}
	digressed = true;
	lastPressed = millis();
}


void setup() {
	//sets each digit to LOW so it does not display
	for (int i = 0; i < sizeof(DIGITS)/sizeof(int); i++) {
		pinMode(DIGITS[i], OUTPUT);
		digitalWrite(DIGITS[i], LOW);
	}

	//sets each segment to HIGH so they do not display
	for (int i = 0; i < sizeof(segs)/sizeof(int); i++) {
		pinMode(segs[i], OUTPUT);
		digitalWrite(segs[i], HIGH);
	}

	// sets the button to call userInput when pressed
	pinMode(button, INPUT_PULLUP);
	attachInterrupt(0, userInput, FALLING);

	pinMode(13, OUTPUT);
}

/*
 * Overloaded displayLetter function
 * defaults to no decimal point
 *
 * int digit: The digit to display the letter on (0-based)
 * int* letter: The letter to display 
 */
void displayLetter(int digit, int *letter) {
displayLetter(digit, letter, false);
}


/* 
 * Displays the letter on the given digit for 1ms
 * supposed to be run in a loop to take advantage of multiplexing
 *
 * int digit: The digit to display the letter on (0-based)
 * int* letter: The letter to display
 * bool DP: whether to display a decimal after the number
 */
void displayLetter(int digit, int *letter, boolean DP) {4
	// set each segment that will be turned on low
	for (int i = 0; i < (sizeof(segs)/sizeof(int))-1; i++) {
		digitalWrite(segs[i], !*(letter+i));
	}
	digitalWrite(segs[(sizeof(segs)/sizeof(int))-1], !DP);

	// turn on the digit to be displayed for 1 ms
	digitalWrite(DIGITS[digit], HIGH);
	delay(1);
	digitalWrite(DIGITS[digit],LOW);
}

/*
 * Displays the first 4 letters of the given word
 * supposed to be run in a loop to take advantage of multiplexing
 * int *statement[]: an array of pointers to the letters of the word
 */
void displayWord(int *statement[]) {
	// for each digit, display the corresponding letter
	for (int i = 0; i < sizeof(DIGITS)/sizeof(int); i++) {
		displayLetter(i, statement[i], false);
	}
}

/*
 * Scrolls the given sentence across the screen using multiplexing
 * waits 1s before scrolling each letter
 *
 * int *sentence[]: an array of pointers to the letters of the word
 * int sentence_len: the length of the array
 */
void scrollSentence(int *sentence[], int sentence_len) {
	int counter = 0;
	while (counter <= sentence_len) {
		// for each digit display the next 4 letters starting at the counter index
		for (int i = 0; i < sizeof(DIGITS)/sizeof(int); i++) {
			if (counter+i < sentence_len) {
				displayLetter(i, sentence[counter+i]);
			}
		}
		// after 1s continue to the next letter
		if (millis() - previousMillis > 1000) {
			previousMillis = millis();
			counter++;
		}

	}
}

/*
 * Overloaded display number
 * defaults to no decimal point
 *
 * int number: the 4-digit number to display 
 */
void displayInt(int number) {
	displayInt(number, false);
}

/*
 * Displays the 4 digits number
 * meant to be run in a loop to take advantage of multiplexing
 *
 * int number: the 4-digit number to display. if a larger number is given, only 
 *             the 4 most significant digits are displayed
 * boolean DP: display the decimal point in between the 2nd and 3rd digit
 */
void displayInt(int number, bool DP) {
	// uses modulo-math and int-division truncation to extract the digit
	int blanks=true;
	displayLetter(0, NUMBERS[(int) (number/1000)]);
	displayLetter(1, NUMBERS[(int) (number%1000/100)], DP);
	displayLetter(2, NUMBERS[(int) (number%100/10)]);
	displayLetter(3, NUMBERS[(int) (number%10)]);
}


void countdown(unsigned long seconds, unsigned long start) {
	displayInt(secondsToMinutesSeconds(seconds - timeSince(start)/1000), true);
}

void countup(unsigned long start) {
	displayInt(secondsToMinutesSeconds(timeSince(start)/1000), true);
}

int secondsToMinutesSeconds(unsigned long seconds) {
	return (seconds/60*100)+(seconds%60);
}

unsigned long timeSince(unsigned long time) {
	return millis() - time;
}

