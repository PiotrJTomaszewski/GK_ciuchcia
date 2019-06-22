#version 330

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec4 position_M; // Polozenie wierzcholka w przestrzeni swiata
in vec4 normal_V; // Wektor normalny w przestrzeni widoku
in vec4 eye_dir_V; // Wektor do obserwatora w przestrzeni widoku
in vec4 light_dir_one_V; // Wektor do swiatla 1 w przestrzeni widoku
in vec4 light_dir_two_V; // Wektor do swiatla 1 w przestrzeni widoku
in vec4 light_pos_one_M;
in vec4 light_pos_two_M;
in vec2 tex_coord; // Wspolrzedne teksturowania

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

vec4 calculate_light(Light light, vec4 normal, vec4 frag_pos, vec4 light_dir){
    // Tlumienie
    float dist = distance(light.light_position,frag_pos);
    float att = 1.0f / (light.constant + light.linear*dist + light.quadratic * (dist*dist));

    // Ambient
    vec4 ambient = light.ambient_strength * texture(tex,tex_coord);

    // Diffuse
    float nor_ld  = clamp(dot(normal,light_dir),0,1); // Wektor normalny dot wektor do swiatla
    vec4 diffuse = light.diffuse_strength * nor_ld * texture(tex,tex_coord);

    // Specular
    vec4 reflected = reflect(-light_dir,normal);
    float spec = pow(clamp(dot(eye_dir_V,reflected),0,1),50);
    vec4 specular = light.specular_strength * spec * light.light_color;

    ambient *= att;
    diffuse *= att;
    specular *= att;

    return vec4(ambient.rgb+diffuse.rgb+specular.rgb,1.0f);
}

void main(void) {
    Light light_one;
    light_one.light_position = light_pos_one_M;
    light_one.light_color = vec4(1.0f,1.0f,1.0f,1.0f);
    light_one.ambient_strength = 0.5f;
    light_one.diffuse_strength = 0.5f;
    light_one.specular_strength = 0.15f;
    light_one.constant = 0.8f;
    light_one.linear = 0.025f;
    light_one.quadratic = 0.0006f;

    Light light_two;
    light_two.light_position = light_pos_two_M;
    light_two.light_color = vec4(1.0f,1.0f,1.0f,1.0f);
    light_two.ambient_strength = 0.0f;
    light_two.diffuse_strength = 0.80f;
    light_two.specular_strength = 0.15f;
    light_two.constant = 0.3f;
    light_two.linear = 0.025f;
    light_two.quadratic = 0.0050f;

    vec4 color_one = calculate_light(light_one, normal_V, position_M, light_dir_one_V);
    vec4 color_two = calculate_light(light_two, normal_V, position_M, light_dir_two_V);

    pixelColor = color_one + color_two;
}
