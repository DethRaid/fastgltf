#pragma once

#if FASTGLTF_ENABLE_GLTFX

#include "fastgltf/core.hpp"

/**
 * Defines various structs and functions that are useful for gltfx
 */
namespace fastgltfx {
    using namespace fastgltf;

    /**
     * Metadata about the asset
     */
    FASTGLTF_EXPORT struct AssetInfo {
        /**
         * The program that generated the asset
         */
        std::string generator;

        /**
         * True if this is a glTFX reference file (it always is)
         */
        bool reference;

        /**
         * glTFX version of this asset
         */
        num version;
    };

    /**
     * How to apply light sources to the references assets
     */
    FASTGLTF_EXPORT enum class LightSource {
        /**
         * Light from this asset may not affect other assets
         */
        Asset,

        /**
         * Light from this asset may affect the entire scene
         */
        Scene,
    };

    /**
     * A glTFX asset is an external data source that is a part of this file. Exactly what to do with that data source depends on a few factors
     */
    FASTGLTF_EXPORT struct Asset {
        /**
         * Name of this asset
         */
        std::string name;

        /**
         * URI to load this asset from 
         */
        URI uri;

        /**
         * How to apply this asset's lights to the scene (this is very poorly named)
         */
        LightSource lightSource = LightSource::Scene;

        /**
         * Index of the environment light to apply to this asset
         */
        std::optional<size_t> environment;

        /**
         * Minimum location of this asset's bounding box, relative to the asset's origin
         */
        Optional<math::fvec3> min;

        /**
         * Maximum location of this asset's bounding box, relative to the asset's origin
         */
        Optional<math::fvec3> max;
    };

    /**
     * Specifies a lighting environment that may affect an asset
     */
    FASTGLTF_EXPORT struct EnvironmentLight {
        /**
         * URI to load this environment light from. Should be an HDR environment map
         */
        URI uri;

        /**
         * Intensity to adjust the environment light by
         */
        num intensity = 1.0;
    };

    /**
     * A Node in a glTFX scene
     */
    FASTGLTF_EXPORT struct Node {
        /**
         * Index of the asset to load for this node
         */
        Optional<std::size_t> asset;

        std::string name;

        math::fvec3 translation = {0, 0, 0};
        math::fquat rotation = math::fquat{0, 0, 0, 1};
        math::fvec3 scale = {1, 1, 1};

        FASTGLTF_STD_PMR_NS::vector<size_t> children;
    };
}

#endif
