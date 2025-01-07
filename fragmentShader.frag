#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec3 outVertPos;
in vec2 TexCoord;

uniform sampler2D texture1;
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
    FragColor = mix( texture( texture1, TexCoord ), texture( texture2, TexCoord ),  0.3);
    FragColor = FragColor * vec4(ourColor, 1.0);
}