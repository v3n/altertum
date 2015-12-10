/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#include <bgfx/bgfx.h>

namespace bgfx_util
{
#   include "bgfx_utils.h"
}

#include "mesh_asset.h"

namespace altertum
{

namespace mesh_asset
{
    void * load(const char * file, foundation::Allocator& a)
    {
        // Mesh * m = meshLoad(file);
    }

    void unload(void * asset, foundation::Allocator& a)
    {

    }

    void on(AssetId id, AssetRegistry& ar)
    {
        Mesh * m = (Mesh *)ar.get(id);

        m->vb = bgfx::createVertexBuffer(m->vertices, m->ms_decl);
        m->ib = bgfx::createIndexBuffer(m->indices);
    }

    void off(AssetId id, AssetRegistry& ar)
    {
        Mesh * m = (Mesh *)ar.get(id);

        bgfx::destroyVertexBuffer(m->vb);
        bgfx::destroyIndexBuffer(m->ib);

        m->vb = BGFX_INVALID_HANDLE;
        m->ib = BGFX_INVALID_HANDLE;
    }
} // namespace mesh_asset
} // namespace altertum
