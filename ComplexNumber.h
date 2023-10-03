//
// Created by Thomas B on 04/09/2023.
//

#include <cstdint>

struct ComplexNumber {
    float64_t real{};
    float64_t imag{};
};
ComplexNumber addComplex(ComplexNumber self, ComplexNumber other) {
    return ComplexNumber{self.real + other.real, self.imag + other.imag};
}
ComplexNumber addComplex(ComplexNumber* self, ComplexNumber other) {
    return ComplexNumber{self->real + other.real, self->imag + other.imag};
}
ComplexNumber addComplex(ComplexNumber self, ComplexNumber* other) {
    return ComplexNumber{self.real + other->real, self.imag + other->imag};
}
ComplexNumber addComplex(ComplexNumber* self, ComplexNumber* other) {
    return ComplexNumber{self->real + other->real, self->imag + other->imag};
}

ComplexNumber subtractComplex(ComplexNumber* self, ComplexNumber other) {
    return ComplexNumber{self->real - other.real, self->imag - other.imag};
}
ComplexNumber subtractComplex(ComplexNumber* self, ComplexNumber* other) {
    return ComplexNumber{self->real - other->real, self->imag - other->imag};
}

ComplexNumber multiplyComplex(ComplexNumber* self, ComplexNumber other) {
    return ComplexNumber{(self->real * other.real) - (self->imag * other.imag),
                         (self->real * other.imag) + (self->imag * other.real)};
}
ComplexNumber multiplyComplex(ComplexNumber* self, ComplexNumber* other) {
    return ComplexNumber{(self->real * other->real) - (self->imag * other->imag),
                         (self->real * other->imag) + (self->imag * other->real)};
}

float64_t lengthComplex(ComplexNumber* self) {
    return (self->real * self->real) + (self->imag * self->imag);
}