#ifndef SUITCASE_H
#define SUITCASE_H

#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;


/**
 * A struct representing the body of suitcase.
**/
struct NatsBody {
    float w_body;                       //width
    float h_body;                       //heigth
    float xas_body, yas_body;           //high left point
    float xad_body, yad_body;           //high right point
};

/**
 * A struct representing a wheel of suitcase 
**/
struct NatsWheel {
    float r_wheel;                      //radius
    float x_wheel, y_wheel;             //center
    float xs_wheel, ys_wheel;           //extreme left point
    float xd_wheel, yd_wheel;           //extreme right point
    float xa_wheel, ya_wheel;           //extreme high point
};

/**
 * A struct representing the handle of suitcase 
**/
struct NatsHandle {
    float w_handle;                     //width
    float h_handle;                     //heigth
    float xas_handle, yas_handle;       //high left point
    float xad_handle, yad_handle;       //high right point
    float xbs_handle, ybs_handle;       //low left point
    float xbd_handle, ybd_handle;       //low right point
};

/**
 * A struct representing the pole of suitcase 
**/
struct NatsPole {
    float w_pole;                       //width
    float h_pole;                       //heigth
    float xas_pole, yas_pole;           //high left point
};

/**
 * A struct representing suitcase with all its parts
**/
struct NatsSuitcase {
    NatsBody body;
    NatsWheel wheelsx;
    NatsWheel wheeldx;
    NatsWheel junction;
    NatsHandle handle;
    NatsPole pole;
    float angle;                        //angle beetwen pole and y-axis
    float x_suitcase, y_suitcase;       //baseline point
    float x_esx, x_edx;                 //extreme x points
    float y_einf, y_esup;               //extreme y point
};

/**
 * Inizialize Suitcase struct
**/
NatsSuitcase* nats_init();

/**
 * Set parameters of suitcase
**/
void nats_setparameters(float x, float y, float wb, float hb, float hp, float wh, float rw, float angle, NatsSuitcase* Suitcase);

/**
 * Set extreme points of suitcase
**/
void nats_setextreme(NatsSuitcase* Suitcase);

/**
 * Control if suitcase's position is in the background
 * 
 *  Return int about the type of error:
 *      1 =  extreme left point is out of the file
 *      2 =  extreme right point is out of the file
 *      3 =  extreme high point is out of the file
 *      4 =  extreme low point is out of the file
 *  Return 0 if the position of suitcase is in the limits
**/
int nats_controllposition(NatsSuitcase* Suitcase);

/**
 * Control if suitcase's dimensions respect the constrains
 * 
 *  Return int about the type of error:
 *      1 =  height of the pole is greater than the height of the body
 *      2 =  width of the handle is greater than the width of the body
 *      3 =  width of the pole is greater than the width of the handle
 *      4 =  radius of the wheels is greater than the half of the width of the body
 *  Return 0 if the dimensions of suitcase is in the limits
**/
int nats_controlldimension(NatsSuitcase* Suitcase);


string nats_svg_handle(NatsSuitcase* Suitcase);
string nats_svg_pole(NatsSuitcase* Suitcase);
string nats_svg_gradient();
string nats_svg_body(NatsSuitcase* Suitcase);
string nats_svg_wheelsx(NatsSuitcase* Suitcase);
string nats_svg_wheeldx(NatsSuitcase* Suitcase);
string nats_svg_junction(NatsSuitcase* Suitcase);
string nats_svg_rotation(NatsSuitcase* Suitcase);
string nats_svg(NatsSuitcase* Suitcase);

bool nats_write_file(string svg);


#endif
