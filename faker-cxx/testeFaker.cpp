#include <iostream>
#include "faker-cxx/faker.h"

int main()
{
    // Generate a random city
    std::cout << "Onde a foto foi tirada: " << faker::location::city(faker::Locale::pt_BR) << std::endl;
    
    // Generate a random dimension
    std::cout << "Dimensoes: " << faker::image::dimensions() << std::endl;
    
    return 0;
}