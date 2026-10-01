#ifndef GROUP_H
#define GROUP_H

#include "Shape.h"

class Group : public Shape
{
public:
    Group();

    int getChildrenCount();

    bool isEmpty();

    Shape* getChild(std::size_t childNumber) const;

    template <typename genericShape>
    genericShape* addChild(std::unique_ptr<genericShape> childShape) {
        static_assert (std::is_base_of_v<Shape, genericShape>, "genericShape must derive from Shape");
        auto* childPointer = childShape.get();
        childShape->setParent(this);
        children.push_back(std::move(childShape));
        return childPointer;
    }

protected:
    Tuple localNormalAt(const Tuple &localPoint) const override;
    void localIntersect(const Ray &localRay, IntersectionTracker &tracker) override;

private:
    std::vector<std::unique_ptr<Shape>> children;
};

#endif // GROUP_H
