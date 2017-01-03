/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include "SDL2/SDL.h"
#include <stdio.h>
#include <string>
#include <cmath>
//#include "mini3d.c"
#include "tiny3D.h"

#define PI 3.141592653
#define angle_to_radian(X) ((X)/180*PI)
#define radian_to_angle(X) ((X)/PI*180)

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
//SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init(int width, int height, const char *title)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

//				//Initialize PNG loading
//				int imgFlags = IMG_INIT_PNG;
//				if( !( IMG_Init( imgFlags ) & imgFlags ) )
//				{
//					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
//					success = false;
//				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}

//SDL_Texture* loadTexture( std::string path )
//{
//	//The final texture
//	SDL_Texture* newTexture = NULL;
//
//	//Load image at specified path
//	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
//	if( loadedSurface == NULL )
//	{
//		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
//	}
//	else
//	{
//		//Create texture from surface pixels
//        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
//		if( newTexture == NULL )
//		{
//			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface( loadedSurface );
//	}
//
//	return newTexture;
//}

//=====================================================================
// 主程序
//=====================================================================
vertex_t ground_mesh[6] = {
    {{-0.5f,  0.0f, -0.5f, 1.0f}, {0.0f,  1.0f},{ 0.2f, 1.0f, 1.0f }, 1 , { 0.0f, 1.0f,  0.0f,0.0f}},
    {{-0.5f,  0.0f,  0.5f, 1.0f},  {0.0f,  0.0f},{ 0.2f, 1.0f, 1.0f }, 1 , { 0.0f, 1.0f,  0.0f,0.0f}},
    {{0.5f,  0.0f,  0.5f, 1.0f},  {1.0f,  0.0f},{ 0.2f, 1.0f, 1.0f }, 1 ,  { 0.0f,1.0f,  0.0f,0.0f}},
    {{0.5f,  0.0f,  0.5f, 1.0f},  {1.0f,  0.0f}, { 0.2f, 1.0f, 1.0f }, 1 , { 0.0f,1.0f,  0.0f,0.0f}},
    {{0.5f,  0.0f, -0.5f, 1.0f},  {1.0f,  1.0f},{ 0.2f, 1.0f, 1.0f }, 1 ,  { 0.0f,1.0f,  0.0f,0.0f}},
    {{-0.5f,  0.0f, -0.5f, 1.0f},  {0.0f,  1.0f},{ 0.2f, 1.0f, 1.0f }, 1 , { 0.0f, 1.0f,  0.0f,0.0f}}
};

