#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

#include "suitcase.h"

using namespace std;

/**
 * Function that re set the wrong parameters (the parameter that not respect the constraints)
 *      9 =  extreme left point is out of the file
 *      10 =  extreme right point is out of the file
 *      11 =  extreme high point is out of the file
 *      12 =  extreme low point is out of the file
 *      13 =  height of the pole is greater than the height of the body
 *      14 =  width of the handle is greater than the width of the body
 *      15 =  width of the pole is greater than the width of the handle
 *      16 =  radius of the wheels is greater than the half of the width of the body
 *      17 =  handle touch the wheel
 *      18 =  handle touch the body
**/
void nats_re_set_parameters(int i, NatsParameters* param, NatsSuitcase* suitcase){
    switch(i){
        case 0:

            break;
        case 9:
            int i1;
            do{
                cout << "Re-enter position x to move the suitcase right (x1 > " << param->x << ")" << endl;
                cout << "   x1 = ";
                cin >> param->x;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i1 = nats_control_suitcase(suitcase);
            }while(i1 == 9);
            break;
        case 10:
            int i2;
            do{
                cout << "Re-enter position x to move the suitcase left (x1 < " << param->x << ")" << endl;
                cout << "   x1 = ";
                cin >> param->x;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i2 = nats_control_suitcase(suitcase);
            }while(i2 == 10);
            break;
        case 11:
            int i3;
            do{
                cout << "Re-enter position y to move the suitcase down (y1 > " << param->y << ")" << endl;
                cout << "   y1 = ";
                cin >> param->y;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i3 = nats_control_suitcase(suitcase);
            }while(i3 == 11);
            break;
        case 12:
            int i4;
            do{
                cout << "Re-enter position y to move the suitcase up (y1 < " << param->x << ")" << endl;
                cout << "   y1 = ";
                cin >> param->y;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i4 = nats_control_suitcase(suitcase);
            }while(i4 == 12);
            break;
        case 13:
            int i5;
            do{
                cout << "Re-enter height of the pole (hp1 < " << param->hb - suitcase->handle.h_handle << ")" << endl;
                cout << "   hp1 = ";
                cin >> param->hp;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i5 = nats_control_suitcase(suitcase);
            }while(i5 == 13);
            break;
        case 14:
            int i6;
            do{
                cout << "Re-enter width of the handle (wh1 < " << param->wb << ")" << endl;
                cout << "   wh1 = ";
                cin >> param->wh;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i6 = nats_control_suitcase(suitcase);
            }while(i6 == 14);
            break;
        case 15:
            int i7;
            do{
                cout << "Re-enter width of the handle (wh1 < " << suitcase->pole.w_pole << ")" << endl;
                cout << "   wh1 = ";
                cin >> param->wh;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i7 = nats_control_suitcase(suitcase);
            }while(i7 == 15);
            break;
        case 16:
            int i8;
            do{
                cout << "Re-enter radious of the wheels (rw1 < " << suitcase->body.w_body/2 << ")" << endl;
                cout << "   rw1 = ";
                cin >> param->rw;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i8 = nats_control_suitcase(suitcase);
            }while(i8 == 16);
            break;
        case 17:
            int i9;
            do{
                cout << "Re-enter angle ( ";
                if(suitcase->angle >= 225){
                    cout << "angle1 > " << suitcase->angle << ")" << endl;
                }else{
                    cout << "0 <= angle1 < " << suitcase->angle << ")" << endl;
                }
                cout << "   angle1 = ";
                cin >> param->angle;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i9 = nats_control_suitcase(suitcase);
            }while(i9 == 17);
            break;
        case 18:
            int i10;
            do{
                cout << "Re-enter angle ( ";
                if(suitcase->angle >= 225){
                    cout << "angle1 > " << suitcase->angle << ")" << endl;
                }else{
                    cout << "0 <= angle1 < " << suitcase->angle << ")" << endl;
                }
                cout << "   angle1 = ";
                cin >> param->angle;
                nats_setparameters(param, suitcase);
                nats_setextreme(suitcase);
                i10 = nats_control_suitcase(suitcase);
            }while(i10 == 18);
            break;
        default:

            break;
    }
}

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
    
    std::cout << "Enter the following parameters:" << endl;
    std::cout << "1) Suitcase's position:" << endl;
    std::cout << "   x = ";
    std::cin >> param->x;
    std::cout << "   y = ";
    std::cin >> param->y;
    std::cout << "2) Body's width:" << endl;
    std::cout << "   wb = ";
    std::cin >> param->wb;
    std::cout << "3) Body's height:" << endl;
    std::cout << "   hb = ";
    std::cin >> param->hb;
    std::cout << "4) Pole's height:" << endl;
    std::cout << "   hp = ";
    std::cin >> param->hp;
    std::cout << "5) Handle's width:" << endl;
    std::cout << "   wh = ";
    std::cin >> param->wh;
    std::cout << "6) Wheel's radious:" << endl;
    std::cout << "   rw = ";
    std::cin >> param->rw;
    std::cout << "7) Angle between body and pole:" << endl;
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

    cout << "Enter file's name to read (remember .svg)" << endl;
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

        nats_enter_parameters(param);
        nats_setparameters(param, device);
        nats_setextreme(device);
        do{
            //nats_setextreme(device);
            i = nats_control_suitcase(device);
            //j = ;
            nats_stamp_error(i);
            nats_re_set_parameters(i, param, device);

        }while(i != 0 && j != 0);

        char quote;
        do{
            cout << "Enter the dimension? [Y = yes || N = no] ";
            cin >> quote;
            if(quote != 'Y' && quote != 'N'){
                cout << "Wrong character!" << endl;
            }

        }while(quote != 'Y' && quote != 'N');

        string s = nats_to_svg(device, quote);
        
        string nome;

        cout << "Write file's name (es: filename.svg)" << endl;
        cin >> nome;

        bool t = nats_write_file(s, nome);

        std::cout << t << endl;

        delete param;
        delete device;

    }else{


        string total = nats_read_from_file();

        NatsParameters* param2 = nats_init_param();

        nats_svg_to_param(total, param2);
        
        NatsSuitcase* device2 = nats_init_device();

        nats_setparameters(param2, device2);

        string s2 = nats_to_svg(device2, 'Y');

        string nome2;
        cout << "Write file's name (es: filename.svg)" << endl;
        cin >> nome2;
        bool t2 = nats_write_file(s2, nome2);

        std::cout << t2 << endl;

        delete param2;
        delete device2;
    }    

}
