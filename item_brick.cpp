#include "headers/item_brick.h"

ItemBrick::ItemBrick() : Brick(0, 0, 0, 0, 1), item_type_(Nothing) {}

ItemBrick::ItemBrick(float x, float y, float width, float height, ItemType item_type) :
    Brick(x, y, width, height, 1), item_type_(item_type) {}

void ItemBrick::setItemType(ItemType item_type) {
    item_type_ = item_type;
}

ItemType ItemBrick::getItemType() {
    return item_type_;
}