vertex_t box_mesh[36] = {
//    { {  -1, -1, -1, 1 }, { 0, 0 }, { 1.0f, 0.2f, 0.2f }, 1 , { -1, -1, -1, 0}},
//    { { 1, -1, -1, 1 }, { 0, 1 }, { 0.2f, 1.0f, 0.2f }, 1 ,{ 1, -1, -1, 0 }},
//    { { -1,  1, -1, 1 }, { 1, 1 }, { 0.2f, 0.2f, 1.0f }, 1 ,{ -1,  1, -1, 0 }},
//    { {  1,  1, -1, 1 }, { 1, 0 }, { 1.0f, 0.2f, 1.0f }, 1 ,{  1,  1, -1, 0 }},
//    { { -1, -1,  1, 1 }, { 0, 0 }, { 1.0f, 1.0f, 0.2f }, 1 ,{ -1, -1,  1, 0 }},
//    { { 1, -1,  1, 1 }, { 0, 1 }, { 0.2f, 1.0f, 1.0f }, 1 ,{ 1, -1,  1, 0 }},
//    { { -1,  1,  1, 1 }, { 1, 1 }, { 1.0f, 0.3f, 0.3f }, 1 ,{ -1,  1,  1, 0 }},
//    { { 1,  1,  1, 1 }, { 1, 0 }, { 0.2f, 1.0f, 0.3f }, 1 ,{ 1,  1,  1, 0 }},
    
    // Positions                  // Texture Coords  //color           //rhw // Normals
    {{-0.5f, -0.5f, -0.5f, 1.0f},{ 0.0f,  0.0f},{ 1.0f, 0.2f, 0.2f }, 1 , { 0.0f,  0.0f,-1.0f,0.0f}},
    {{-0.5f,  0.5f, -0.5f, 1.0f},{ 0.0f,  1.0f},{ 1.0f, 0.2f, 0.2f }, 1 , { 0.0f,  0.0f,-1.0f,0.0f}},
    {{0.5f,  0.5f, -0.5f, 1.0f}, {1.0f,  1.0f}, { 1.0f, 0.2f, 0.2f }, 1 , {0.0f,  0.0f,-1.0f ,0.0f}},
    {{0.5f,  0.5f, -0.5f, 1.0f}, { 1.0f,  1.0f}, { 1.0f, 0.2f, 0.2f }, 1 , {0.0f,  0.0f,-1.0f,0.0f}},
    {{0.5f, -0.5f, -0.5f, 1.0f}, {1.0f,  0.0f}, { 1.0f, 0.2f, 0.2f }, 1 , {0.0f,  0.0f,-1.0f ,0.0f}},
    {{-0.5f, -0.5f, -0.5f, 1.0f},{ 0.0f,  0.0f},{ 1.0f, 0.2f, 0.2f }, 1 , { 0.0f,  0.0f,-1.0f,0.0f}},
    
    {{-0.5f, -0.5f,  0.5f, 1.0f},{ 0.0f,  0.0f},{ 0.2f, 1.0f, 0.2f }, 1 , { 0.0f,  0.0f, 1.0f,0.0f}},
    {{0.5f, -0.5f,  0.5f, 1.0f},{ 1.0f,  0.0f}, { 0.2f, 1.0f, 0.2f }, 1 , {0.0f,  0.0f,  1.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f, 1.0f},{ 1.0f,  1.0f}, { 0.2f, 1.0f, 0.2f }, 1 , {0.0f,  0.0f,  1.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f, 1.0f},{ 1.0f,  1.0f}, { 0.2f, 1.0f, 0.2f }, 1 , {0.0f,  0.0f,  1.0f,0.0f}},
    {{-0.5f,  0.5f,  0.5f, 1.0f},{ 0.0f,  1.0f},{ 0.2f, 1.0f, 0.2f }, 1 , { 0.0f,  0.0f,  1.0f,0.0f}},
    {{-0.5f, -0.5f,  0.5f, 1.0f},{ 0.0f,  0.0f},{ 0.2f, 1.0f, 0.2f }, 1 , { 0.0f,  0.0f,  1.0f,0.0f}},
    
    {{-0.5f,  0.5f,  0.5f, 1.0f}, { 1.0f,  0.0f},{ 0.2f, 0.2f, 1.0f}, 1 , {-1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f,  0.5f, -0.5f, 1.0f},{ 1.0f,  1.0f},{ 0.2f, 0.2f, 1.0f }, 1 , { -1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f, -0.5f, 1.0f},{ 0.0f,  1.0f},{ 0.2f, 0.2f, 1.0f }, 1 , { -1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f, -0.5f, 1.0f},{ 0.0f,  1.0f},{ 0.2f, 0.2f, 1.0f }, 1 , { -1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f,  0.5f, 1.0f},{ 0.0f,  0.0f},{ 0.2f, 0.2f, 1.0f}, 1 , { -1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f,  0.5f,  0.5f,1.0f},{ 1.0f,  0.0f},{ 0.2f, 0.2f, 1.0f }, 1 , { -1.0f,  0.0f,  0.0f,0.0f}},
    
    {{0.5f,  0.5f,  0.5f,1.0f}, { 1.0f,  0.0f}, { 1.0f, 0.2f, 1.0f }, 1 , {1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f,  0.5f,1.0f},{ 0.0f,  0.0f}, { 1.0f, 0.2f, 1.0f }, 1 , { 1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f, -0.5f,1.0f},{ 0.0f,  1.0f}, { 1.0f, 0.2f, 1.0f }, 1 , { 1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f, -0.5f,1.0f},{ 0.0f,  1.0f}, { 1.0f, 0.2f, 1.0f }, 1 , { 1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f, -0.5f,1.0f},{ 1.0f,  1.0f}, { 1.0f, 0.2f, 1.0f }, 1 , { 1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f,1.0f},{ 1.0f,  0.0f}, { 1.0f, 0.2f, 1.0f }, 1 , { 1.0f,  0.0f,  0.0f,0.0f}},
    
    {{-0.5f, -0.5f, -0.5f,1.0f},{  0.0f,  1.0f},{ 1.0f, 1.0f, 0.2f }, 1 , {  0.0f, -1.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f, -0.5f,1.0f}, { 1.0f,  1.0f},{ 1.0f, 1.0f, 0.2f }, 1 ,  { 0.0f, -1.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f,  0.5f,1.0f}, { 1.0f,  0.0f}, { 1.0f, 1.0f, 0.2f }, 1 , { 0.0f, -1.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f,  0.5f,1.0f}, { 1.0f,  0.0f},{ 1.0f, 1.0f, 0.2f }, 1 ,  { 0.0f, -1.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f,  0.5f,1.0f},{ 0.0f,  0.0f},{ 1.0f, 1.0f, 0.2f }, 1 , {  0.0f, -1.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f, -0.5f,1.0f},{ 0.0f,  1.0f},{ 1.0f, 1.0f, 0.2f }, 1 , {  0.0f, -1.0f,  0.0f,0.0f}},

    {{-0.5f,  0.5f, -0.5f, 1.0f}, {0.0f,  1.0f},{ 0.2f, 1.0f, 1.0f }, 1 , { 0.0f, 1.0f,  0.0f,0.0f}},
    {{-0.5f,  0.5f,  0.5f, 1.0f},  {0.0f,  0.0f},{ 0.2f, 1.0f, 1.0f }, 1 , { 0.0f, 1.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f, 1.0f},  {1.0f,  0.0f},{ 0.2f, 1.0f, 1.0f }, 1 ,  { 0.0f,1.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f, 1.0f},  {1.0f,  0.0f}, { 0.2f, 1.0f, 1.0f }, 1 , { 0.0f,1.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f, -0.5f, 1.0f},  {1.0f,  1.0f},{ 0.2f, 1.0f, 1.0f }, 1 ,  { 0.0f,1.0f,  0.0f,0.0f}},
    {{-0.5f,  0.5f, -0.5f, 1.0f},  {0.0f,  1.0f},{ 0.2f, 1.0f, 1.0f }, 1 , { 0.0f, 1.0f,  0.0f,0.0f}}
};

