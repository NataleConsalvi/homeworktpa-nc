#ifndef SUITCASE_H
#define SUITCASE_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <sstream>

using namespace std;

/**
 * A struct representing parameters to build suitcase
**/
struct NatsParameters {
    float x, y;
    float wb;
    float hb;
    float hp;
    float wh;
    float rw;
    float angle;
};

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
 * Inizialize struct "Parameters"
**/
NatsParameters* nats_init_param();

/**
 * Inizialize struct "Suitcase"
**/
NatsSuitcase* nats_init_device();

/**
 * Return the coordinate x of the point (float "x", float "y") rotated by an angle "angle"
**/
float nats_rotation_x(float x, float y, float angle);
/**
 * Return the coordinate y of the point (float "x", float "y") rotated by an angle "angle"
**/
float nats_rotation_y(float x, float y, float angle);

/**
 * Control if the parameters are positive
 * 
 *  Return int about the type of error:
 *      1 =  angle if out of range [0, 360]
 *      2 =  position x of suitcase is negative or > 800
 *      3 =  position y of suitcase is negative or > 600
 *      4 =  width of the body is null or negative or > 800
 *      5 =  height of the body is null or negative or > 600
 *      6 =  height of the pole is null or negative or > 600
 *      7 =  width of the handle is null or negative or > 800
 *      8 =  radius of the wheels is null or negative or > 600
 *  Return 0 if the parameters is in the range
**/
int nats_controlparameters(NatsParameters* param);


/**
 * Set parameters of struct "Suitcase" from struct "Parameters"
**/
void nats_setparameters(NatsParameters* param, NatsSuitcase* Suitcase);

/**
 * Set extreme points of suitcase
**/
void nats_setextreme(NatsSuitcase* Suitcase);

/**
 * Control if suitcase's position is in the background
 * 
 *  Return int about the type of error:
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
 *  Return 0 if all parts of suitcase is in the limits
**/
int nats_control_suitcase(NatsSuitcase* Suitcase);


/**
 * Functions for the construction of svg files of the various parts:
 *  Handle
 *  Pole
 *  Body
 *  Wheels and junction
**/
string nats_svg_handle(NatsSuitcase* Suitcase);
string nats_svg_pole(NatsSuitcase* Suitcase);
string nats_svg_body(NatsSuitcase* Suitcase);
string nats_svg_wheelsx(NatsSuitcase* Suitcase);
string nats_svg_wheeldx(NatsSuitcase* Suitcase);
string nats_svg_junction(NatsSuitcase* Suitcase);

/**
 * Function for the construction of svg file about the rotation of the group handle + pole
**/
string nats_svg_rotation(NatsSuitcase* Suitcase);

/**
 * Function for the construction of svg file about the color of the body
**/
string nats_svg_gradient();

/**
 * Functions for the construction of svg files of the dimensions and the text of the various parts
**/
string nats_svg_q_handle(NatsSuitcase* Suitcase);
string nats_svg_q_pole(NatsSuitcase* Suitcase);
string nats_svg_q_body(NatsSuitcase* Suitcase);
string nats_svg_q_radius(NatsSuitcase* Suitcase);

/**
 * Function for the construction of complete svg file with header, end and the various part of the suitcase
**/
string nats_to_svg(NatsSuitcase* Suitcase, char c);


/**
 * Function that create and save a file call "name" with svg string
**/
bool nats_write_file(string svg, string name);


/**
 * Function that parse string "totale" to search string "parse" from "start_index" to string "end"
 *  Return float = number between string "parse" and string "end"
**/
float nats_parse(string totale, string parse, string end, int &start_index);

/**
 * Function that parse string "totale" to take parameters from svg file
**/
void nats_svg_to_param(string totale, NatsParameters* parametri);


#endif
