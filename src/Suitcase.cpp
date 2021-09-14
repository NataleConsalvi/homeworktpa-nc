#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <sstream>
#include "suitcase.h"



#define _USE_MATH_DEFINES

using namespace std;

NatsParameters* nats_init_param(){
    NatsParameters* param = new NatsParameters;
    return param;
}

NatsSuitcase* nats_init_device(){
    NatsSuitcase* device = new NatsSuitcase;
    return device;
}

int nats_controlparameters(NatsParameters* param){
    int i = 0;
    if(param->angle < 0 || param->angle>360){
        //nats_handling_parameters(1, param);
        return i = 1;
    }
    if(param->x < 0){
        return i = 2;
    }
    if(param->y < 0){
        return i = 3;
    }
    if(param->wb <= 0){
        return i = 4;
    }
    if(param->hb <= 0){
        return i = 5;
    }
    if(param->hp <= 0){
        return i = 6;
    }
    if(param->wh <= 0){
        return i = 7;
    }
    if(param->rw <= 0){
        return i = 8;
    }
    return i;
}


void nats_setparameters(NatsParameters* param, NatsSuitcase* Suitcase){
    
    float x = param->x;
    float y = param->y;
    float wb = param->wb;
    float hb = param->hb;
    float hp = param->hp;
    float wh = param->wh;
    float rw = param->rw;
    float angle = param->angle;

    Suitcase->x_suitcase = x;
    Suitcase->y_suitcase = y;
    Suitcase->angle = angle;
    float anglerad = angle * M_PI/180;

    Suitcase->body.w_body = wb;
    Suitcase->body.h_body = hb;
    Suitcase->body.xas_body = x - (wb/2);
    Suitcase->body.yas_body = y -rw- hb;
    Suitcase->body.xad_body = x + (wb/2);
    Suitcase->body.yad_body = y -rw- hb;

    Suitcase->pole.w_pole = hp/5;           //default
    Suitcase->pole.h_pole = hp;
    Suitcase->pole.xas_pole = x + (wb/2) - (hp/10) + (hp * sin(anglerad));
    Suitcase->pole.yas_pole = y - rw - hb - hp + (hp * (1 - cos(anglerad)));

    Suitcase->handle.w_handle = wh;
    Suitcase->handle.h_handle = hp/5;       //default
    Suitcase->handle.xas_handle = x + wb/2 - wh/2 + ((hp + wh) * sin(anglerad));
    Suitcase->handle.yas_handle = y - rw - hb - hp - hp/5 + ((hp + wh) * (1 - cos(anglerad)));
    Suitcase->handle.xad_handle = x + wb/2 + wh/2 + ((hp + wh) * sin(anglerad));
    Suitcase->handle.yad_handle = y - rw - hb - hp - hp/5 + ((hp + wh) * (1 - cos(anglerad)));
    Suitcase->handle.xbs_handle = x + wb/2 - wh/2 + ((hp) * sin(anglerad));
    Suitcase->handle.ybs_handle = y - rw - hb - hp + ((hp) * (1 - cos(anglerad)));
    Suitcase->handle.xbd_handle = x + wb/2 + wh/2 + ((hp) * sin(anglerad));
    Suitcase->handle.ybd_handle = y - rw - hb - hp + ((hp) * (1 - cos(anglerad)));

    Suitcase->wheelsx.r_wheel = rw;
    Suitcase->wheelsx.x_wheel = x - wb/2;
    Suitcase->wheelsx.y_wheel = y - rw;
    Suitcase->wheelsx.xs_wheel = x - wb/2 - rw;
    Suitcase->wheelsx.ya_wheel = y - rw;

    Suitcase->wheeldx.r_wheel = rw;
    Suitcase->wheeldx.x_wheel = x + wb/2;
    Suitcase->wheeldx.y_wheel = y - rw;
    Suitcase->wheeldx.xd_wheel = x + wb/2 + rw;

    Suitcase->junction.r_wheel = hp/8;
    Suitcase->junction.x_wheel = x + wb/2;
    Suitcase->junction.y_wheel = y - rw - hb;
    Suitcase->junction.ya_wheel = y - rw - hb - hp/8;

}

