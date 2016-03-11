/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#include "asset_registry.h"

#include "foundation/hash.h"
#include "foundation/murmur_hash.h"

namespace altertum
{

const   AssetRegistry::AssetInstance
        AssetRegistry::AssetInstance::NOT_FOUND = { 0xffffffffu, (void *)AssetTypes::ASSET_UNKNOWN };

AssetRegistry::AssetRegistry() : _instances(foundation::memory_globals::default_allocator())
{
    _types[AssetTypes::ASSET_UNKNOWN]   = { nullptr, nullptr, nullptr, nullptr };
    _types[AssetTypes::ASSET_AUDIO]     = { nullptr, nullptr, nullptr, nullptr };
    _types[AssetTypes::ASSET_MESH]      = { nullptr, nullptr, nullptr, nullptr };
    _types[AssetTypes::ASSET_TEXTURE]   = { nullptr, nullptr, nullptr, nullptr };
    _types[AssetTypes::ASSET_REGISTRY]  = { nullptr, nullptr, nullptr, nullptr };
    _types[AssetTypes::ASSET_SCRIPT]    = { nullptr, nullptr, nullptr, nullptr };
    _types[AssetTypes::ASSET_PACKAGE]   = { nullptr, nullptr, nullptr, nullptr };
}

AssetRegistry::~AssetRegistry()
{
}

void * AssetRegistry::get(AssetId id)
{
    return foundation::hash::get(_instances, id, AssetInstance::NOT_FOUND).data;
}

void AssetRegistry::load(unsigned type, const char * path)
{
    using namespace foundation;
    const AssetInstance& instance = hash::get(_instances, murmur_hash_64(path, (uint32_t)strlen(path), 0), AssetInstance::NOT_FOUND);

    if ( instance == AssetInstance::NOT_FOUND )
    {
        _types[type].load(path);
    }
}

void AssetRegistry::unload(AssetId id)
{

}

void AssetRegistry::on(AssetId id)
{

}

void AssetRegistry::off(AssetId id)
{

}

} // namespace altertum
