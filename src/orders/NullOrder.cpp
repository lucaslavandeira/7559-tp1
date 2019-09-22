#include "NullOrder.h"

NullOrder::NullOrder() : Order(0, 0){
    Order::fulfilled = false;
}