void nats_setextreme(NatsSuitcase* Suitcase){

    float edx, esx, esup, einf;

    //Extreme left point beetween extreme left point of handle and extreme left poin of left wheel
    if(Suitcase->wheelsx.xs_wheel < Suitcase->handle.xas_handle){
        esx = Suitcase->wheelsx.xs_wheel;
    }else{
        esx = Suitcase->handle.xas_handle;
    }

    //Extreme right point beetween extreme right point of junction, extreme right point of handle and extreme right poin of rigth wheel
    if(Suitcase->junction.xd_wheel > Suitcase->wheeldx.xd_wheel){
        edx = Suitcase->junction.xd_wheel;
        if(edx > Suitcase->handle.xad_handle){
            
        }else{
            edx = Suitcase->handle.xad_handle;
        }
    }else{
        edx = Suitcase->wheeldx.xd_wheel;
        if(edx > Suitcase->handle.xad_handle){
            
        }else{
            edx = Suitcase->handle.xad_handle;
        }
    }

    //Extreme high point beetween extreme hight point of junction, extreme high point of handle (left or right)
    if(Suitcase->handle.yad_handle < Suitcase->handle.yas_handle){
        esup = Suitcase->handle.yad_handle;
        if(esup < Suitcase->junction.ya_wheel){
            
        }else{
            esup = Suitcase->junction.ya_wheel;
        }
    }else{
        esup = Suitcase->handle.yas_handle;
        if(esup < Suitcase->junction.ya_wheel){
            
        }else{
            esup = Suitcase->junction.ya_wheel;
        }
    }

    //Extreme low point beetween extreme low point of wheels and extreme low poin of handle
    if(Suitcase->y_suitcase < Suitcase->handle.yad_handle){
        einf = Suitcase->handle.yad_handle;
    }else{
        einf = Suitcase->y_suitcase;
    }

    Suitcase->x_edx = edx;
    Suitcase->x_esx = esx;
    Suitcase->y_esup = esup;
    Suitcase->y_einf = einf;
}


int nats_controlposition(NatsSuitcase* Suitcase){
    int i = 0;
    if(Suitcase->x_esx < 0){
        return i = 9;
    }else{
        if(Suitcase->x_edx > 800){
            return i = 10;
        }else{
            if(Suitcase->y_esup < 0){
                return i = 11;
            }else{
                if(Suitcase->y_einf > 600){
                    return i = 12;
                }else{
                    return i = 0;
                }
            }
        }
    }
}

int nats_controldimension(NatsSuitcase* Suitcase){
    int i = 0;

    if((Suitcase->pole.h_pole + Suitcase->handle.h_handle) > Suitcase->body.h_body){
        return i = 13;
    }else{
        if(Suitcase->handle.w_handle > Suitcase->body.w_body){
            return i = 14;
        }else{
            if(Suitcase->pole.w_pole > Suitcase->handle.w_handle){
                return i = 15;
            }else{
                if(Suitcase->wheelsx.r_wheel > (Suitcase->body.w_body / 2)){
                    return i = 16;
                }else{
                    return i = 0;
                }
            }
        }
    }
}

int nats_controlhandle(NatsSuitcase* Suitcase){
    int i = 0;
    if(Suitcase->angle <= 180){

        if(Suitcase->handle.ybd_handle > Suitcase->wheeldx.ya_wheel){
            if(Suitcase->handle.xbd_handle < Suitcase->wheeldx.xd_wheel){
                return i = 17;
            }
        }else{
            if(Suitcase->handle.xbd_handle < Suitcase->body.xad_body){
                return i = 18;
            }
            if(Suitcase->handle.xad_handle < Suitcase->wheeldx.xd_wheel){
                return i = 17;
            }
        }

    }else{
        if(Suitcase->handle.ybs_handle > Suitcase->body.yad_body){
            return i = 18;
        }

    }
    return i = 0;
}


