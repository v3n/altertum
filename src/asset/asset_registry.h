
/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include <string>

#include "foundation/collection_types.h"

#include "asset/asset_types.h"
#include "platform/thread/thread.h"

namespace altertum
{

typedef uint64_t AssetId;

class AssetRegistry
{
public:
    AssetRegistry();
    ~AssetRegistry();

    // void register();

    void * get(AssetId id);

    void load(unsigned type, const char * path);
    void unload(AssetId id);

    void gc();

    void on(AssetId id);
    void off(AssetId id);

private:
    typedef void *  (*LoadFunction)(const char *);
    typedef void    (*UnloadFunction)(AssetId);
    typedef void    (*OnlineFunction)(AssetId);
    typedef void    (*OfflineFunction)(AssetId);

private:
    struct AssetInstance
    {
        uint32_t references;    /** reference count */
        void * data;            /** pointer to type-specific data */
        std::string path;       /** @FIXME implement global string buffer */

        /** default unfound instance */
        static const AssetInstance NOT_FOUND;

        /** compare asset instances */
        inline bool operator==(const AssetInstance& ai) const
        {
            return (references == ai.references) && (data == ai.data);
        }
    };

    struct AssetHandlers
    {
        LoadFunction    load;
        UnloadFunction  unload;
        OnlineFunction  online;
        OfflineFunction offline;
    };

    /** database of handlers for all types */
    AssetHandlers _types[AssetTypes::SIZE];
    /** all registered instances */
    foundation::Hash<AssetInstance> _instances;
};


} // namespace altertum
