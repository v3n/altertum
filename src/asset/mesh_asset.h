/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include "asset_types.h"
#include "asset_registry.h"

#include "foundation/memory.h"

namespace altertum
{

namespace mesh_asset
{
    void * load(const char * file, foundation::Allocator& a);
    void unload(void * asset, foundation::Allocator& a);
    void online(AssetId id, AssetRegistry& ar);
    void offline(AssetId id, AssetRegistry& ar);
}
} // namespace altertum
