#version 330

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec4 position_M; // Polozenie wierzcholka w przestrzeni swiata
in vec4 normal_V; // Wektor normalny w przestrzeni widoku
in vec4 eye_dir_V; // Wektor do obserwatora w przestrzeni widoku
in vec4 light_dir_one_V; // Wektor do swiatla 1 w przestrzeni widoku
in vec4 light_dir_two_V; // Wektor do swiatla 1 w przestrzeni widoku
in vec4 light_pos_one_M; // Polozenie zrodla swiatla w przestrzeni swiata
in vec4 light_pos_two_M; // Polozenie zrodla swiatla w przestrzeni swiatla
in vec2 tex_coord; // Wspolrzedne teksturowania

uniform sampler2D tex;
uniform float material_ambient_strength;
uniform float material_diffuse_strength;
uniform float material_specular_strength;
uniform float material_shininess;

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

vec4 calculate_light(Light light, vec4 normal, vec4 frag_pos, vec4 light_dir, vec4 eye_dir){
    vec4 color = texture(tex,tex_coord);

    // Ambient
    vec4 ambient = light.ambient_strength * material_ambient_strength * color;

    // Diffuse
    float nor_ld  = clamp(dot(normal,light_dir),0,1); // Wektor normalny dot wektor do swiatla
    vec4 diffuse = light.diffuse_strength * material_diffuse_strength * nor_ld * color;

    // Specular
    vec4 reflected = normalize(reflect(-light_dir,normal));
    float spec = pow(clamp(dot(eye_dir,reflected),0,1),material_shininess);
    vec4 specular = light.specular_strength * material_specular_strength * spec * light.light_color;

    // Tlumienie
    float dist = distance(light.light_position,frag_pos);
    float att = 1.0f / (light.constant + light.linear*dist + light.quadratic*(dist*dist));
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
    light_one.specular_strength = 0.005f;
    light_one.constant = 0.25f;
    light_one.linear = 0.3f;
    light_one.quadratic = 0.06f;

    Light light_two;
    light_two.light_position = light_pos_two_M;
    light_two.light_color = vec4(1.0f,1.0f,1.0f,1.0f);
    light_two.ambient_strength = 0.4f;
    light_two.diffuse_strength = 0.40f;
    light_two.specular_strength = 2.00f;
    light_two.constant = 0.3f;
    light_two.linear = 0.025f;
    light_two.quadratic = 0.0050f;

    vec4 color_one = calculate_light(light_one, normal_V, position_M, light_dir_one_V, eye_dir_V);
    vec4 color_two = calculate_light(light_two, normal_V, position_M, light_dir_two_V, eye_dir_V);

    pixelColor = color_one + color_two;
}