string nats_svg_handle(NatsSuitcase* Suitcase){
    float xas_norotation = (Suitcase->handle.xas_handle) - ((Suitcase->pole.h_pole + Suitcase->handle.w_handle) * sin((Suitcase->angle)*M_PI/180));
    float yas_norotation = (Suitcase->handle.yas_handle) - ((Suitcase->pole.h_pole + Suitcase->handle.w_handle) * (1 - cos((Suitcase->angle)*M_PI/180)));
    string handle;
    handle += "  <rect  x=\"";
    handle += to_string(xas_norotation);
    handle += "\" y=\"";
    handle += to_string(yas_norotation);
    handle += "\" width=\"";
    handle += to_string(Suitcase->handle.w_handle);
    handle +="\" height=\"";
    handle += to_string(Suitcase->handle.h_handle);
    handle += "\" style=\"fill:rgb(200,200,0);stroke-width:3;stroke:rgb(0,0,0)\" />  \n";
    return handle;
}

string nats_svg_pole(NatsSuitcase* Suitcase){
    float xas_norotation = (Suitcase->pole.xas_pole) - ((Suitcase->pole.h_pole)*sin((Suitcase->angle)*M_PI/180));
    float yas_norotation = (Suitcase->pole.yas_pole) - ((Suitcase->pole.h_pole)*(1 - cos((Suitcase->angle)*M_PI/180)));
    string pole;
    pole += "  <rect  x=\"";
    pole += to_string(xas_norotation);
    pole += "\" y=\"";
    pole += to_string(yas_norotation);
    pole += "\" width=\"";
    pole += to_string(Suitcase->pole.w_pole);
    pole +="\" height=\"";
    pole += to_string(Suitcase->pole.h_pole);
    pole += "\" style=\"fill:rgb(200,200,200);stroke-width:3;stroke:rgb(0,0,0)\" />    \n";
    return pole;
}

string nats_svg_gradient(){
    string gradient;
    gradient += "  <defs>\n    <linearGradient id=\"grad1\" x1=\"0%\" y1=\"0%\" x2=\"0%\" y2=\"100%\">\n      <stop offset=\"0%\" style=\"stop-color:rgb(255,0,0);stop-opacity:1\" />\n      <stop offset=\"100%\" style=\"stop-color:rgb(255,255,0);stop-opacity:1\" />\n    </linearGradient>\n  </defs>\n";
    return gradient;
}

string nats_svg_body(NatsSuitcase* Suitcase){
    string body;
    body += "  <rect  x=\"";
    body += to_string(Suitcase->body.xas_body);
    body += "\" y=\"";
    body += to_string(Suitcase->body.yas_body);
    body += "\" width=\"";
    body += to_string(Suitcase->body.w_body);
    body +="\" height=\"";
    body += to_string(Suitcase->body.h_body);
    body += "\" style=\"fill:url(#grad1);stroke-width:3;stroke:rgb(0,0,0)\" />    \n";
    return body;
}

string nats_svg_wheelsx(NatsSuitcase* Suitcase){
    string wheel;
    wheel += "  <circle cx=\"";
    wheel += to_string(Suitcase->wheelsx.x_wheel);
    wheel += "\" cy=\"";
    wheel += to_string(Suitcase->wheelsx.y_wheel);
    wheel += "\" r=\"";
    wheel += to_string(Suitcase->wheelsx.r_wheel);
    wheel += "\" stroke=\"black\" stroke-width=\"3\" fill=\"grey\" />    \n";
    return wheel;
}

string nats_svg_wheeldx(NatsSuitcase* Suitcase){
    string wheel;
    wheel += "  <circle cx=\"";
    wheel += to_string(Suitcase->wheeldx.x_wheel);
    wheel += "\" cy=\"";
    wheel += to_string(Suitcase->wheeldx.y_wheel);
    wheel += "\" r=\"";
    wheel += to_string(Suitcase->wheeldx.r_wheel);
    wheel += "\" stroke=\"black\" stroke-width=\"3\" fill=\"grey\" />    \n";
    return wheel;
}

