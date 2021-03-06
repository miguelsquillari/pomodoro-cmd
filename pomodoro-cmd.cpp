#include <stdio.h>
#include <iostream>
#include <windows.h>
//#include <iomanip>
#include <bits/stdc++.h>
#include <chrono>
#include <ctime>

using namespace std;


HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );


void playBeep();
void help();

void setColor( int colorn){
   SetConsoleTextAttribute( h,  colorn);
}

// definiendo vars
//bool startTimer = false;
//bool isMatrixRain = false;
bool restActive = false;
// Pomodoros vars
int cur_cantPomodoros = 0; // current cant pomodoros
int cantPomodoros = 0; // cant de pomodoros
// Alarm
int cantHs = 0;
int mins = 0;
int sec = 00;
int hour = 0;
int pomodoro_rest = 5; // 5 mins de descanzo
//string matrix = "klm8АВCDEFGHГДЅЗИѲІК'ЛМНѮѺПЧРСТѴФХѰѾЦЅЗИѲІК'ЛМНѮѺПЧРСТѴФХѰѾЦ";
char matrix[] = {"klm  8 А В C DEFG  H Г ДЅЗИ ѲІК  ЛМН  ѮѺП  ЧРС Т  Ѵ   Ф Х   Ѱ Ѿ  Ц ЅЗИ ѲІК  Л М Н   Ѯ    ѺП  Ч  Р  С  Т  ѴФ Х Ѱ Ѿ Ц  "};

string input;

string cmd_help = " HELP \n  Pomodoro timer \n  Ingrese la cant de pomodoros \n  el sistema comenzara la cuenta y agregara 5 mins de descanzo \n  por cada pomodoro que se compute. Ejemplo: \n  cmd> pom 2 <Enter> \n   \n  setcolor <0 -15> ej setcolor 5 \n Exit para salir de la aplicacion..\n";


void help(){
     cout << cmd_help;    
}


/* Matrix rain, pero esta limitida a lineas, para que se muestre arriba. */
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
   return dt;
}


string getCurrentDateTimeFormat(){
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%d-%m-%Y %H:%M:%S", std::localtime(&now));
    return s;
}

int h_cur = 0;
int m_cur = 0;
int s_cur = 0;

// hora , min y sec de inicio.
int h_ = 0;
int m_ = 0;
int s_ = 0;

void welcome(){
    cout << " ------------------------------------------------------ \n";
    cout << "    WELCOME TO POMODORO COMMANDER v 0.01 Alpha \n";
    cout << "    Type <<Help>> to know how to run commands. \n";
    cout << " ------------------------------------------------------ \n";
    cout << "   \n";
}

string bar ="|";  
void display(){      
    system("cls");
    if (bar.length() >=25) bar ="|";  
    smallMatrixRain();
    cout << " \n";
    cout << "------------------------------------------------------ \n";
    cout << " Pomodoro Commander		 \n";
    cout << " ------------------------------------------------------ \n";
    cout << " Current Date and time: " <<  getCurrentDateTime();
    cout << " ------------------------------------------------------ \n";  

    if (!restActive){
        cout << " In Progress:";
        printf("%02d:%02d:%02d\n", h_, m_, s_); 
    }else{
        cout << "--> Break <-- ";
        printf("%02d:%02d:%02d\n", h_, m_, s_); 
    }
    
    cout << " ------------------------------------------------------ \n";
    cout << " INFO:" << cantPomodoros << " Pomodoros  \n";
    cout << " ------------------------------------------------------ \n";
    cout << "  " << bar;
    cout << " \n";
    cout << " ------------------------------------------------------ \n";

}

/* Beep params : xxx hertz (C5) , for 200 milliseconds .*/
void playBeep(){
    for (int i = 0; i < 5 ; i++){
		Beep(750,150); }
}



 int secs = 0;
// runing pomodoros !!
void runPomodoro(){        
    int milis = 200;
    auto start = std::chrono::system_clock::now();        
    while( true){        
        if (milis==800){  
            milis = 0;            
            auto end = std::chrono::system_clock::now();    
            std::chrono::duration<double> elapsed_seconds = end-start;
            secs = elapsed_seconds.count();
            h_ = ((secs / 3600)) % 24;  
            m_ = (secs / 60) % 60;
            s_ = secs % 60;            
        }
        
        if (cantPomodoros > 0){
            if (!restActive){
                if (m_==25){
                    playBeep();
                    m_ = 0;
                    cantPomodoros --;  
                    if (cantPomodoros >0){
                        restActive = true;
                        runPomodoro();
                    }            
                }
            }else{
                if (m_==5){
                    restActive = false;
                    playBeep();
                    m_ = 0;                    
                    runPomodoro();                                
                }
            }
        }else{
            restActive = false;        
            getCurrentDateTime();
            bar ="|";
            display();        
            break;
        }
        Sleep(200);
        milis = milis + 200;        
        display();        
		bar =  bar.append("|");	          
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
            // Comando Pom == Pomodoro
            if (cmd == "pom" || cmd == "POM"){
                ss >> p1;
                cantPomodoros = p1;                
                runPomodoro();                
            }            
            if (cmd == "setColor" || cmd == "setcolor"){
                ss >> p1;
                setColor(p1);
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

void addTime(int mins){
    using clock = std::chrono::system_clock;
    clock::time_point nowp = clock::now();
    cout<<"Enter the time that you want to add in minutes"<<endl;
    int time_min;
    cin>>time_min;  
    cin.ignore();
    clock::time_point end = nowp + std::chrono::minutes(time_min);
    time_t nowt =  clock::to_time_t ( nowp );
    time_t endt =  clock::to_time_t ( end);
    std::cout  << " " << ctime(&nowt) << "\n";
    std::cout << ctime(&endt) << std::endl;

}

int main(){
    setColor(3); // color 9 es el blue y el 10 el green /4 dark red / 3 lightblue
    //rain();    
    welcome();
    getConsoleCmds();    
    return 0;
}

