#include <iostream>
#include <string.h>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <sstream>
#include "suitcase.h"

using namespace std;

NatsSuitcase* nats_init(){
    NatsSuitcase* device = new NatsSuitcase;
    return device;
}

void nats_setparameters(float x, float y, float wb, float hb, float hp, float wh, float rw, float angle, NatsSuitcase* Suitcase){
    
    Suitcase->x_suitcase = x;
    Suitcase->y_suitcase = y;
    Suitcase->angle = angle;

    Suitcase->body.w_body = wb;
    Suitcase->body.h_body = hb;
    Suitcase->body.xas_body = x - (wb/2);
    Suitcase->body.yas_body = y -rw- hb;
    Suitcase->body.xad_body = x + (wb/2);
    Suitcase->body.yad_body = y -rw- hb;


    Suitcase->pole.w_pole = hp/5;           //default
    Suitcase->pole.h_pole = hp;
    Suitcase->pole.xas_pole = x + (wb/2) - (hp/10) + (hp * sin(angle));
    Suitcase->pole.yas_pole = y - rw - hb - hp + (hp * (1 - cos(angle)));

    Suitcase->handle.w_handle = wh;
    Suitcase->handle.h_handle = hp/5;       //default
    Suitcase->handle.xas_handle = x + wb/2 - wh/2 + ((hp + wh) * sin(angle));
    Suitcase->handle.yas_handle = y - rw - hb - hp - hp/5 + ((hp + wh) * (1 - cos(angle)));
    Suitcase->handle.xad_handle = x + wb/2 + wh/2 + ((hp + wh) * sin(angle));
    Suitcase->handle.yad_handle = y - rw - hb - hp - hp/5 + ((hp + wh) * (1 - cos(angle)));
    Suitcase->handle.xbs_handle = x + wb/2 - wh/2 + ((hp) * sin(angle));
    Suitcase->handle.ybs_handle = y - rw - hb - hp + ((hp) * (1 - cos(angle)));
    Suitcase->handle.xbd_handle = x + wb/2 + wh/2 + ((hp) * sin(angle));
    Suitcase->handle.ybd_handle = y - rw - hb - hp + ((hp) * (1 - cos(angle)));

    Suitcase->wheelsx.r_wheel = rw;
    Suitcase->wheelsx.x_wheel = x - wb/2;
    Suitcase->wheelsx.y_wheel = y - rw;
    Suitcase->wheelsx.xs_wheel = x - wb/2 - rw;

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
            edx = Suitcase->junction.ya_wheel;
        }
    }else{
        esup = Suitcase->handle.yas_handle;
        if(esup < Suitcase->junction.ya_wheel){
            
        }else{
            edx = Suitcase->junction.ya_wheel;
        }
    }

    //Extreme low point beetween extreme low point of wheels and extreme low poin of handle
    if(Suitcase->y_suitcase < Suitcase->handle.yad_handle){
        esx = Suitcase->handle.yad_handle;
    }else{
        esx = Suitcase->y_suitcase;
    }

    Suitcase->x_edx = edx;
    Suitcase->x_esx = esx;
    Suitcase->y_esup = esup;
    Suitcase->y_einf = einf;
}



int nats_controllposition(NatsSuitcase* Suitcase){
    int i = 0;
    if(Suitcase->x_esx < 0){
        return i = 1;
    }else{
        if(Suitcase->x_edx > 800){
            return i = 2;
        }else{
            if(Suitcase->y_esup < 0){
                return i = 3;
            }else{
                if(Suitcase->y_einf > 600){
                    return i = 4;
                }else{
                    return i = 0;
                }
            }
        }
    }
}



int nats_controlldimension(NatsSuitcase* Suitcase){
    int i = 0;

    if(Suitcase->pole.h_pole > Suitcase->body.h_body){
        return i = 1;
    }else{
        if(Suitcase->handle.w_handle > Suitcase->body.w_body){
            return i = 2;
        }else{
            if(Suitcase->pole.w_pole > Suitcase->handle.w_handle){
                return i = 3;
            }else{
                if(Suitcase->wheelsx.r_wheel > (Suitcase->body.w_body / 2)){
                    return i = 4;
                }else{
                    return i = 0;
                }
            }
        }
    }
}



string nats_svg_handle(NatsSuitcase* Suitcase){


    float xas_norotation = (Suitcase->handle.xas_handle) - ((Suitcase->pole.h_pole + Suitcase->handle.w_handle) * sin(Suitcase->angle));

    float yas_norotation = (Suitcase->handle.yas_handle) - ((Suitcase->pole.h_pole + Suitcase->handle.w_handle) * (1 - cos(Suitcase->angle)));

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


    float xas_norotation = (Suitcase->pole.xas_pole) - ((Suitcase->pole.h_pole)*sin(Suitcase->angle));

    float yas_norotation = (Suitcase->pole.yas_pole) - ((Suitcase->pole.h_pole)*(1 - cos(Suitcase->angle)));

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
    rotation += ")\">";
    return rotation;
}

string nats_svg(NatsSuitcase* Suitcase){
    string svg;
    svg += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    svg += "\n<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">\n";
    svg += nats_svg_rotation(Suitcase);
    svg += nats_svg_handle(Suitcase);
    svg += "  \n";
    svg += nats_svg_pole(Suitcase);
    svg += "  </g>";                    //end rotation
    svg += "  \n";
    svg += nats_svg_gradient();
    svg += nats_svg_body(Suitcase);
    svg += "  \n";
    svg += nats_svg_wheelsx(Suitcase);
    svg += "  \n";
    svg += nats_svg_wheeldx(Suitcase);
    svg += "\n";
    svg += nats_svg_junction(Suitcase);
    svg += "\n</svg>";
    return svg;

}

bool nats_write_file(string svg){

    if(svg != ""){
        string nome;

        cout << "Scrivere il nome del file (es: nomefile.svg)" << endl;
        cin >> nome;

        // Create and open a text file
        ofstream MyFile(nome);

        string string_to_write = svg;

        // Write to the file
        MyFile << string_to_write;

        // Close the file
        MyFile.close();

        return false;
    }else{
        return true;
    }

}
