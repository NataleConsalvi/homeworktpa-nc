#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

#include "suitcase.h"

using namespace std;

void nats_stamp_error(int i){
    switch(i){
        case 0:

            break;
        case 1:
            cout << "Error: angle if out of range [0, 360]" << endl;
            break;
        case 2:
            cout << "Error: position x of suitcase is null or negative" << endl;
            break;
        case 3:
            cout << "Error: position y of suitcase is null or negative" << endl;
            break;
        case 4:
            cout << "Error: width of the body is null or negative" << endl;
            break;
        case 5:
            cout << "Error: height of the body is null or negative" << endl;
            break;
        case 6:
            cout << "Error: height of the pole is null or negative" << endl;
            break;
        case 7:
            cout << "Error: width of the handle is null or negative" << endl;
            break;
        case 8:
            cout << "Error: radius of the wheels is null or negative" << endl;
            break;
        case 9:
            cout << "Error: extreme left point is out of the file" << endl;
            break;      
        case 10:
            cout << "Error: extreme right point is out of the file" << endl;
            break;      
        case 11:
            cout << "Error: extreme high point is out of the file" << endl;
            break;
        case 12:
            cout << "Error: extreme low point is out of the file" << endl;
            break;
        case 13:
            cout << "Error: height of the pole is greater than the height of the body" << endl;
            break;      
        case 14:
            cout << "Error: width of the handle is greater than the width of the body" << endl;
            break;      
        case 15:
            cout << "Error: width of the pole is greater than the width of the handle" << endl;
            break;
        case 16:
            cout << "Error: radius of the wheels is greater than the half of the width of the body" << endl;
            break;
        case 17:
            cout << "Error: handle touch the wheel" << endl;
            break;
        case 18:
            cout << "Error: handle touch the body" << endl;
            break;
        default:

            break;
    }
}

void nats_handling_parameters(int i, NatsParameters* param){
    switch(i){
        case 0:

            break;
        case 1:
            int i1;
            do{
                cout << "Re-enter angle beetween body and pole:" << endl;
                cout << "   angle = ";
                cin >> param->angle;
                i1 = nats_controlparameters(param);
            }while(i1 == 1);
            break;
        case 2:
            int i2;
            do{
                cout << "Re-enter position x:" << endl;
                cout << "   x = ";
                cin >> param->x;
                i2 = nats_controlparameters(param);
            }while(i2 == 2);
            break;
        case 3:
            int i3;
            do{
                cout << "Re-enter position y:" << endl;
                cout << "   y = ";
                cin >> param->y;
                i3 = nats_controlparameters(param);
            }while(i3 == 3);
            break;
        case 4:
            int i4;
            do{
                cout << "Re-enter width of the body:" << endl;
                cout << "   wb = ";
                cin >> param->wb;
                i4 = nats_controlparameters(param);
            }while(i4 == 4);
            break;
        case 5:
            int i5;
            do{
                cout << "Re-enter height of the body:" << endl;
                cout << "   hb = ";
                cin >> param->hb;
                i5 = nats_controlparameters(param);
            }while(i5 == 5);
            break;
        case 6:
            int i6;
            do{
                cout << "Re-enter height of the pole:" << endl;
                cout << "   hp = ";
                cin >> param->hp;
                i6 = nats_controlparameters(param);
            }while(i6 == 6);
            break;
        case 7:
            int i7;
            do{
                cout << "Re-enter width of the handle:" << endl;
                cout << "   wh = ";
                cin >> param->wh;
                i7 = nats_controlparameters(param);
            }while(i7 == 7);
            break;
        case 8:
            int i8;
            do{
                cout << "Re-enter radius of the wheels:" << endl;
                cout << "   rw = ";
                cin >> param->rw;
                i8 = nats_controlparameters(param);
            }while(i8 == 8);
            break;
        default:

            break;
    }
}


void nats_enter_parameters(NatsParameters* param){
    int i = 0;
    
    std::cout << "Inserire i seguenti parametri:" << endl;
    std::cout << "1) Posizione della valigia:" << endl;
    std::cout << "   x = ";
    std::cin >> param->x;
    std::cout << "   y = ";
    std::cin >> param->y;
    std::cout << "2) Larghezza della valigia:" << endl;
    std::cout << "   wb = ";
    std::cin >> param->wb;
    std::cout << "3) Altezza della valigia:" << endl;
    std::cout << "   hb = ";
    std::cin >> param->hb;
    std::cout << "4) Altezza dell'asta:" << endl;
    std::cout << "   hp = ";
    std::cin >> param->hp;
    std::cout << "5) Larghezza maniglia:" << endl;
    std::cout << "   wh = ";
    std::cin >> param->wh;
    std::cout << "6) Raggio delle ruote:" << endl;
    std::cout << "   rw = ";
    std::cin >> param->rw;
    std::cout << "7) Angolo inclinazione:" << endl;
    std::cout << "   angle = ";
    std::cin >> param->angle;
    do{
        i = nats_controlparameters(param);
        nats_stamp_error(i);
        nats_handling_parameters(i, param);
        i = nats_controlparameters(param);
    }while(i != 0);

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


    cout << "Start: device SUITCASE" << endl;
    char choice;

    do{
        cout << "  Choose: [l] = load file .svg;" << endl;
        cout << "          [n] = create new file .svg" << endl;
        cin >> choice;
        if(choice != 'l' && choice != 'n'){
            cout << "Error: wrong character, repeat choice!" << endl;
        }
    }while(choice != 'l' && choice != 'n');

    if(choice == 'n'){

        NatsParameters* param = nats_init_param();
        NatsSuitcase* device = nats_init_device();

        int i, j, k;

        do{
            nats_enter_parameters(param);
            nats_setparameters(param, device);
            nats_setextreme(device);
            i = nats_controlposition(device);
            nats_stamp_error(i);
            j = nats_controldimension(device);
            nats_stamp_error(j);
            k = nats_controlhandle(device);
            nats_stamp_error(k);

        }while(i != 0 || j != 0 || k != 0);

        char quote;
        do{
            cout << "Inserire le quote? [Y = yes || N = no] ";
            cin >> quote;
            if(quote != 'Y' && quote != 'N'){
                cout << "Carattere errato!" << endl;
            }

        }while(quote != 'Y' && quote != 'N');

        string s = nats_to_svg(device, quote);
        
        string nome;

        cout << "Scrivere il nome del file (es: nomefile.svg)" << endl;
        cin >> nome;

        bool t = nats_write_file(s, nome);

        std::cout << t << endl;

    }else{


        string total = nats_read_from_file();

        NatsParameters* param2 = nats_init_param();

        nats_svg_to_param(total, param2);
        
        NatsSuitcase* device2 = nats_init_device();

        nats_setparameters(param2, device2);

        string s2 = nats_to_svg(device2, 'Y');

        string nome2;
        cout << "Scrivere il nome del file (es: nomefile.svg)" << endl;
        cin >> nome2;
        bool t2 = nats_write_file(s2, nome2);

        std::cout << t2 << endl;
    }    

}
