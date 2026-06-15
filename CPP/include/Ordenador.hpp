#ifndef ORDENADOR_HPP
#define ORDENADOR_HPP

class Ordenador {
public:
    virtual void ejecutar() = 0;
    virtual ~Ordenador() = default;
};

#endif