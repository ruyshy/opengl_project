#pragma once

#ifndef GAME_H_
#define GAME_H_

class Game
{
public:
	Game() = delete;
	Game(MainWindow* mainWindow);
	~Game();

	void initialize();
	void Render() const;
	void Update() const;

private:
	unique_ptr<Shader> mpCheckboardShader;
	shared_ptr<Shader> mpTextureShader;
	shared_ptr<Shader> mpNormalShader;
	unique_ptr<VertexBufferObject2D> mpCheckboard;

	shared_ptr<Camera> mpCamera;
	shared_ptr<SceneBase> mpScene;

private:
	MainWindow* mpMainWindow;

};

#endif // !GAME_H_