string nats_svg_junction(NatsSuitcase* Suitcase){
    string junction;
    junction += "  <circle cx=\"";
    junction += to_string(Suitcase->junction.x_wheel);
    junction += "\" cy=\"";
    junction += to_string(Suitcase->junction.y_wheel);
    junction += "\" r=\"";
    junction += to_string(Suitcase->junction.r_wheel);
    junction += "\" stroke=\"black\" stroke-width=\"3\" fill=\"grey\" />    \n";
    return junction;
}

string nats_svg_rotation(NatsSuitcase* Suitcase){
    string rotation;
    rotation += "  \n";
    rotation += "  <g transform = \"rotate(";
    rotation += to_string(Suitcase->angle);
    rotation += ", ";
    rotation += to_string(Suitcase->body.xad_body);
    rotation += ", ";
    rotation += to_string(Suitcase->body.yad_body);
    rotation += ")\">\n";
    return rotation;
}

string nats_svg_q_handle(NatsSuitcase* Suitcase){
    //text + dimension of handle
        float xas_norotation = (Suitcase->handle.xas_handle) - ((Suitcase->pole.h_pole + Suitcase->handle.w_handle) * sin((Suitcase->angle)*M_PI/180));
        float yas_norotation = (Suitcase->handle.yas_handle) - ((Suitcase->pole.h_pole + Suitcase->handle.w_handle) * (1 - cos((Suitcase->angle)*M_PI/180)));

        string testo;
        testo += "\n  <text  x=\"";
        testo += to_string(xas_norotation + (Suitcase->handle.w_handle)/2);
        testo += "\" y=\"";
        testo += to_string(yas_norotation - 30);
        testo += "\" fill='black' dominant-baseline='middle' text-anchor='middle'>";

        string prova = to_string(Suitcase->handle.w_handle);
        prova.resize(5);

        testo += prova;
        testo += "</text>\n";

        testo += "  <rect  x=\"";
        testo += to_string(xas_norotation);
        testo += "\" y=\"";
        testo += to_string(yas_norotation - 20);
        testo += "\" width=\"";
        testo += to_string(Suitcase->handle.w_handle);
        testo +="\" height=\"";
        testo += to_string(3);
        testo += "\" style=\"stroke-width:0;stroke:rgb(200,200,200)\" />  \n";

    return testo;

}

string nats_svg_q_pole(NatsSuitcase* Suitcase){
    //text + dimension of pole
        string testo;
        float xas_norotation = (Suitcase->pole.xas_pole) - ((Suitcase->pole.h_pole)*sin((Suitcase->angle)*M_PI/180));
        float yas_norotation = (Suitcase->pole.yas_pole) - ((Suitcase->pole.h_pole)*(1 - cos((Suitcase->angle)*M_PI/180)));
    if(Suitcase->angle >= 270){
        
        testo += "\n  <text  x=\"";
        testo += to_string(xas_norotation + Suitcase->pole.w_pole  + 30);
        testo += "\" y=\"";
        testo += to_string(yas_norotation + Suitcase->pole.h_pole/2);
        testo += "\" fill='black' dominant-baseline='middle' text-anchor='middle'";
        testo += " transform =\"rotate(90,";
        testo += to_string(xas_norotation + Suitcase->pole.w_pole  + 30);
        testo += ",";
        testo += to_string(yas_norotation + Suitcase->pole.h_pole/2);
        testo += ")\">";

        string prova = to_string(Suitcase->pole.h_pole);
        prova.resize(5);

        testo += prova;
        testo += "</text>\n";

        testo += "  <rect  x=\"";
        testo += to_string(xas_norotation + Suitcase->pole.w_pole  + 20);
        testo += "\" y=\"";
        testo += to_string(yas_norotation);
        testo += "\" width=\"";
        testo += to_string(3);
        testo +="\" height=\"";
        testo += to_string(Suitcase->pole.h_pole);
        testo += "\" style=\"stroke-width:0;stroke:rgb(200,200,200)\" />  \n";
    }else{

        testo += "\n  <text  x=\"";
        testo += to_string(xas_norotation  - 30);
        testo += "\" y=\"";
        testo += to_string(yas_norotation + Suitcase->pole.h_pole/2);
        testo += "\" fill='black' dominant-baseline='middle' text-anchor='middle'";
        testo += " transform =\"rotate(270,";
        testo += to_string(xas_norotation  - 30);
        testo += ",";
        testo += to_string(yas_norotation + Suitcase->pole.h_pole/2);
        testo += ")\">";

        string prova = to_string(Suitcase->pole.h_pole);
        prova.resize(5);

        testo += prova;
        testo += "</text>\n";

        testo += "  <rect  x=\"";
        testo += to_string(xas_norotation -20);
        testo += "\" y=\"";
        testo += to_string(yas_norotation);
        testo += "\" width=\"";
        testo += to_string(3);
        testo +="\" height=\"";
        testo += to_string(Suitcase->pole.h_pole);
        testo += "\" style=\"stroke-width:0;stroke:rgb(200,200,200)\" />  \n";

    }
    return testo;

}

