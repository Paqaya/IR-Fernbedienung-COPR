#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h>

// HEX Signale
#define ON_OFF 0xE0E06798
#define VOL_UP 0xE0E0E01F
#define VOL_DWN 0xE0E0D02F
// #define CHNL_UP 0xFF0CF3
// #define CHNL_DWN 0xFF44BB

const uint16_t sendPIN = 13;

boolean gedrueckt = false;
int currentAsk;
IRsend irsend(sendPIN);

void setup()
{
	Serial.begin(9600);
	irsend.begin();
}


void loop() {

	int currentAsk = askButton();
	if (currentAsk > 0 && !gedrueckt) {
		gedrueckt = true;
		switch (askButton())
		{
		case 7:
			irsend.sendNEC(ON_OFF, 32);
			Serial.println(7);
			break;
		case 6:
			irsend.sendNEC(VOL_UP, 32);
			Serial.println(6);
			break;
		case 5:
			irsend.sendNEC(VOL_DWN, 32);
			Serial.println(5);
			break;
		}
	} else if (currentAsk > 0 && gedrueckt) {
		gedrueckt = true;
	} else if (currentAsk < 0) {
		gedrueckt = false;
	}
}

int askButton()
{
	// Wenn irgendein Knopf gedrueckt wird
	if (touchRead(T7) < 30)
	{
		return 7;
	}
	else if (touchRead(T6) < 30)
	{
		return 6;
	}
	else if (touchRead(T5) < 30)
	{
		return 5;
	}

	// Wenn nichts gedrueckt
	gedrueckt = false;
	return -1;
}