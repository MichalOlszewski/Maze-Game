#version 330

uniform sampler2D textureMap0;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 ic; 
in vec4 n;
in vec4 l1;
in vec4 l2;
in vec4 v;
in vec2 iTexCoord0;



void main(void) {

	//Znormalizowane interpolowane wektory
	vec4 ml1 = normalize(l1);
	vec4 ml2 = normalize(l2);
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);
	//Wektor odbity
	vec4 mr1 = reflect(-ml1, mn);
	vec4 mr2 = reflect(-ml2, mn);

	//Parametry powierzchni
	vec4 kd = texture(textureMap0, iTexCoord0);
	vec4 ks = kd;
	float light1 = dot(mn, ml1);
	float light2 = dot(mn, ml2);
	if(light1 < 0.0f) light1 = 0.0f;
	if(light2 < 0.0f) light2 = 0.0f;
	if((light1 + light2) <= 0.0f) 
	{
	light1 = 0.05f;
	light2 = 0.05f;
	}

	//Obliczenie modelu oświetlenia
	float nl = clamp(light1+light2, 0, 1);
	//float rv = pow(clamp(dot(mr, mv), 0, 1), 50);
	pixelColor= vec4(kd.rgb * nl, kd.a); 
}
