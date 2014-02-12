//
//  Addon.cpp
//  SampleGame
//
//  Created by Stanislav Korotaev on 1/26/14.
//  Copyright (c) 2014 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Addon.h"

Addon::Addon(Hexagon* hex, Addon::Type type): hex(hex), addonType(type)
{
	CCNode::init();
}

Addon::Type Addon::getType() const
{
    return addonType;
}