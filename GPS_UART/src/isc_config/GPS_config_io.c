
#include "GPS_config_io.h"

/*

The function gpio_pin_configure_dt() is used to configure a GPIO pin based on the device tree (DT) configuration.

Here's a breakdown of what each part of the function does:

gpio_pin_configure_dt: It configures a GPIO pin according to the settings specified in the device tree.

example &CE: This is likely a reference to a GPIO pin object. GPIO pins are often represented as structures containing configuration information.

GPIO_OUTPUT / GPIO_INPUT: This parameter specifies the desired configuration of the GPIO pin.  GPIO_OUTPUT / / GPIO_INPUT likely means configuring the pin as an input/ output, allowing it to drive a signal either high or low.

In summary, the function gpio_pin_configure_dt() configures a GPIO pin based on the configuration specified in the device tree. This allows for easy and consistent pin configuration across different hardware configurations defined in the device tree.

*/
int GPIO_INIT(void)
{
        int ret;

        printk("GPIO init\n");
        
        ret = gpio_pin_configure_dt(&CE, GPIO_OUTPUT); 
        if (ret < 0)
        {
                return 1;
        }

        
        ret = gpio_pin_configure_dt(&DS_EN, GPIO_INPUT);
        if (ret < 0)
        {
                return 1;
        }
        ret = gpio_pin_configure_dt(&DS_STS, GPIO_OUTPUT);
        if (ret < 0)
        {
                return 1;
        }
        ret = gpio_pin_configure_dt(&SYS_READY, GPIO_OUTPUT);
        if (ret < 0)
        {
                return 1;
        }
        ret = gpio_pin_configure_dt(&FIX_OUT, GPIO_OUTPUT);
        if (ret < 0)
        {
                return 1;
        }
        ret = gpio_pin_configure_dt(&AUTO_START, GPIO_INPUT);
        if (ret < 0)
        {
                return 1;
        }
        ret = gpio_pin_configure_dt(&EPPS_OUT, GPIO_OUTPUT);
        if (ret < 0)
        {
                return 1;
        }
        ret = gpio_pin_configure_dt(&IF_CTRL, GPIO_INPUT);
        if (ret < 0)
        {
                return 1;
        }
        ret = gpio_pin_configure_dt(&nRESET, GPIO_OUTPUT);
        if (ret < 0)
        {
                return 1;
        }
        
}

/*
gpio_pin_set_dt(&DS_EN, SET); 

Here's a breakdown of the components:

gpio_pin_set_dt: This function that interacts with a GPIO (General Purpose Input/Output) pin. The "gpio_pin_set" part suggests it's setting the pin.

example &DS_EN: the GPIO pin is the address-of operator, so this suggests that DS_EN is a pointer to the GPIO pin configuration or a GPIO pin structure.

SET: This indicates the state to which the GPIO pin is being set. It could be a predefined constant or macro representing a logical state, like "HIGH" or "LOW", or it could be a numeric value representing the state.

In the nRF context, this function call would set the GPIO pin represented by DS_EN to the state indicated by SET. This could be setting the pin to a high voltage level, a low voltage level, or some other state depending on how the macro or constant SET is defined.

*/


void CE_CONFIG(void){

        // gpio_pin_set_dt(&DS_EN,CLEAR);
        // k_msleep(5);
        gpio_pin_set_dt(&DS_EN,HIGH);

}

void DS_EN_CONFIG(void){

        // gpio_pin_set_dt(&DS_EN,CLEAR);
        // k_msleep(5);
        gpio_pin_set_dt(&DS_EN,HIGH);

}

void DS_STS_CONFIG(void){

        // gpio_pin_set_dt(&DS_EN,SET);
        // k_msleep(5);
        gpio_pin_set_dt(&DS_EN,LOW);

}

void SYS_READY_CONFIG(void){
        // gpio_pin_set_dt(&DS_EN,SET);
        // k_msleep(5);
        gpio_pin_set_dt(&DS_EN,LOW);
}


void FIX_OUT_CONFIG(void){

        // gpio_pin_set_dt(&DS_EN,CLEAR);
        // k_msleep(5);
        gpio_pin_set_dt(&DS_EN,HIGH);

}


void AUTO_START_CONFIG(void){

        // gpio_pin_set_dt(&DS_EN,CLEAR);
        // k_msleep(5);
        gpio_pin_set_dt(&DS_EN,HIGH);

}
void EPPS_OUT_CONFIG(void){
        // gpio_pin_set_dt(&DS_EN,CLEAR);
        // k_msleep(5);
        gpio_pin_set_dt(&DS_EN,HIGH);
}

void IF_CTRL_CONFIG(void){

        // gpio_pin_set_dt(&DS_EN,SET);
        // k_msleep(5);
        gpio_pin_set_dt(&DS_EN,LOW);
}

void nRESET_CONFIG(void){

        // gpio_pin_set_dt(&DS_EN,SET);
        // k_msleep(5);
        gpio_pin_set_dt(&DS_EN,HIGH);
}



