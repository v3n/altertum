/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include <bgfx/bgfx.h>
#include "math/math_types.h"

namespace altertum
{

/**
 * Enum class declarations
 */
struct AssetTypes
{ enum {
      ASSET_UNKNOWN     /** used internally */
    , ASSET_AUDIO       /** audio **/
    , ASSET_MESH        /** mesh **/
    , ASSET_TEXTURE     /** texture **/
    , ASSET_SCRIPT      /** script **/
    , ASSET_REGISTRY    /** registry file */
    , ASSET_PACKAGE     /** packaged assets */
    // ...
    , SIZE
}; };


/**
 * static mesh data, base for model.
 */
struct Mesh
{
    // struct SubMesh
    // {
    //     unsigned start;
    //     unsigned length;
    // };

    bgfx::Memory * vertices;
    bgfx::Memory * indices;

    bgfx::VertexDecl            ms_decl;
    bgfx::VertexBufferHandle    vertex_buffer;
    bgfx::IndexBufferHandle     index_buffer;

    uint32_t vertex_stride;
    uint32_t indices_offset;

    uint32_t vertices_count;
    uint32_t indices_count;

    // unsigned     n_submeshed;
    // SubMesh      submeshes[ALTERTUM_MAX_SUBMESHES];
};

struct Joint
{
    Matrix4 g_pose;
    Matrix4 l_pose;
};

struct Texture
{
    bgfx::Memory uv;
    bgfx::TextureHandle texture;
};

} // namespace altertum
