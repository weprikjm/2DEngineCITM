#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1FileSystem.h"
#include "j1Map.h"



j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	//App->map->Load("mario.tmx");
	//App->map->Load("hello2.tmx");
	App->map->Load("iso.tmx");
	//LoadImg("data/textures/test.png");
	LoadMusic("data/audio/music/music_sadpiano.ogg");
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// TODO 5: Call load / save methods when pressing l/s
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveWarning();

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadWarning();

	if (App->input->GetKey(48) == KEY_REPEAT)
		RaiseVolume();

	if (App->input->GetKey(56) == KEY_REPEAT)
		LowerVolume();

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 10;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 10;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 10;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 10;

	App->map->Draw();
	/*
	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
		App->map->GetMapNode()->width, App->map->GetMapNode()->height,
		App->map->GetMapNode()->tileWidth, App->map->GetMapNode()->tileHeigth,
		App->map->GetMapNode()->tiles.count(),
		map_coordinates.x, map_coordinates.y);

	App->win->SetTitle(title.GetString());
	*/


	//App->render->Blit(img, 0, 0);
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool j1Scene::LoadImg(const char* path)
{
	bool ret = false;

	PHYSFS_sint64* size = NULL;
	char* buff = NULL;
	SDL_RWops* temp = App->fs->LoadFile(path, buff, size);
	SDL_Surface* surf = App->tex->Load_image(temp);

	img = App->tex->LoadSurface(surf);//TO CHANGE TO A DATA STRUCTURE

	if (img != NULL)
		ret = true;

	return ret;
}

bool j1Scene::LoadMusic(const char* path)
{
	bool ret = false;
	PHYSFS_sint64* size = NULL;
	char* buff = NULL;
	SDL_RWops* temp = App->fs->LoadFile(path, buff, size);
	ret = App->audio->PlayMusic(temp, path);
	delete size;
	return ret;
}

bool j1Scene::RaiseVolume()
{
	App->audio->SetVolumeMusic(App->audio->SetVolume(App->audio->getVolume() + App->audio->getVolumeIncrement()));
	return true;
}


bool j1Scene::LowerVolume()
{
	App->audio->SetVolumeMusic(App->audio->SetVolume(App->audio->getVolume() - App->audio->getVolumeIncrement()));
	return true;
}