typedef struct {
    vertex_t *mesh;
    int mesh_num;
    int material_id;
    int texture_id;
    bool shadow;
    
    bool dirty;
    point_t pos;
    vector_t scale;
    
    vector_t axis;
    float theta;
    
    matrix_t matrix;
} object_t;
#define MAX_NUM_OBJECT 100
object_t objects[MAX_NUM_OBJECT];
int object_count = 0;

typedef struct {
    IUINT32 **texture;           // mipmap纹理
    bool use_mipmap;
    int width;              // 纹理宽度
    int height;             // 纹理高度
} texture_t;
#define MAX_NUM_TEXTURE 100
texture_t textures[MAX_NUM_TEXTURE];
int texture_count = 0;

int generate_mipmaps(texture_t *texture, float gamma) {
    IUINT32 **mipmaps = NULL;
    int num_mip_levels = logbase2ofx(texture->width) + 1;
    mipmaps = (IUINT32**)malloc(num_mip_levels * sizeof(IUINT32*));
    mipmaps[0] = texture->texture[0];
    int mip_width = texture->width;
    int mip_height = texture->height;
    for(int mip_level = 1; mip_level < num_mip_levels; mip_level++) {
        mip_width = mip_width >> 1;
        mip_height = mip_height >> 1;
        mipmaps[mip_level] = (IUINT32*)malloc(mip_width * mip_height * sizeof(IUINT32));
        IUINT32 *src_buffer = mipmaps[mip_level-1];
        IUINT32 *dest_buffer = mipmaps[mip_level];
        for(int x = 0; x < mip_width; x++)
        {
            for(int y = 0; y < mip_height; y++)
            {
                float r0, g0, b0,
                r1, g1, b1,
                r2, g2, b2,
                r3, g3, b3;
                int r_avg, g_avg, b_avg;
                
                IUINT32 c = src_buffer[(x*2+0) + (y*2+0)*mip_width*2];
                b0 = c & 0xff;
                g0 = (c >> 8) & 0xff;
                r0 = (c >> 16) & 0xff;
                
                c = src_buffer[(x*2+1) + (y*2+0)*mip_width*2];
                b1 = c & 0xff;
                g1 = (c >> 8) & 0xff;
                r1 = (c >> 16) & 0xff;
                
                c = src_buffer[(x*2+0) + (y*2+1)*mip_width*2];
                b2 = c & 0xff;
                g2 = (c >> 8) & 0xff;
                r2 = (c >> 16) & 0xff;
                
                c = src_buffer[(x*2+1) + (y*2+1)*mip_width*2];
                b3 = c & 0xff;
                g3 = (c >> 8) & 0xff;
                r3 = (c >> 16) & 0xff;
                
                r_avg = (IUINT32)(0.5f + gamma*(r0+r1+r2+r3)/4);
                g_avg = (IUINT32)(0.5f + gamma*(g0+g1+g2+g3)/4);
                b_avg = (IUINT32)(0.5f + gamma*(b0+b1+b2+b3)/4);
                
                int R = CMID(r_avg, 0, 255);
                int G = CMID(g_avg, 0, 255);
                int B = CMID(b_avg, 0, 255);
                
                dest_buffer[x+y*mip_width] = (R << 16) | (G << 8) | B;
            }
        }
    }
    texture->texture = mipmaps;
    return num_mip_levels;
}

