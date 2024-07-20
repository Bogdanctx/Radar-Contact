#ifndef OOP_AIRPLANE_H
#define OOP_AIRPLANE_H

#include "FlyingEntity.h"

class Airplane : public FlyingEntity {
public:
    template <typename... Args>
    explicit Airplane(Args... args) : FlyingEntity(args...) {
        setSpeedConstraints(160, 335);
        setAltitudeConstraints(2000, 43000);
        setClocks(Clocks(1100, 750, 800, 230));
    }

private:
    void hijackUpdateData() override;
    void internalUpdate() override;
};


#endif //OOP_AIRPLANE_H
