#version 330

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec4 i_color;
in vec4 lpos0;
in vec4 lpos1;
in vec4 ds; // Wektor do swiatla 0
in vec4 nor; // Wektor normalny
in vec4 dob;
in vec4 ds1; // Wektor do swiatla 1
in vec2 texCoord; // Wspolrzedne teksturowania
in vec4 fragPos;

uniform sampler2D tex;


struct Light {
    vec4 light_position;
    vec4 light_color;

    // Tlumienie
    float constant;
    float linear;
    float quadratic;

    float ambient_strength;
    float diffuse_strength;
    float specular_strength;
};

vec4 calculate_light(Light light, vec4 normal, vec4 fragPos, vec4 ds){
    // Attenuation
    float dist = length(light.light_position - fragPos);
    float att = 1.0f / (light.constant + light.linear*dist + light.quadratic * (dist*dist));

    // Ambient
    vec4 ambient = light.ambient_strength * texture(tex,texCoord);

    // Diffuse
    float nor_ds  = clamp(dot(nor,ds),0,1); // Wektor normalny dot wektor do swiatla
    vec4 diffuse = light.diffuse_strength * nor_ds * texture(tex,texCoord);

    // Specular
    vec4 reflected = reflect(-ds,nor);
    float spec = pow(clamp(dot(dob,reflected),0,1),32);
    vec4 specular = light.specular_strength * spec * light.light_color;

    ambient *= att;
    diffuse *= att;
    specular *= att;

    return vec4(ambient.rgb+diffuse.rgb+specular.rgb,1.0f);
}

void main(void) {

    Light light_one;
    light_one.light_position = lpos0;
    light_one.light_color = vec4(1.0f,0.0f,1.0f,1.0f);
    light_one.ambient_strength = 0.5f;
    light_one.diffuse_strength = 0.5f;
    light_one.specular_strength = 1.0f;
    light_one.constant = 0.8f;
    light_one.linear = 0.025f;
    light_one.quadratic = 0.0006f;

    Light light_two;
    light_two.light_position = lpos1;
    light_two.light_color = vec4(0.0f,1.0f,1.0f,1.0f);
    light_two.ambient_strength = 0.3f;
    light_two.diffuse_strength = 0.6f;
    light_two.specular_strength = 1.0f;
    light_two.constant = 0.3f;
    light_two.linear = 0.02f;
    light_two.quadratic = 0.0001f;


    vec4 color_one = calculate_light(light_one, nor, fragPos, ds);
    vec4 color_two = calculate_light(light_two, nor, fragPos, ds1);

    pixelColor = color_one + color_two;
}