string nats_svg_q_body(NatsSuitcase* Suitcase){

    //text + dimension of body's heigth
        string testo;
        testo += "\n  <text  x=\"";
        testo += to_string(Suitcase->body.xas_body  - Suitcase->wheelsx.r_wheel - 20);
        testo += "\" y=\"";
        testo += to_string(Suitcase->body.yas_body + Suitcase->body.h_body/2);
        testo += "\" fill='black' dominant-baseline='middle' text-anchor='middle'";
        testo += " transform =\"rotate(270,";
        testo += to_string(Suitcase->body.xas_body  - Suitcase->wheelsx.r_wheel - 20);
        testo += ",";
        testo += to_string(Suitcase->body.yas_body + Suitcase->body.h_body/2);
        testo += ")\">";

        string prova = to_string(Suitcase->body.h_body);
        prova.resize(5);

        testo += prova;
        testo += "</text>\n";

        testo += "  <rect  x=\"";
        testo += to_string(Suitcase->body.xas_body  - Suitcase->wheelsx.r_wheel - 10);
        testo += "\" y=\"";
        testo += to_string(Suitcase->body.yas_body);
        testo += "\" width=\"";
        testo += to_string(3);
        testo +="\" height=\"";
        testo += to_string(Suitcase->body.h_body - 1);
        testo += "\" style=\"stroke-width:0;stroke:rgb(200,200,200)\" />  \n";

    //text + dimension of body's width
        testo += "  <g transform = \"rotate(270,";
        testo += to_string(Suitcase->body.xas_body);
        testo += ",";
        testo += to_string(Suitcase->y_suitcase + 10);
        testo += ")\" >";

        testo += "\n  <text  x=\"";
        testo += to_string(Suitcase->body.xas_body - 10);
        testo += "\" y=\"";
        testo += to_string(Suitcase->y_suitcase + Suitcase->body.w_body/2 + 10);
        testo += "\" fill='black' dominant-baseline='middle' text-anchor='middle'";
        testo += " transform =\"rotate(90,";
        testo += to_string(Suitcase->body.xas_body - 10);
        testo += ",";
        testo += to_string(Suitcase->y_suitcase + Suitcase->body.w_body/2 + 10);
        testo += ")\">";

        string prova1 = to_string(Suitcase->body.w_body);
        prova1.resize(5);

        testo += prova1;
        testo += "</text>\n";

        testo += "  <rect  x=\"";
        testo += to_string(Suitcase->body.xas_body);
        testo += "\" y=\"";
        testo += to_string(Suitcase->y_suitcase + 10);
        testo += "\" width=\"";
        testo += to_string(3);
        testo +="\" height=\"";
        testo += to_string(Suitcase->body.w_body);
        testo += "\" style=\"stroke-width:0;stroke:rgb(200,200,200)\" />  \n";
        testo += "  </g>";  

    return testo;
}

