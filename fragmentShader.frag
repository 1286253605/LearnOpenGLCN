#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec3 outVertPos;
in vec2 TexCoord;       // 从顶点着色器传递的纹理坐标 范围是 [0,1]

uniform sampler2D texture1; // 纹理采样器 以纹理类型作为后缀 1D 2D 3D 
uniform sampler2D texture2; 

void main()
{
    // FragColor = vec4(ourColor, 1.0);
    // 使得顶点位置控制顶点颜色 
    // FragColor = vec4( outVertPos, 1.0 );

    // 纹理对应纹理坐标
    // FragColor = texture( outTexture, TexCoord );
    // FragColor = texture( outTexture, TexCoord ) * vec4(ourColor, 1.0);

    // mix第三个参数为 第2个texture的占比
    FragColor = mix( texture( texture1, TexCoord ), texture( texture2, vec2( 1 - TexCoord.x, 1 - TexCoord.y ) ),  0.3);
    FragColor = FragColor * vec4(ourColor, 1.0);
}