void init_texture() {
    int width = 256;
    int height = 256;
    IUINT32 *bits = (IUINT32*)malloc(sizeof(IUINT32) * width * height);
    int i, j;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            int x = i / 32, y = j / 32;
            bits[j*width+i] = ((x + y) & 1)? 0xffffff : 0x3fbcef;
        }
    }
    texture_t *texture = &textures[0];
    texture->texture = &bits;
    texture->height = height;
    texture->width = width;
    texture->use_mipmap = true;
    generate_mipmaps(texture, 1.01);
}

void draw_object(device_t *device, object_t *objects, int obj_cnt) {
    for(int i = 0; i < obj_cnt; i++)
    {
        object_t *object = &objects[i];
        if(object->dirty == true) {
            matrix_set_rotate_translate_scale(&object->matrix, &object->axis, object->theta, &object->pos, &object->scale);
            object->dirty = false;
        }
        // 切换纹理
        texture_t *texture = &textures[object->texture_id];
        device_set_texture(device, texture->texture, texture->width, texture->height, false);
        device->material = materials[object->material_id];
        device->transform.world = object->matrix;
        transform_update(&device->transform);
        vertex_t *mesh = object->mesh;
        for(int i = 0; i < object->mesh_num; i+=3)
            clip_polys(device, &mesh[i], &mesh[i+1], &mesh[i+2]);
    }
}

void draw_shadow(device_t *device, object_t *objects, int obj_cnt) {
    for(int i = 0; i < pointlight_cnt; i++) {
        vector_t pl = pointLights[i].pos;
        for(int j = 0; j < obj_cnt; j++)
        {
            object_t *object = &objects[j];
            if(object->shadow == false)
                continue;
            vertex_t *mesh = object->mesh;
            vertex_t shadow_mesh[object->mesh_num];
            for(int k = 0; k < object->mesh_num; k++) {
                shadow_mesh[k] = mesh[k];
                vector_t vi;
                matrix_apply(&vi, &shadow_mesh[k].pos, &object->matrix);
                
                float t0 = -pl.y / (vi.y - pl.y);
                shadow_mesh[k].pos.x = pl.x + t0 * (vi.x - pl.x);
                shadow_mesh[k].pos.y = 0.02f;
                shadow_mesh[k].pos.z = pl.z + t0 * (vi.z - pl.z);
                shadow_mesh[k].pos.w = 1.0f;
                
                shadow_mesh[k].normal = {0.0f, 1.0f, 0.0f, 0.0f};
            }
            for(int k = 0; k < object->mesh_num; k+=3)
                clip_polys(device, &shadow_mesh[k], &shadow_mesh[k+1], &shadow_mesh[k+2], true);
        }
    }
}

void camera_at_zero(device_t *device, const point_t *eye, const vector_t *at, const vector_t *up) {
    matrix_set_lookat(&device->transform.view, eye, at, up);
    transform_update(&device->transform);
}



