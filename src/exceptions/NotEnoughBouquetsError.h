#ifndef TP1_NOTENOUGHBOUQUETSERROR_H
#define TP1_NOTENOUGHBOUQUETSERROR_H


#include <exception>
#include <string>

class NotEnoughBouquetsError : std::exception {
    const std::string& type;
    unsigned int amount_requested;
    unsigned int amount_stored;
public:
    NotEnoughBouquetsError(const std::string& type, unsigned int amount_requested, unsigned int amount_stored);
    const char* what() const throw() override;
};


#endif //TP1_NOTENOUGHBOUQUETSERROR_H
