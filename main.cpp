#include "mbed.h"
#include "Si114x.h"
#include "Si114x_defs.h"

int main()
{
Si114x sensor(I2C_SDA, I2C_SCL);
    while(sensor.verifyConnection() != 1);
    unsigned short visible;
    unsigned short ir;
    unsigned short uv;
    unsigned short temp;

    while (true) {
    visible = sensor.getVisibleLight();
    ir = sensor.getIRLight();
    uv = sensor.getUVIndex();
    //printf("Lumiere infra-rouge: %d\n",ir);
    printf("Lumiere visible: %d\n",visible);
    printf("Indice UV: %d\n",uv);
    wait_us(500000);
    temp=sensor.getCouleur();
    

    if (temp<1000) 
    {
        printf("rouge (%d)\n",temp);
    }
    else if (temp<2500)
    {
        printf("orange(%d)\n",temp);
    }
    else if (temp<4000)
    {
        printf("jaune(%d)\n",temp);
    }
    else if (temp<6000)
    {
        printf("blanc(%d)\n",temp);
    }
    else
    {
       printf("bleu(%d)\n",temp); 
    }
    
    }
}