string nats_svg_q_radius(NatsSuitcase* Suitcase){

    //text + dimension of wheel's radius
        string testo;
        testo += "\n  <text  x=\"";
        testo += to_string(Suitcase->body.xas_body  - Suitcase->wheelsx.r_wheel - 20);
        testo += "\" y=\"";
        testo += to_string(Suitcase->y_suitcase - Suitcase->wheelsx.r_wheel/2);
        testo += "\" fill='black' dominant-baseline='middle' text-anchor='middle'";
        testo += " transform =\"rotate(270,";
        testo += to_string(Suitcase->body.xas_body  - Suitcase->wheelsx.r_wheel - 20);
        testo += ",";
        testo += to_string(Suitcase->y_suitcase - Suitcase->wheelsx.r_wheel/2);
        testo += ")\">";

        string prova = to_string(Suitcase->wheelsx.r_wheel);
        prova.resize(5);

        testo += prova;
        testo += "</text>\n";

        testo += "  <rect  x=\"";
        testo += to_string(Suitcase->body.xas_body  - Suitcase->wheelsx.r_wheel - 10);
        testo += "\" y=\"";
        testo += to_string(Suitcase->wheelsx.ya_wheel + 1);
        testo += "\" width=\"";
        testo += to_string(3);
        testo +="\" height=\"";
        testo += to_string(Suitcase->wheelsx.r_wheel - 1);
        testo += "\" style=\"stroke-width:0;stroke:rgb(200,200,200)\" />  \n";
    return testo;
}


string nats_to_svg(NatsSuitcase* Suitcase, char c){
    string svg;
    svg += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";                    //header
    svg += "\n<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">\n";

    svg += nats_svg_rotation(Suitcase);
    svg += "  \n";
    svg += nats_svg_handle(Suitcase);
    svg += "  \n";
    svg += nats_svg_pole(Suitcase);
    svg += "  </g>";                                                                            //end rotation
    svg += "  \n";
    svg += nats_svg_gradient();
    svg += "  \n";
    svg += nats_svg_body(Suitcase);
    svg += "  \n";
    svg += nats_svg_wheelsx(Suitcase);
    svg += "  \n";
    svg += nats_svg_wheeldx(Suitcase);
    svg += "\n";
    svg += nats_svg_junction(Suitcase);
    svg += "  \n";
    svg += "  \n";
    
    if(c == 'Y'){                                                                               //aggiunta quotatura
        svg += nats_svg_rotation(Suitcase);
        svg += nats_svg_q_handle(Suitcase);
        svg += nats_svg_q_pole(Suitcase);
        svg += "  </g>";
        svg += nats_svg_q_body(Suitcase);
        svg += "  \n";
        svg += nats_svg_q_radius(Suitcase);        
    }
    
    svg += "\n</svg>";                                                                          //end

    return svg;

}

bool nats_write_file(string svg, string name){

    if(svg != ""){
        ofstream MyFile(name);                                              // Create and open a text file
        string string_to_write = svg;
        MyFile << string_to_write;                                          // Write to the file
        MyFile.close();                                                     // Close the file
        return false;
    }else{
        return true;
    }

}


float nats_parse(string totale, string parse, string end, int &start_index){

    string parametro;
    size_t position = totale.find(parse, start_index);                  //position of string "parse"
                                                                        //if "parse" is not found in total return npos
    size_t end_parse = position + parse.length();
    size_t position_end = totale.find(end, end_parse);

    parametro = totale.substr(end_parse, position_end);                 //substr take the string between end_parse and position_end

    start_index = position_end + end.length();

    return stof(parametro);                                             //Parses str interpreting its content as a float
}


void nats_svg_to_param(string totale, NatsParameters* parametri){

    int start_index = 0;

    parametri->angle = nats_parse(totale, "rotate(", ", ", start_index);
    parametri->wh = nats_parse(totale, "width=\"", "\" height", start_index);
    parametri->hp = nats_parse(totale, "height=\"", "\" style", start_index);

    float xas_body = nats_parse(totale, "<rect  x=\"", "\" ", start_index);
    float yas_body = nats_parse(totale, "y=\"", "\" ", start_index);

    parametri->wb = nats_parse(totale, "width=\"", "\" ", start_index);
    parametri->hb = nats_parse(totale, "height=\"", "\" ", start_index);
    parametri->rw = nats_parse(totale, "\" r=\"", "\"stoke=", start_index);
    parametri->x = xas_body + (parametri->wb) / 2;
    parametri->y = yas_body + (parametri->hb) + (parametri->rw);

}
