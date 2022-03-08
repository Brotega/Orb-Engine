#version 460 core

// TODO: In the future, move all lighting into a different script that can be included here,
// and create a new ShaderLit class that joins them together when creating shaders 

/*Lighting*/
#define MAX_POINT_LIGHTS 4

struct DirectionalLight // 80
{
	vec3 Direction; // 16, 0
	vec4 Ambient;   // 16, 16
	vec4 Diffuse;   // 16, 32
	vec4 Specular;  // 16, 48
	bool IsEnabled; //  1, 64
	// pad 15, 65 -> 80
};

struct SpotLight // 112
{
	vec3 Position;    // 16, 0
	vec3 Direction;   // 16, 16

	vec4 Ambient;     // 16, 32
	vec4 Diffuse;     // 16, 48
	vec4 Specular;    // 16, 64

	float InnerAngle; // 4, 80
	float OuterAngle; // 4, 84

	float Constant;   // 4, 88
	float Linear;     // 4, 92
	float Quadratic;  // 4, 96
	bool IsEnabled;   // 1, 100
	// pad 11, 101 -> 112
};

struct PointLight // 80
{
	vec3 Position;   // 16, 0

	vec4 Ambient;    // 16, 16
	vec4 Diffuse;    // 16, 32
	vec4 Specular;   // 16, 48

	float Constant;  // 4, 64
	float Linear;    // 4, 68
	float Quadratic; // 4, 72
	bool IsEnabled;  // 1, 76
	// pad 3, 77
};
/*End of Lighting*/

out vec4 FragColor;
  
in vec3 WorldPos;
in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec2 UV;
in vec3 UVW;

in vec3 CameraPosWS;
in float ZNear;
in float ZFar;

struct MaterialProperty
{
	sampler2D Diffuse;
	sampler2D Specular;
	sampler2D Environment;
	float Shininess;
}; uniform MaterialProperty materialProperty;

layout (std140, binding = 1) uniform Lighting
{
	DirectionalLight directionalLight; // 80, 0
	SpotLight spotLight; // 112, 64
	PointLight pointLights[MAX_POINT_LIGHTS]; // 80 * MAX_POINT_LIGHTS, 176
};

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec2 UV);
vec3 CalculatePointLight(PointLight light, vec3 worldPos, vec3 normal, vec3 viewDir, vec2 UV);
vec3 CalculateSpotLight(SpotLight light, vec3 worldPos, vec3 normal, vec3 viewDir, vec2 UV);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(CameraPosWS - WorldPos);

    vec3 res = CalculateDirectionalLight(directionalLight, norm, viewDir, UV);

    for(int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        res += CalculatePointLight(pointLights[i], WorldPos, norm, viewDir, UV);
    }

    res += CalculateSpotLight(spotLight, WorldPos, norm, viewDir, UV);

    FragColor = vec4(res, 1.0f);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec2 UV)
{
	if(light.IsEnabled == false) return vec3(0.0f);

	vec3 lightDir = normalize(-light.Direction);

	float diff = max(dot(normal, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), materialProperty.Shininess);

	vec3 ambient = vec3(light.Ambient) * vec3(texture(materialProperty.Diffuse, UV));
	vec3 diffuse = vec3(light.Diffuse) * diff * vec3(texture(materialProperty.Diffuse, UV));
	vec3 specular = vec3(light.Specular) * spec * vec3(texture(materialProperty.Specular, UV));

	return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 worldPos, vec3 normal, vec3 viewDir, vec2 UV)
{
	if(light.IsEnabled == false) return vec3(0.0f);

	vec3 lightDir = normalize(light.Position - worldPos);

	float diff = max(dot(normal, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), materialProperty.Shininess);

	float dist = length(light.Position - worldPos);
	float attenuation = 1.0f / (light.Constant + light.Linear * dist + light.Quadratic * dist * dist);

	vec3 ambient = vec3(light.Ambient) * vec3(texture(materialProperty.Diffuse, UV));
	vec3 diffuse = vec3(light.Diffuse) * diff * vec3(texture(materialProperty.Diffuse, UV));
	vec3 specular = vec3(light.Specular) * spec * vec3(texture(materialProperty.Specular, UV));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 worldPos, vec3 normal, vec3 viewDir, vec2 UV)
{
	if(light.IsEnabled == false) return vec3(0.0f);

    vec3 lightDir = normalize(light.Position - worldPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialProperty.Shininess);

    float dist = length(light.Position - worldPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist));    

    float theta = dot(lightDir, normalize(-light.Direction)); 
    float epsilon = light.InnerAngle - light.OuterAngle;
    float intensity = clamp((theta - light.OuterAngle) / epsilon, 0.0, 1.0);

    vec3 ambient = vec3(light.Ambient) * vec3(texture(materialProperty.Diffuse, UV));
    vec3 diffuse = vec3(light.Diffuse) * diff * vec3(texture(materialProperty.Diffuse, UV));
    vec3 specular = vec3(light.Specular) * spec * vec3(texture(materialProperty.Specular, UV));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return ambient + diffuse + specular;
}