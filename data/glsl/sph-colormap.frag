
uniform vec2 tex_a[8];
uniform vec2 tex_d[8];

uniform sampler2D image[8];
uniform float     alpha[8];

//------------------------------------------------------------------------------

vec4 texture(sampler2D s, vec2 t)
{
    vec4 p = texture2D(s, t);
    vec3 b = floor(p.rgb * 65535.0);
    vec3 c = 2.0 * mix(p.rgb, p.rgb - 1.0, step(32767.0, b));
    return vec4(c, p.a);
}

// Some hardware disallows accessing a sampler array element using a computed
// index. So, we need to unroll these.

vec4 img0(vec2 t)
{
    vec4 c = texture(image[0], t);
    return c;
}

vec4 img1(vec2 t)
{
    vec4 c = texture(image[1], (t - tex_a[1]) / (tex_d[1] - tex_a[1]));
    return vec4(c.rgb, c.a * alpha[1]);
}

vec4 img2(vec2 t)
{
    vec4 c = texture(image[2], (t - tex_a[2]) / (tex_d[2] - tex_a[2]));
    return vec4(c.rgb, c.a * alpha[2]);
}

vec4 img3(vec2 t)
{
    vec4 c = texture(image[3], (t - tex_a[3]) / (tex_d[3] - tex_a[3]));
    return vec4(c.rgb, c.a * alpha[3]);
}

vec4 img4(vec2 t)
{
    vec4 c = texture(image[4], (t - tex_a[4]) / (tex_d[4] - tex_a[4]));
    return vec4(c.rgb, c.a * alpha[4]);
}

vec4 img5(vec2 t)
{
    vec4 c = texture(image[5], (t - tex_a[5]) / (tex_d[5] - tex_a[5]));
    return vec4(c.rgb, c.a * alpha[5]);
}

vec4 img6(vec2 t)
{
    vec4 c = texture(image[6], (t - tex_a[6]) / (tex_d[6] - tex_a[6]));
    return vec4(c.rgb, c.a * alpha[6]);
}

vec4 img7(vec2 t)
{
    vec4 c = texture(image[7], (t - tex_a[7]) / (tex_d[7] - tex_a[7]));
    return vec4(c.rgb, c.a * alpha[7]);
}

//------------------------------------------------------------------------------

vec4 blend(vec4 a, vec4 b)
{
    return vec4(mix(b.rgb, a.rgb, a.a), 1.0);
}

vec4 sample(vec2 t)
{
    vec4 c = vec4(0.0);

    c = blend(img0(t), c);
    c = blend(img1(t), c);
    c = blend(img2(t), c);
    c = blend(img3(t), c);
    c = blend(img4(t), c);
    c = blend(img5(t), c);
    c = blend(img6(t), c);
    c = blend(img7(t), c);

    return c;
}

float peak(float k, float c)
{
    return max(0.0, 1.0 - abs(k - c) * 5.0);
}

vec3 colormap(float k)
{
    return peak(k, 0.0) * vec3(1.0, 0.0, 1.0) +
           peak(k, 0.2) * vec3(0.0, 0.0, 1.0) +
           peak(k, 0.4) * vec3(0.0, 1.0, 1.0) +
           peak(k, 0.6) * vec3(1.0, 1.0, 0.0) +
           peak(k, 0.8) * vec3(1.0, 0.0, 0.0) +
           peak(k, 1.0) * vec3(1.0, 1.0, 1.0);
}

void main()
{
    float k = (3.2768 * sample(gl_TexCoord[0].xy).r + 1.0) / 2.0;
    gl_FragColor = vec4(colormap(k), 1.0);
}
