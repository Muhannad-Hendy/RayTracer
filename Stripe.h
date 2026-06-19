#ifndef STRIPE_H
#define STRIPE_H

#include "Pattern.h"

class Stripe : public Pattern
{
public:
    Stripe();

protected:
    const Color patternAt(const Tuple &patternPoint) const override;
};

#endif // STRIPE_H
