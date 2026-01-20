//
//    Textures
//    g_texture0 : Texture passed from Siv3D
//    g_sampler0 : Sampler for texture sampling
//
Texture2D g_texture0 : register(t0);
SamplerState g_sampler0 : register(s0);

namespace s3d
{
    //
    //    VS Input
    //    position : Local vertex position
    //    uv       : Texture coordinates
    //    color    : Color and alpha passed from draw(ColorF)
    //
    struct VSInput
    {
        float2 position : POSITION;
        float2 uv : TEXCOORD0;
        float4 color : COLOR0;
    };

    //
    //    VS Output / PS Input
    //    position : Transformed screen position
    //    color    : Vertex color (draw(ColorF) * g_colorMul)
    //    uv       : Texture coordinates
    //
    struct PSInput
    {
        float4 position : SV_POSITION;
        float4 color : COLOR0;
        float2 uv : TEXCOORD0;
    };

    //
    //    Siv3D internal function
    //    Transforms 2D coordinates using Siv3D's transform matrix
    //
    float4 Transform2D(float2 pos, float2x4 t)
    {
        return float4(
            (t._13_14 + (pos.x * t._11_12) + (pos.y * t._21_22)),
            t._23_24
        );
    }
}

//
//    Constant Buffers
//    Used internally by Siv3D
//
cbuffer VSConstants2D : register(b0)
{
    row_major float2x4 g_transform; // 2D transform matrix
    float4 g_colorMul; // Global color multiplier
}

cbuffer PSConstants2D : register(b0)
{
    float4 g_colorAdd;
    float4 g_sdfParam;
    float4 g_sdfOutlineColor;
    float4 g_sdfShadowColor;
    float4 g_internal;
}

//
//    Vertex Shader
//    Transforms vertex positions and passes color and UV to the pixel shader
//
s3d::PSInput VS(s3d::VSInput input)
{
    s3d::PSInput result;

    // Transform to screen space
    result.position = s3d::Transform2D(input.position, g_transform);

    // Apply draw(ColorF) color and Siv3D color multiplier
    result.color = input.color * g_colorMul;

    // Pass texture coordinates
    result.uv = input.uv;

    return result;
}

//
//    Pixel Shader
//    Applies a circular vignette effect and uses draw(ColorF)
//    alpha for fade-in / fade-out control
//
float4 main(s3d::PSInput input) : SV_TARGET
{
    // Sample base texture color
    float4 texColor = g_texture0.Sample(g_sampler0, input.uv);

    // Screen center in UV space
    float2 center = float2(0.5, 0.5);

    // Distance from center
    float dist = distance(input.uv, center);

    // Vignette shape
    // Alpha increases smoothly toward the edges
    float vignette = smoothstep(0.4, 0.7, dist);

    // Apply color and alpha from draw(ColorF)
    float4 color = texColor * input.color;

    // Combine vignette alpha with draw(ColorF) alpha
    color.a *= vignette;

    return color;
}
