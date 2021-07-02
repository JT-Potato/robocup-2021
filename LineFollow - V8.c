#pragma config(Sensor, S1,     leftSensor,     sensorEV3_Color)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Functions
float leftSensorValue;
float rightSensorValue;
float leftMotorSpeed;
float rightMotorSpeed;

bool greenFlagLeft = false;
bool greenFlagRight = false;

//Line following
void lineFollow() { //function
	//Tweaking the values
	leftMotorSpeed = leftSensorValue/2
	rightMotorSpeed = rightSensorValue/2

	if (leftSensorValue < 20) { //emergency value
		leftMotorSpeed = -80;
		rightMotorSpeed = 80;
	}
	if (rightSensorValue < 20) {
		rightMotorSpeed = -80;
		leftMotorSpeed = 80;
	}

	setMotorSpeed(leftMotor, leftMotorSpeed); //Set leftMotor speed
	setMotorSpeed(rightMotor, rightMotorSpeed); //Set leftMotor speed
}

//Green, for right sensor
void rightSensorGreen() {
	if (getColorName(rightSensor) == colorGreen) {
		//Check if its really green
		setMotorSpeed(leftMotor, 10);
		setMotorSpeed(rightMotor, 10);
		sleep(50);
		if (getColorName(rightSensor) == colorGreen) {
			playSound(soundBlip);
			//turn
			moveMotorTarget(leftMotor, 360, 80);
			sleep(250);
		}
	}
	greenFlagRight = false;
}

//Green, for left sensor
void leftSensorGreen() {
	if (getColorName(leftSensor) == colorGreen) {
		//Check if its really green
		setMotorSpeed(leftMotor, 10);
		setMotorSpeed(rightMotor, 10);
		sleep(50);
		if (getColorName(leftSensor) == colorGreen) {
			playSound(soundBlip);
			//turn
			moveMotorTarget(rightMotor, 360, 80);
			sleep(250);
		}
	}
	greenFlagLeft = false;
}

task main()
{
	while (true) {
		leftSensorValue = getColorReflected(leftSensor); //Left sensor value
		rightSensorValue = getColorReflected(rightSensor); //Right sensor value

		//Display Values
		/*string leftValueString = leftSensorValue;
		string rightValueString = rightSensorValue;
		strcat(leftValueString, " ");
		strcat(leftValueString, rightValueString);
		string stringToDisplay = leftValueString;
		displayBigTextLine(1, stringToDisplay);*/

		//Green:
		//We set flags, to give the robot a tiny bit of time to get rid of any false greens

		//Acts on flags, if any
		if (greenFlagLeft) {
			leftSensorGreen();
		}
		if (greenFlagRight) {
			rightSensorGreen();
		}

		//Sets flags
		if (leftSensorValue < 30) {
			//Set a flag to check for green next time
			greenFlagLeft = true;
		}
		if (rightSensorValue < 30) {
			//Set a flag to check for green next time
			greenFlagRight = true;
		}

		lineFollow();
	} //end of while loop
} //end of task main