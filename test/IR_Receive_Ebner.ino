// #include <IRremote.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>

const int greenLEDpin = 22;
const int kRecvPin = 4;
IRrecv irrecv(kRecvPin);

decode_results results;

void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn();
	pinMode(2, OUTPUT);
	pinMode(greenLEDpin, OUTPUT);

	Serial.print("Es wird auf ein IR Signal bei PIN ");
	Serial.print(kRecvPin);
	Serial.println(" gewartet! \n");
}

void loop()
{

	if (irrecv.decode(&results))
	{
		switch (results.value)
		{
		case 0xFFA45B:
			Serial.println("OK");
			digitalWrite(greenLEDpin, HIGH);
			break;
		case 0xFF14EB:
			Serial.println("Volume UP");
			break;
		case 0xFF24DB:
			Serial.println("Volume DOWN");
			break;
		case 0xFF04FB:
			Serial.println("MODE");
			break;
		case 0xFFC43B:
			Serial.println("HOME");
			break;
		case 0xFF0CF3:
			Serial.println("Arrow UP");
			break;
		case 0xFF44BB:
			Serial.println("Arrow DOWN");
			break;
		case 0xFFE41B:
			Serial.println("Arrow LEFT");
			break;
		case 0xFF649B:
			Serial.println("Arrow RIGHT");
			break;
		case 0xFFFFFFFFFFFFFFFF:
			break;
		default:
			Serial.println(results.value, HEX);
		}

		digitalWrite(2, HIGH);
		delay(250);
		digitalWrite(2, LOW);
		digitalWrite(greenLEDpin, LOW);
		irrecv.resume();
	}
}


/*
		*/