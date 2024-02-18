#pragma once
#include "Component.h"
class InventoryComponent :
    public Component
{
public:
    void Start();
    void Update(double elapsedTime);
};

