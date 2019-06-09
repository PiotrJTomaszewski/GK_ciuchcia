#version 330


out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec4 i_color;
in vec4 ds;
in vec4 nor;
in vec4 dob;
in vec4 ds1;
in vec2 texCoord;

uniform sampler2D myTexture;

void main(void) {

    float nl = clamp(dot(normalize(ds),normalize(nor)),0,1);
    nl += clamp(dot(normalize(ds1),normalize(nor)),0,1);

    nl = clamp(nl,0,1);

    vec4 mr =  reflect(-normalize(ds),normalize(nor));

    float nf = pow(clamp(dot(mr,normalize(dob)),0,1),25);
    pixelColor = texture(myTexture, texCoord);
//	pixelColor=vec4(i_color.rgb*nl+vec3(1,1,1)*nf,i_color.a);
}
