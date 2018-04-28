#include "headers/item_brick.h"

ItemBrick::ItemBrick() : Brick(), type_(NoEffect) {}

void ItemBrick::setItemType(ItemType type) {
    type_ = type;
}

ItemType ItemBrick::getItemType() {
    return type_;
}