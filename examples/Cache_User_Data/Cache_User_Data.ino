#include <Arduino.h>

#include <WM1110_Storage.hpp>


uint32_t test_data_key = 0x3000;
uint32_t test_data_value = 0x01;
uint32_t test_data_size = 0x4;


void setup()
{
    Serial.begin(115200);
    while (!Serial) delay(100);   

    printf("WM1110 Cache User Data Example\r\n");

    test_data_size = sizeof(test_data_value);
    //Read-write overlay example
    wm1110_storage.begin();
    int ret = wm1110_storage.readStorageKeyValue(test_data_key,&test_data_value,test_data_size);
    if(ret >= 0 )
    {
        printf("booting test data value:%d\r\n",test_data_value);
    }
    else
    {
        ret = wm1110_storage.writeStorageKeyValue(test_data_key,&test_data_value,test_data_size);
        if(ret < 0)
        {
            printf("write test data value error:%d\r\n",ret);
        }
        else
        {
            printf("write default test data value:%d\r\n",test_data_value);
        }
    }
}

void loop()
{
    uint32_t read_data = 0;
    test_data_value++;
    int ret = wm1110_storage.writeStorageKeyValue(test_data_key,&test_data_value,test_data_size);
    if(ret < 0)
    {
        printf("write test data value error:%d\r\n",ret);
    }
    else
    {
        int ret = wm1110_storage.readStorageKeyValue(test_data_key,&test_data_value,test_data_size);
        if(ret >= 0 )
        {
            printf("test data value:%d\r\n",test_data_value);
        }
    }
    delay(1000);      
}







