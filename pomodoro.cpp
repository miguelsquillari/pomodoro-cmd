#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;


// definiendo vars
int cantPomodoros = 2;
int pomodoro_min = 25;
int sec = 59;
int hour = 0;
int pomodoro_rest = 5; // 5 min de descanzo

string input;

void processInput(string input);

void playBeep(){
    for (int i = 0; i < 5 ; i++){
		Beep(750,200); // xxx hertz (C5) for 200 milliseconds    			
	}
}


void getConsoleSetting(){
    cantPomodoros << cin.get();
}


void help(){
    cout << "HELP \n";
    cout << "Pomodoro timer \n";
    cout << "Ingrese la cant de pomodoros \n";
    cout << "el sistema comenzara la cuenta y añadira 5 min de descanzo \n";
    cout << "por cada pomodoro que se compute. \n";
    cin.get();

}

void showOptions(){
    cout << "Ingrese cant de Pomodoros \n";
}


void display(){    
    system("cls");
    cout << setfill(' ') << setw(50) << "	POMODORO TIMER		 \n";
    cout << setfill(' ') << setw(50) << "	CANT POMODORO 		 " << cantPomodoros << "\n";
    cout << setfill(' ') << setw(50) << "	" << pomodoro_min << ":" << sec << "  \n";
   // printf("\t [%.2d:%.2d:%.2d]", cantPomodoros, pomodoro_min, sec);
}

 
// Pomodorosss !!
void pomodoro(){    
    while(cantPomodoros !=0){
        display();
        sec --;
        if (sec==0){
            pomodoro_min--;
            sec = 59;
        }
        if (pomodoro_min == 0){
            cantPomodoros--;
            playBeep();
        }
        Sleep(1000);
    }    
}

void processInput(string input){
    cout << input;
}

int main(){
    pomodoro();
    cout << "INPUT: " << endl;
    cin.get();
    return 0;
}