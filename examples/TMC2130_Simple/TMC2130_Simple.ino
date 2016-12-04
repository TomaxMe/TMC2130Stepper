#define EN_PIN    38  // Nano v3:	16 Mega:	38	//enable (CFG6)
#define DIR_PIN   55  //			19			55	//direction
#define STEP_PIN  54  //			18			54	//step
#define CS_PIN    40  //			17			64	//chip select

bool dir = 0;


#include <TMC2130Stepper.h>
TMC2130Stepper TMC2130 = TMC2130Stepper(EN_PIN, DIR_PIN, STEP_PIN, CS_PIN);

void setup() {
	Serial.begin(9600);
	TMC2130.begin();
	TMC2130.SilentStepStick2130(600);
	TMC2130.stealthChop(1);
	
	digitalWrite(EN_PIN, LOW);
}

void loop() {
	digitalWrite(STEP_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(STEP_PIN, LOW);
	delayMicroseconds(10);
	uint32_t ms = millis();
	static uint32_t last_time = 0;
	if ((ms - last_time) > 2000) {
		if (dir) {
			Serial.println("Dir -> 0");
			TMC2130.shaft_dir(0);
			Serial.println(TMC2130.GCONF(), BIN);
			dir = 0;
		} else {
			Serial.println("Dir -> 1");
			TMC2130.shaft_dir(1);
			Serial.println(TMC2130.GCONF(), BIN);
			dir = 1;
		}
		last_time = ms;
	}
}
