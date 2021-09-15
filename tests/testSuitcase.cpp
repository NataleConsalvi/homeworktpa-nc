#include "catch2/catch2.hpp"
#include "suitcase.h"


//Test 1: nats_init_param
TEST_CASE("Test 1: nats_init_param (it should initialize a new set of parameters)", "[suitcase]") {

    NatsParameters* param = nats_init_param();

    REQUIRE(param != NULL);

    delete param;
}

//Test 2: nats_init_device
TEST_CASE("Test 2: nats_init_device (it should initialize a new device)", "[suitcase]") {

    NatsSuitcase* device = nats_init_device();

    REQUIRE(device != NULL);

    delete device;
}

//Test 3: nats_control_parameters
TEST_CASE("Test 3: nats_control_parameters (it should return a int for each type of error in a set of parameters)"){

    NatsParameters* param = nats_init_param();

    param->x = -3;

    param->y = 500;
    param->wb = 200;
    param->hb = 250;
    param->hp = 100;
    param->wh = 40;
    param->rw = 20;
    param->angle= 45;

    int i = nats_controlparameters(param);

    REQUIRE(i == 2); //The wrong parameter is position x that it is negative!

    param->x = 400;
    param-> hb = 0;

    int j = nats_controlparameters(param);

    REQUIRE(j == 5); //The wrong parameter is the height of the body that it is null!

    param->hb = 100;

    int a = nats_controlparameters(param);

    REQUIRE(a == 0); //There are not wrong parameters!

    delete param;

}

//Test 4: nats_set_parameters
TEST_CASE("Test 4: nats_set_parameters (it should set all device's parameters from struct parameters)", "[suitcase]") {

    NatsParameters* param = nats_init_param();
    NatsSuitcase* device = nats_init_device();

    param->x = 400;
    param->y = 500;
    param->wb = 200;
    param->hb = 250;
    param->hp = 100;
    param->wh = 40;
    param->rw = 20;
    param->angle= 45;

    nats_setparameters(param, device);

    REQUIRE(device->angle == 45);                                   //Correct passage of values
    REQUIRE(device->body.w_body == 200);
    REQUIRE(device->wheeldx.r_wheel == 20);

    REQUIRE(device->body.xas_body == (400 - 200/2));                //Calculation succesfull
    REQUIRE(device->junction.x_wheel == device->body.xad_body);     //Correct position of the center of the junction (in the extreme high left point of the body)
    REQUIRE(device->wheelsx.x_wheel == (400 - 200/2));              //Correct position of the center of the left wheel (in the extreme low left point of the body)

    REQUIRE((device->pole.xas_pole - 563.63961) <= 0.0001);         //Calculation with trigonometric function corrected with an approximation of 0.01%
    REQUIRE((device->handle.xas_handle -570.71068) <= 0.0001);


    delete param;
    delete device;

}


//Test 5: nats_setextreme
TEST_CASE("Test 5.1: nats_setextreme (it should set the extreme points of the suitcase in various situations)", "[suitcase]") {

    NatsParameters* param = nats_init_param();
    NatsSuitcase* device = nats_init_device();

    //Case 1: the extreme high point is the high LEFT point of the handle
    param->x = 400;
    param->y = 500;
    param->wb = 200;
    param->hb = 250;
    param->hp = 100;
    param->wh = 40;
    param->rw = 20;
    param->angle= 45;

    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE((device->y_esup - device->handle.yas_handle) <= 0.0001);
    REQUIRE((device->y_esup - 145.14719) <= 0.0001);
    

    //Case 2: the extreme high point is the high RIGHT point of the handle
    param->angle = 320;

    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE((device->y_esup - device->handle.yad_handle) <= 0.0001);
    REQUIRE((device->y_esup - 138.07467) <= 0.0001);

    delete param;
    delete device;
}


   /* test
    string total = nats_read_from_file();
    int a = 0;
    float b = nats_parse(total, "rotate(", ", ", a);
    cout << b << endl;
   */
