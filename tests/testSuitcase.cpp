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


//Test 5.1: nats_setextreme (extreme high point)
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


    //Case 3: the extreme high point is the high point of the junction
    param->angle = 160;
    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE(device->y_esup - device->junction.ya_wheel <= 0.0001);
    REQUIRE(device->y_esup - 217.5 <= 0.0001);

    delete param;
    delete device;
}

//Test 5.2: nats_setextreme (extreme low point)
TEST_CASE("Test 5.2: nats_setextreme (it should set the extreme points of the suitcase in various situations)", "[suitcase]") {

    NatsParameters* param = nats_init_param();
    NatsSuitcase* device = nats_init_device();

    //The extreme low point is the extreme low point of the wheels
    param->x = 400;
    param->y = 500;
    param->wb = 150;
    param->hb = 250;
    param->hp = 200;
    param->wh = 140;
    param->rw = 20;
    param->angle= 155;
    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE((device->y_einf - device->y_suitcase) <= 0.0001);
    REQUIRE((device->y_einf - 500) <= 0.0001);

    delete param;
    delete device;
}

//Test 5.3: nats_setextreme (extreme left point)
TEST_CASE("Test 5.3: nats_setextreme (it should set the extreme points of the suitcase in various situations)", "[suitcase]") {

    NatsParameters* param = nats_init_param();
    NatsSuitcase* device = nats_init_device();

    //Case 1: the extreme left point is the extreme left point of the left wheel
    param->x = 400;
    param->y = 500;
    param->wb = 200;
    param->hb = 250;
    param->hp = 150;
    param->wh = 100;
    param->rw = 40;
    param->angle= 300;
    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE((device->x_esx - device->wheelsx.xs_wheel) <= 0.0001);
    REQUIRE((device->x_esx - 260) <= 0.0001);

    //Case 2: the extreme left point is the extreme left point of the handle
    param->rw = 20;
    param->hp = 200;
    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE((device->x_esx - device->handle.xas_handle) <= 0.0001);
    REQUIRE((device->x_esx - 267.15390) <= 0.0001);

    delete param;
    delete device;
}

//Test 5.4: nats_setextreme (extreme right point)
TEST_CASE("Test 5.4: nats_setextreme (it should set the extreme points of the suitcase in various situations)", "[suitcase]") {

    NatsParameters* param = nats_init_param();
    NatsSuitcase* device = nats_init_device();

    //Case 1: the extreme right point is the extreme right point of the left wheel
    param->x = 400;
    param->y = 500;
    param->wb = 200;
    param->hb = 250;
    param->hp = 150;
    param->wh = 100;
    param->rw = 40;
    param->angle= 300;
    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE((device->x_edx - device->wheeldx.xd_wheel) <= 0.0001);
    REQUIRE((device->x_edx - 540) <= 0.0001);
    
    //Case 2: the extreme right point is the extreme right point of the junction
    param->rw = 20;
    param->hp = 200;
    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE((device->x_edx - device->junction.xd_wheel) <= 0.0001);
    REQUIRE((device->x_edx - 525) <= 0.0001);

    //Case 3: the extreme right point is the extreme right point of the handle
    param->rw = 40;
    param->hp = 200;
    param->angle = 45;
    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE((device->x_edx - device->handle.xad_handle) <= 0.0001);
    REQUIRE((device->x_edx - 705.06097) <= 0.0001);

    //Case 4: the extreme right point is the extreme left point of the handle
    param->angle = 120;
    nats_setparameters(param, device);
    nats_setextreme(device);

    REQUIRE((device->x_edx - device->handle.xas_handle) <= 0.0001);
    REQUIRE((device->x_edx - 732.84609) <= 0.0001);


    delete param;
    delete device;
}

//Test 6.1: nats_control_suitcase
TEST_CASE("Test 6.1: nats_control_suitcase (it should return a int for each type of error)"){

    NatsParameters* param = nats_init_param();
    NatsSuitcase* device = nats_init_device();

    //Case 1: extreme left point is out of the file
    param->x = 100;
    param->y = 500;
    param->wb = 200;
    param->hb = 250;
    param->hp = 200;
    param->wh = 80;
    param->rw = 30;
    param->angle= 45;
    nats_setparameters(param, device);
    nats_setextreme(device);
    int i = nats_control_suitcase(device);

    REQUIRE(i == 9);

    //Case 2: extreme right point is out of the file
    param->x = 700;
    nats_setparameters(param, device);
    nats_setextreme(device);
    i = nats_control_suitcase(device);

    REQUIRE(i == 10);

    //Case 3: extreme high point is out of the file
    param->x = 400;
    param->angle = 0;
    nats_setparameters(param, device);
    nats_setextreme(device);
    i = nats_control_suitcase(device);

    REQUIRE(i == 11);

    delete param;
    delete device;
}

//Test 6.2: nats_control_suitcase
TEST_CASE("Test 6.2: nats_control_suitcase (it should return a int for each type of error)"){

    NatsParameters* param = nats_init_param();
    NatsSuitcase* device = nats_init_device();

    //Case 1: height of the pole and handle is greater than the height of the body
    param->x = 400;
    param->y = 500;
    param->wb = 200;
    param->hb = 250;
    param->hp = 210;
    param->wh = 80;
    param->rw = 30;
    param->angle= 45;
    nats_setparameters(param, device);
    nats_setextreme(device);
    int i = nats_control_suitcase(device);

    REQUIRE(i == 13);

    //Case 2: width of the handle is greater than the width of the body
    param->hp = 100;
    param->wh = 210;
    nats_setparameters(param, device);
    nats_setextreme(device);
    i = nats_control_suitcase(device);

    REQUIRE(i == 14);

    //Case 3: width of the pole is greater than the width of the handle
    param->wh = 10;
    nats_setparameters(param, device);
    nats_setextreme(device);
    i = nats_control_suitcase(device);

    REQUIRE(i == 15);

    //Case 4: radius of the wheels is greater than the half of the width of the body
    param->wh = 80;
    param->rw = 101;
    nats_setparameters(param, device);
    nats_setextreme(device);
    i = nats_control_suitcase(device);

    REQUIRE(i == 16);
    
    delete param;
    delete device;
}

//Test 6.3: nats_control_suitcase
TEST_CASE("Test 6.3: nats_control_suitcase (it should return a int for each type of error)"){

    NatsParameters* param = nats_init_param();
    NatsSuitcase* device = nats_init_device();

    //Case 1: handle touch the wheel
    param->x = 400;
    param->y = 500;
    param->wb = 200;
    param->hb = 250;
    param->hp = 200;
    param->wh = 80;
    param->rw = 40;
    param->angle= 165;
    nats_setparameters(param, device);
    nats_setextreme(device);
    int i = nats_control_suitcase(device);

    REQUIRE(i == 17);

    //Case 2:handle touch the body
    param->angle = 280;
    nats_setparameters(param, device);
    nats_setextreme(device);
    i = nats_control_suitcase(device);

    REQUIRE(i == 18);
    
    delete param;
    delete device;
}
