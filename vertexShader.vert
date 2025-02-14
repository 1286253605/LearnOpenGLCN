#version 330 core
layout (location = 0) in vec3 aPos;         // 位置变量的属性位置值为 0 
layout (location = 1) in vec3 aColor;       // 颜色变量的属性位置值为 1
layout (location = 2) in vec2 aTexCoord;    // 纹理坐标属性位置为2

out vec3 ourColor; // 向片段着色器输出一个颜色
out vec3 outVertPos;
out vec2 TexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 view;

void main()
{
    // 使得三角形上下颠倒
    // gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);

    
    
    outVertPos = aPos;
    ourColor = aColor; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
    TexCoord = aTexCoord;
    // gl_Position = vec4( aPos, 1.0 );
    // gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    gl_Position = projectionMatrix * view * modelMatrix * vec4(aPos, 1.0);
}