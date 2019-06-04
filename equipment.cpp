#include "equipment.h"

Equipment::Equipment()    //初始化
{
    device_name = "";
    device_type = "";
    device_number = "";
    model_number = "";
    device_spec = "";
    device_price = 0;
    device_quantity = 0;
    buy_date= new QDate(2016,1,1);
    device_producer = "";
    device_purchaser = "";
    device_lot = "";
}
