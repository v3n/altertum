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

        return nullptr;
    }

    void unload(void * asset, foundation::Allocator& a)
    {

    }

    void on(AssetId id, AssetRegistry& ar)
    {
        Mesh * m = (Mesh *)ar.get(id);

        m->vertex_buffer = bgfx::createVertexBuffer(m->vertices, m->ms_decl);
        m->index_buffer = bgfx::createIndexBuffer(m->indices);
    }

    void off(AssetId id, AssetRegistry& ar)
    {
        Mesh * m = (Mesh *)ar.get(id);

        bgfx::destroyVertexBuffer(m->vertex_buffer);
        bgfx::destroyIndexBuffer(m->index_buffer);

        m->vertex_buffer = BGFX_INVALID_HANDLE;
        m->index_buffer = BGFX_INVALID_HANDLE;
    }
} // namespace mesh_asset
} // namespace altertum
