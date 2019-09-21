#include <sstream>
#include "NotEnoughBouquetsError.h"

NotEnoughBouquetsError::NotEnoughBouquetsError(const std::string &type,
        unsigned int amount_requested, unsigned int amount_stored) :
        std::exception(),
        type(type),
        amount_requested(amount_requested),
        amount_stored(amount_stored) {
}

const char *NotEnoughBouquetsError::what() const throw() {
    std::ostringstream msg;
    msg << "No hay suficientes flores de tipo " <<
    type << " para procesar el pedido. Se pidieron " << amount_requested
    << ", hay " << amount_stored << ".";

    return msg.str().c_str();
}
