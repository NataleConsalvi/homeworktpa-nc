#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

#include "suitcase.h"

using namespace std;

void richieste_utente(float &x, float &y, float &wb, float &hb, float &hp, float &wh, float &rw, float &angle){
    std::cout << "Inserire i seguenti parametri:" << endl;
    std::cout << "1) Posizione della valigia:" << endl;
    std::cout << "   x = ";
    std::cin >> x;
    std::cout << "   y = ";
    std::cin >> y;
    std::cout << "2) Larghezza della valigia:" << endl;
    std::cout << "   wb = ";
    std::cin >> wb;
    std::cout << "3) Altezza della valigia:" << endl;
    std::cout << "   hb = ";
    std::cin >> hb;
    std::cout << "4) Altezza dell'asta:" << endl;
    std::cout << "   hp = ";
    std::cin >> hp;
    std::cout << "5) Larghezza maniglia:" << endl;
    std::cout << "   wh = ";
    std::cin >> wh;
    std::cout << "6) Raggio delle ruote:" << endl;
    std::cout << "   rw = ";
    std::cin >> rw;
    std::cout << "7) Angolo inclinazione:" << endl;
    std::cout << "   angle = ";
    std::cin >> angle;
}

void position_error(int i){

    if(i == 1){
        std::cout << "Error: extreme left point is out of the file" << endl;
    }else{
        if(i == 2){
            std::cout << "Error: extreme right point is out of the file" << endl;
        }else{
            if(i == 3){
                std::cout << "Error: extreme high point is out of the file" << endl;
            }else{
                if(i == 4){
                    std::cout << "Error: extreme low point is out of the file" << endl;
                }else{
                    std::cout << endl;
                }
                
            }
        }
    }
}

void dimension_error(int i){

    if(i == 1){
        std::cout << "Error: height of the pole is greater than the height of the body" << endl;
    }else{
        if(i == 2){
            std::cout << "Error: width of the handle is greater than the width of the body" << endl;
        }else{
            if(i == 3){
                std::cout << "Error: width of the pole is greater than the width of the handle" << endl;
            }else{
                if(i == 4){
                    std::cout << "Error: radius of the wheels is greater than the half of the width of the body" << endl;
                }else{
                    std::cout << endl;
                }
                
            }
        }
    }
}

void handle_error(int i){

    if(i == 1){
        std::cout << "Error: handle touch the right wheel" << endl;
    }else{
        if(i == 2){
            std::cout << "Error: handle touch the body" << endl;
        }else{
            std::cout << endl;
        }
    }
}

string nats_read_from_file(){
    string nomefile;

    cout << "Inserire il nome del file da leggere! (ricorda .svg)" << endl;
    cin >> nomefile;

    string s;
    ifstream t(nomefile);
    stringstream buffer;
    buffer << t.rdbuf();
    s = buffer.str();

    return s;
}


int main() {

    float x, y, hp, rw, wb, wh, hb, angle;

    NatsSuitcase* device = nats_init();

    int i, j, k;
    do{
        richieste_utente(x, y, wb, hb, hp, wh, rw, angle);
        nats_setparameters(x, y, wb, hb, hp, wh, rw, angle, device);
        nats_setextreme(device);
        i = nats_controllposition(device);
        position_error(i);
        j = nats_controlldimension(device);
        dimension_error(j);
        k = nats_controllhandle(device);
        handle_error(k);

    }while(i != 0 || j != 0 || k != 0);

    char quote;
    do{
        cout << "Inserire le quote? [Y = yes || N = no] ";
        cin >> quote;
        if(quote != 'Y' && quote != 'N'){
            cout << "Carattere errato!" << endl;
        }

    }while(quote != 'Y' && quote != 'N');

    string s = nats_svg(device, quote);

    bool t = nats_write_file(s);

    std::cout << t << endl;
}
