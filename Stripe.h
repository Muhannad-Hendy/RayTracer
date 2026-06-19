#ifndef STRIPE_H
#define STRIPE_H

#include "Pattern.h"

class Stripe : public Pattern
{
public:
    using Pattern::Pattern;

protected:
    const Color patternAt(const Tuple &patternPoint) const override;
};

#endif // STRIPE_H
