#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
flat in int texID;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{
	vec4 temp;

	switch(texID)
	{
		case 0:
		temp = texture(texture1, TexCoord);
			if((temp.x + temp.y +temp.z) > 2.99)
			{
				discard;
			}
		break;
		case 1:
		temp = texture(texture2, TexCoord);
		break;
		case 2:
		temp = texture(texture3, TexCoord);
			if(temp.y > temp.z)
			{
				discard;
			}
		break;
	}

	if((temp.x + temp.y +temp.z) < 0.02)
	{
		discard;
	}
	
	FragColor = temp;
}