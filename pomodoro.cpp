#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;


HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );

void playBeep();
void help();

void color( int colorn){
   SetConsoleTextAttribute( h,  colorn);        // need to add some checking ... job for another day
}

// definiendo vars
bool startTimer = false;
bool isMatrixRain = false;
int cantPomodoros = 2;
int pomodoro_min = 25;
int sec = 59;
int hour = 0;
int pomodoro_rest = 5; // 5 min de descanzo
//string matrix = "klm8АВCDEFGHГДЅЗИѲІК'ЛМНѮѺПЧРСТѴФХѰѾЦЅЗИѲІК'ЛМНѮѺПЧРСТѴФХѰѾЦ";
char matrix[] = {"klm  8 А В C DEFG  H Г ДЅЗИ ѲІК  ЛМН  ѮѺП  ЧРС Т  Ѵ   Ф Х   Ѱ Ѿ  Ц ЅЗИ ѲІК  Л М Н   Ѯ    ѺП  Ч  Р  С  Т  ѴФ Х Ѱ Ѿ Ц  "};

string input;




void help(){
    cout << "HELP \n";
    cout << "Pomodoro timer \n";
    cout << "Ingrese la cant de pomodoros \n";
    cout << "el sistema comenzara la cuenta y añadira 5 min de descanzo \n";
    cout << "por cada pomodoro que se compute. Ejemplo: \n";    
    cout << "pom 2 \n";
}




void runMatrixRain(){    
    int rnd = 0;    
    string rain = "";
    int max = sizeof(matrix);    
    while(isMatrixRain){
        while (rain.length() < 110){
            rnd = (rand() % max);
            rain  = rain + "    " +  matrix[rnd];                
        }
        cout <<   rain << "\n";         
        Sleep(30);
        rain = "";     
    }
}
string bar ="|";  
// Polimorfismo
void display(){  
    
    system("cls");
    //cout << setfill(' ') << setw(50) << "	POMODORO TIMER		 \n";
    cout << " POMODORO TIMER		 \n";
    cout << " cant pomodoros:" << cantPomodoros << "\n";    
    cout << "cmd> running:" << pomodoro_min << ":" << sec << "  \n";
    if (bar.length() >=10) bar ="|";  
    cout << bar;
   // printf("\t [%.2d:%.2d:%.2d]", cantPomodoros, pomodoro_min, sec);
}

void playBeep(){
    for (int i = 0; i < 5 ; i++){
		Beep(750,200); // xxx hertz (C5) for 200 milliseconds    			
	}
}
 
// runing pomodoros !!
void runPomodoro(){    
    string cancel = "";
    while( true){        
        sec --;
        if (sec==0){
            pomodoro_min--;
            sec = 59;
        }
        if (pomodoro_min == 0){
            cantPomodoros--;
            playBeep();
            pomodoro_min = 25;
        }

        if (cantPomodoros==0){
            break;
        }
        Sleep(1000);
        display();        
		bar =  bar + " |";	          
    }    
}


// runing Timer o Crono !!
void runTimer(){        
    while( true){        
        sec --;
        if (sec==0){
            pomodoro_min--;
            sec = 59;
        }
        if (pomodoro_min == 0){
            cantPomodoros--;
            playBeep();
            pomodoro_min = 59;
        }

        if (cantPomodoros==0){
            break;
        }
        Sleep(1000);
        display();        
		bar =  bar + ">> ";	          
    }    
}

void processInput(string input){
    stringstream ss(input);

    ss.seekg(0, ios::end);
    int size = ss.tellg();
    ss.seekg(0, ios::beg);
    string cmd;
    int p1 = 0;
    int p2 = 0;

    if (size > 20){
        cout << "invalid command" << endl;
    }else{        
        while (ss >> cmd) {                        
            if (cmd == "pom"){                                                
                ss >> p1;
                cantPomodoros = p1;                
                runPomodoro();
            }

            if (cmd == "crono"){                                                                
                ss >> p1;
                ss >> p2;
                cantPomodoros = p1;
                pomodoro_min = p2;
                runTimer();
            }
        }
    }
}

/*
   
*/
void getConsoleCmds(){
    //cantPomodoros << cin.get();
    while(input != "exit"){
        cout << "\n" <<  "cmd> ";
        getline(cin, input);
        processInput(input);
        if (input == "help"){
            help();
        }
    }
}

int main(){
    color( 9);
    //rain();
    getConsoleCmds();
    //cin.get();
    return 0;
}

