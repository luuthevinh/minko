/*
Copyright (c) 2013 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "minko/Minko.hpp"
#include "minko/MinkoDevIL.hpp"
#include "minko/MinkoSDL.hpp"

using namespace minko;
using namespace minko::component;
using namespace minko::math;

int main(int argc, char** argv)
{
	auto canvas = Canvas::create("Minko Example - DevIL", 800, 600);

	auto sceneManager = SceneManager::create(canvas->context());
	
	// setup assets
	sceneManager->assets()->defaultOptions()->generateMipmaps(true);
	sceneManager->assets()
		->queue("texture/bricks.jpg")
		->queue("texture/bricks.png")
		->queue("texture/bricks.tga")
		->queue("texture/bricks.tif")
		->queue("texture/bricks.bmp")
		->queue("texture/bricks.psd")
		->queue("texture/bricks.dds")
		->queue("effect/Basic.effect");

	std::vector<std::string> extensions = file::DevILParser::getSupportedFileExensions();

	for each (std::string extension in extensions)
	{
		sceneManager->assets()->registerParser<file::DevILParser>(extension);
	}

	sceneManager->assets()->geometry("cube", geometry::CubeGeometry::create(sceneManager->assets()->context()));
	

	auto _ = sceneManager->assets()->complete()->connect([=](file::AssetLibrary::Ptr assets)
	{
		std::vector<minko::render::Texture::Ptr> textures;

		textures.push_back(assets->texture("texture/bricks.jpg"));
		textures.push_back(assets->texture("texture/bricks.png"));
		textures.push_back(assets->texture("texture/bricks.tga"));
		textures.push_back(assets->texture("texture/bricks.tif"));
		textures.push_back(assets->texture("texture/bricks.bmp"));
		textures.push_back(assets->texture("texture/bricks.psd"));
		textures.push_back(assets->texture("texture/bricks.dds"));
		
		auto root = scene::Node::create("root")
			->addComponent(sceneManager);

		auto camera = scene::Node::create("camera")
			->addComponent(Renderer::create(0x7f7f7fff))
			->addComponent(Transform::create(
				Matrix4x4::create()->lookAt(Vector3::zero(), Vector3::create(0.f, 0.f, 3.f))
			))
			->addComponent(PerspectiveCamera::create(800.f / 600.f, (float)PI * 0.25f, .1f, 1000.f));
		root->addChild(camera);
		
		auto mesh = scene::Node::create("mesh")
			->addComponent(Transform::create())
			->addComponent(Surface::create(
				geometry::CubeGeometry::create(sceneManager->assets()->context()),
				material::BasicMaterial::create()->diffuseMap(textures[0]),
				assets->effect("effect/Basic.effect")
			));
		root->addChild(mesh);

		auto resized = canvas->resized()->connect([&](Canvas::Ptr canvas, uint w, uint h)
		{
			camera->component<PerspectiveCamera>()->aspectRatio((float)w / (float)h);
		});

		int frames = 0;

		auto enterFrame = canvas->enterFrame()->connect([&](Canvas::Ptr canvas, uint time, uint deltaTime)
		{
			frames++;
			mesh->component<Transform>()->transform()->appendRotationY(.01f);

			sceneManager->nextFrame();

			if ((frames % 100) == 0)
			{
				int i = (frames / 100) % textures.size();

				mesh->component<Surface>()->material()->set("diffuseMap", textures[i]);
			}
		});

		canvas->run();
	});

	sceneManager->assets()->load();

	return 0;
}


