#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <bits/stdc++.h>
#include <chrono>
#include <ctime>

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
int cantPomodoros = 0;
int cantHs = 0;
int mins = 0;
int sec = 00;
int hour = 0;
int pomodoro_rest = 5; // 5 mins de descanzo
//string matrix = "klm8АВCDEFGHГДЅЗИѲІК'ЛМНѮѺПЧРСТѴФХѰѾЦЅЗИѲІК'ЛМНѮѺПЧРСТѴФХѰѾЦ";
char matrix[] = {"klm  8 А В C DEFG  H Г ДЅЗИ ѲІК  ЛМН  ѮѺП  ЧРС Т  Ѵ   Ф Х   Ѱ Ѿ  Ц ЅЗИ ѲІК  Л М Н   Ѯ    ѺП  Ч  Р  С  Т  ѴФ Х Ѱ Ѿ Ц  "};

string input;




void help(){
    cout << " HELP \n";
    cout << " Pomodoro timer \n";
    cout << " Ingrese la cant de pomodoros \n";
    cout << " el sistema comenzara la cuenta y añadira 5 mins de descanzo \n";
    cout << " por cada pomodoro que se compute. Ejemplo: \n";    
    cout << " pom 2 <Enter> \n";
}



void smallMatrixRain(){    
    int rnd = 0;    
    string rain = "";
    int max = sizeof(matrix);        
    for (int i = 0; i < 20; i++){
        while (rain.length() < 110){
            rnd = (rand() % max);
            rain  = rain + "    " +  matrix[rnd];                
        }
        cout <<   rain << "\n";                 
        rain = "";        
    }
}

/* Matrix rain */
/*
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
}*/


// https://en.cppreference.com/w/cpp/chrono/c/strftime
string getCurrentDateTime(){
   time_t now = time(0);   
   char* dt = ctime(&now);
   //cout << "Current date and time: " << dt << endl;   
   return dt;
}

int h_cur = 0;
int m_cur = 0;
int s_cur = 0;

// hora , min y sec de inicio.
int h_inicio = 0;
int m_inicio = 0;
int s_inicio = 0;

/* Seteo la hora:min:sec de inicio */
void setInitTime(){
    char buf[64];
    time_t t = time(0);   
    // Time Zone -3  int time_zone = -3;  
    struct tm *tmp = gmtime(&t);    
        h_inicio = ((t / 3600)-3) % 24;  
        m_inicio = (t / 60) % 60;
        s_inicio = t % 60;
}


/* ********************************************
Calcular el tiempo restante
almacenar hora : min : sec
 start time    16 : 35 : 54
       +       25 : 00   
         --------------
 final time   17 : 00 : 00

*********************************************** */
string getRemainingTime(){
    char buf[64];
    time_t t = time(0);     
    struct tm *tmp = gmtime(&t);    
        h_cur = ((t / 3600)-3) % 24;  
        m_cur = (t / 60) % 60;
        s_cur = t % 60;
    // resto honra_min:sec
    hour = h_cur - h_inicio;
    mins = m_cur - m_inicio;
    sec = s_cur --;

  //  printf("%02d:%02d:%02d\n", h_, m_, s_);
  //  strftime(buf, sizeof(buf), "%H:%M:%S\n", tmp);
    //return strftime(buf, sizeof(buf), "%H:%M:%S\n", tmp);
    return to_string(hour).append(":") + to_string(mins).append(":") + to_string(sec);
}


void welcome(){
    cout << "  ------------------------------------------ \n";
    cout << "    WELCOME TO TIMER COMMANDER v 0.01 Alpha \n";
    cout << "    Type Help to how to run commands. \n";
    cout << "  ------------------------------------------ \n";
    cout << "   \n";
}

string bar ="|";  
// Polimorfismo
void display(){      
    system("cls");
    if (bar.length() >=25) bar ="|";  
    smallMatrixRain();
    cout << " \n";
    cout << " -------------------------------------------- \n";
    cout << " Current Date and time: " <<  getCurrentDateTime();
    cout << " -------------------------------------------- \n";
    cout << " POMODORO TIMER		 \n";
    cout << " -------------------------------------------- \n";
    cout << " Starter time: " << h_inicio << ":" << m_inicio << ":" <<  s_inicio << "  \n";
    cout << " running:" << mins << ":" << sec << "  \n";
   // cout << " >>>> " << getRemainingTime();
    cout << " -------------------------------------------- \n";    
    cout << "  " << bar;
    cout << " \n";
    cout << " -------------------------------------------- \n";
   // printf("\t [%.2d:%.2d:%.2d]", cantPomodoros, mins, sec);
}

void playBeep(){
    for (int i = 0; i < 5 ; i++){
		Beep(750,200); // xxx hertz (C5) for 200 milliseconds    			
	}
}



 
// runing pomodoros !!
void runPomodoro(){    
    string cancel = "";
    int milis = 200;
    setInitTime();
    while( true){        
        if (milis==800){  
            milis = 0;            
            getRemainingTime();
        }
        
        if (mins==25){
            playBeep();
            mins = 0;
            cantPomodoros --;
            setInitTime();
        }
        if (cantPomodoros ==0){break;}
        Sleep(200);
        milis = milis + 100;        
        display();        
		bar =  bar.append("|");	          
    }    
}


// runing Timer o Crono !!
void runTimer(){        
    while( true){        
        sec --;
        if (sec==0){
            mins--;
            sec = 59;
        }
        

        if (hour==0 && mins ==0){
            display();
            playBeep();
            break;
        }
         if (mins == 0){
            cantPomodoros--;
            playBeep();
            mins = 59;        
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
                mins = p2;
                runTimer();
            }
        }
    }
}

/*
   keyboard input .... :)
   wainting for input commands ..
*/
void getConsoleCmds(){    
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
    color( 9); // color 9 es el blue y el 10 el green
    //rain();    
    welcome();
    getConsoleCmds();    
    return 0;
}

