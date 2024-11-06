
struct PS_Input {
    float4 pos : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0) {
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;

    unsigned int m_time;
};

float4 PSMain(PS_Input input) : SV_TARGET {

    //return float4(lerp(input.color, input.color1, (sin(m_time / 500.0f) + 1.0f) / 2.0f),1.0f);
    return float4(input.color.x, input.color.y, input.color.z, 1);
}