int screen_keys[512];	// 当前键盘按下状态
float deltaTime = 0.0f;
Uint32 lastFrame = 0;

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init(SCREEN_WIDTH, SCREEN_HEIGHT, "lixuefeng") )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            device_t device;
            int states[] = { RENDER_STATE_TEXTURE, RENDER_STATE_COLOR, RENDER_STATE_WIREFRAME };
            int indicator = 0;
            int kbhit = 0;
            
            float c_yaw = 0.0f;
            float c_pitch = 0.0f;
            vector_t c_pos = {0.0f, 1.0f, -3.0f, 1.0f};
            vector_t c_front = {0.0f, 0.0f, 1.0f, 0.0f};
            vector_t c_up = {0.0f, 1.0f, 0.0f, 0.0f};
            vector_t c_right = {1.0f, 0.0f, 0.0f, 0.0f};
            vector_t c_worldup = {0.0f, 1.0f, 0.0f, 0.0f};
            float c_movementspeed = 2.0f;
            float c_mouse_sensitivity = 0.25f;
            float c_zoom = 45.0f;
            bool c_dirty = true;
            
            memset(screen_keys, 0, sizeof(int) * 512);
            device_init(&device, SCREEN_WIDTH, SCREEN_HEIGHT, 3.1415926 * 0.5f, 2.0f, 500.0f, NULL);
            
            init_texture();
            device.render_state = RENDER_STATE_TEXTURE;
            
            materials[0] = {0.2f, 0.2f, 0.2f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 32.0f};
            material_cnt++;
            materials[1] = {0.2f, 0.2f, 0.2f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 32.0f};
            material_cnt++;
            materials[2] = {0.2f, 0.2f, 0.2f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 32.0f};
            material_cnt++;
            materials[3] = {0.2f, 0.2f, 0.2f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 32.0f};
            material_cnt++;
            
            dirLight = {0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.05f, 0.05f, 0.05f, 0.4f, 0.4f, 0.4f, 0.5f, 0.5f, 0.5f};
