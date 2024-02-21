#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Item.h"

struct ItemBundle {
    int objectType;
    int num;
};

class InventoryComponent :
    public Component
{
    std::unordered_map<int, ItemBundle> inventory;
public:
    static const int MAX_INVENTORY;
public:
    void Start();
    void Update(double elapsedTime);
    
    void AddItem(E_OBJECT type);
};

