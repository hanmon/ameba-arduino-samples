#include "Button.h"
#include "FiniteStateMachine.h"
#include "SetRgbLed.h"
Button button(3);
SetRgbLed rgb(COMMON_ANODE,9,10,11);
//Declaring prototypes of all functions of state
void enterRunning();
void updateRunning();
void exitRunning();
void enterPausing();
void updatePausing();
void exitPausing();
void enterWaiting();
void updateWaiting();
void exitWaiting();

//Defining all states by State object
State RUNNING=State(enterRunning,updateRunning,exitRunning);
State PAUSING=State(enterPausing,updatePausing,exitPausing);
State WAITING=State(enterWaiting,updateWaiting,exitWaiting);
//Initiates Finite State Machine object
FSM stateMachine=FSM(WAITING);

void setup()
{
  Serial.begin(115200);
  button.begin();
}

void loop()
{
	if(button.pressed()){
        Serial.println("Pressed!");
       if(stateMachine.isInState(WAITING)){
           stateMachine.transitionTo(RUNNING);
       }
       else if(stateMachine.isInState(RUNNING)){
           stateMachine.transitionTo(PAUSING);
       }
       else if(stateMachine.isInState(PAUSING)){
           stateMachine.transitionTo(WAITING);
       }
    }
   stateMachine.update();
}

//implementing functions regarding "Running":enterRunning,updateRunning,exitRunning
void enterRunning(){
    Serial.println("enterRunning");
}

void updateRunning(){
    rgb.setColor(RED);
    //Serial.print("updateRunning");
}

void exitRunning(){
    Serial.println("exitRunning");
}
//implementing functions regarding "Pausing":enterPausing,updatePausing,exitPausing
void enterPausing(){
    Serial.println("enterPausing");
}

void updatePausing(){
    rgb.setColor(GREEN);
}

void exitPausing(){
    Serial.println("exitPausing");
}

//implementing functions regarding "Pausing":enterWaiting,updateWaiting,exitWaiting
void enterWaiting(){
    Serial.println("enterWaiting");
}

void updateWaiting(){
    rgb.setColor(BLUE);
}   

void exitWaiting(){
    Serial.println("exitWaiting");
}