//            dirLight = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
            
            int i = 0;
            for(i = 0; i < 4; i++)
            {
                pointLights[i] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
                pointlight_cnt++;
            }
            
            pointLights[0] = {{0.0f, 6.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 1.0f, 0.09f, 0.032f, {0.05f, 0.05f, 0.05f}, {0.4f, 0.4f, 0.4f}, {0.5f, 0.5f, 0.5f}};
            //pointLights[1] = {-1.0f, 6.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.09f, 0.032f, 0.05f, 0.05f, 0.05f, 0.4f, 0.4f, 0.4f, 0.5f, 0.5f, 0.5f};
            //pointLights[2] = {7.0f, -1.0f, -6.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.09f, 0.032f, 0.05f, 0.05f, 0.05f, 0.4f, 0.4f, 0.4f, 0.5f, 0.5f, 0.5f};
            //pointLights[3] = {0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.09f, 0.032f, 0.05f, 0.05f, 0.05f, 0.4f, 0.4f, 0.4f, 0.5f, 0.5f, 0.5f};

            // init object
            // ground
            object_t *ground = &objects[0];
            ground->pos = {0, 0, 0, 1};
            ground->scale = {10, 1, 10, 0};
            ground->axis = {0, 0, 0, 1};
            ground->theta = 0.0f;
            ground->mesh = ground_mesh;
            ground->mesh_num = 6;
            ground->material_id = 0;
            ground->texture_id = 0;
            ground->shadow = false;
            ground->dirty = true;
            object_count++;
            
            // box
            object_t *box = &objects[1];
            box->pos = {0, 5, 0, 1};
            box->scale = {1, 1, 1, 0};
            box->axis = {0, 5, 0, 1};
            box->theta = 0.0f;
            box->mesh = box_mesh;
            box->mesh_num = 36;
            box->material_id = 0;
            box->texture_id = 0;
            box->shadow = true;
            box->dirty = true;
            object_count++;
            
            // box
            object_t *box1 = &objects[2];
            box1->pos = {0, 6, -1, 1};
            box1->scale = {0.2, 0.2, 0.2, 0};
            box1->axis = {0, 0, 0, 1};
            box1->theta = 0.0f;
            box1->mesh = box_mesh;
            box1->mesh_num = 36;
            box1->material_id = 0;
            box1->texture_id = 0;
            box1->shadow = false;
            box1->dirty = true;
            object_count++;

            //Event handler
            SDL_Event e;
            
            //While application is running
            while( !quit )
            {
                // Set frame time
                Uint32 currentFrame = SDL_GetTicks();
                deltaTime = (currentFrame - lastFrame) * 1.0f /1000;
                lastFrame = currentFrame;
                
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //User presses a key
                    else if( e.type == SDL_KEYDOWN )
                    {
                        screen_keys[e.key.keysym.scancode] = 1;
                    }
                    else if(e.type == SDL_KEYUP)
                    {
                        screen_keys[e.key.keysym.scancode] = 0;
                    }
                    else if(e.type == SDL_MOUSEMOTION)
                    {
                        
                    }
                }
                
                if (screen_keys[SDL_SCANCODE_UP]) {
                    
                    float velocity = c_movementspeed * deltaTime;
                    vector_t temp = c_front;
                    vector_scale(&temp, velocity);
                    vector_add(&c_pos, &c_pos, &temp);
                    c_dirty = true;
                    
                    //theta += 0.04f;
                    //box->dirty = true;
                }
                if (screen_keys[SDL_SCANCODE_DOWN]) {
                    
                    float velocity = c_movementspeed * deltaTime;
                    vector_t temp = c_front;
                    vector_scale(&temp, velocity);
                    vector_sub(&c_pos, &c_pos, &temp);
                    c_dirty = true;
                    
//                    theta -= 0.04f;
//                    box->dirty = true;
                }
                if (screen_keys[SDL_SCANCODE_LEFT]) {
                    box->theta -= 0.04f;
                    box->dirty = true;
                }
                if (screen_keys[SDL_SCANCODE_RIGHT]) {
                    box->theta += 0.04f;
                    box->dirty = true;
                }
                if (screen_keys[SDL_SCANCODE_W]) {
                    float velocity = c_movementspeed * deltaTime;
                    vector_t temp = c_up;
                    vector_scale(&temp, velocity);
//                    vector_add(&c_pos, &c_pos, &temp);
//                    c_dirty = true;
                    vector_add(&box->pos, &box->pos, &temp);
                    box->dirty = true;
                }
                if (screen_keys[SDL_SCANCODE_A]) {
                    float velocity = c_movementspeed * deltaTime;
                    vector_t temp = c_right;
                    vector_scale(&temp, velocity);
                    //vector_sub(&c_pos, &c_pos, &temp);
                    //c_dirty = true;
                    vector_sub(&box->pos, &box->pos, &temp);
                    box->dirty = true;
                }
                if (screen_keys[SDL_SCANCODE_S]) {
                    float velocity = c_movementspeed * deltaTime;
                    vector_t temp = c_up;
                    vector_scale(&temp, velocity);
//                    vector_sub(&c_pos, &c_pos, &temp);
//                    c_dirty = true;
                    vector_sub(&box->pos, &box->pos, &temp);
                    box->dirty = true;
                }
                if (screen_keys[SDL_SCANCODE_D]) {
                    float velocity = c_movementspeed * deltaTime;
                    vector_t temp = c_right;
                    vector_scale(&temp, velocity);
                    //vector_add(&c_pos, &c_pos, &temp);
                    //c_dirty = true;
                    vector_add(&box->pos, &box->pos, &temp);
                    box->dirty = true;
                }
                
                if (screen_keys[SDL_SCANCODE_SPACE]) {
                    if (kbhit == 0) {
                        kbhit = 1;
                        if (++indicator >= 3) indicator = 0;
                        device.render_state = states[indicator];
                    }
                }   else {
                    kbhit = 0;
                }
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                device_clear(&device, 1);
                
                if(c_dirty == true) {
                    c_front.x = sin(angle_to_radian(c_yaw)) * cos(angle_to_radian(c_pitch));
                    c_front.y = -sin(angle_to_radian(c_pitch));
                    c_front.z = cos(angle_to_radian(c_yaw)) * cos(angle_to_radian(c_pitch));
                    vector_normalize(&c_front);
                    vector_crossproduct(&c_right, &c_worldup, &c_front);
                    vector_normalize(&c_right);
                    vector_crossproduct(&c_up, &c_front, &c_right);
                    vector_normalize(&c_up);
                    vector_t at;
                    vector_add(&at, &c_pos, &c_front);
                    camera_at_zero(&device, &c_pos, &at, &c_up);
                    
                    matrix_apply(&dirLight.vdir, &dirLight.dir, &device.transform.view);
                    for(i = 0; i < pointlight_cnt; i++)
                    {
                        matrix_apply(&pointLights[i].vpos, &pointLights[i].pos, &device.transform.view);
                    }
                    
                    c_dirty = false;
                }
                
                draw_object(&device, objects, object_count);
                
                // 渲染阴影
                draw_shadow(&device, objects, object_count);

                for(int i = 0; i < SCREEN_WIDTH; i++)
                {
                    for(int j = 0; j < SCREEN_HEIGHT; j++)
                    {
                        IUINT32 color = device.framebuffer[j][i];
                        SDL_SetRenderDrawColor( gRenderer, (0xff<<16&color)>>16, (0xff<<8&color)>>8, 0xff&color, (0xff<<24&color)>>24);
                        SDL_RenderDrawPoint( gRenderer, i, j);
                    }
                }

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

