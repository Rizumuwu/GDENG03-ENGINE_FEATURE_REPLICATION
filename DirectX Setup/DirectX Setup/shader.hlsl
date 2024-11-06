float4 VSMain(float4 pos : POSITION) : SV_POSITION
{
    return pos;
}

float4 PSMain(float4 pos : SV_POSITION) : SV_TARGET
{
    return float4(0.5f, 0.6f, 0.5f, 1.0f);
}