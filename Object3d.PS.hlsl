struct PixelShaderOutput{
float32_t4 color : SV_TARGET0;
};

struct Camera{
float32_t3 worldPosition;
}

ConstantBuffer<Camera>gCamera:reister(b2);


PixelShaderOutput main(){
PixelShaderOutput output;
output.color=float32_t4(1.0, 1.0, 1.0, 1.0);
return output;
}