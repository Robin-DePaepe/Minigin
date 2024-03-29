#pragma once
#include "SceneObject.h"
#include "TransformComponent.h"
#include "SDL_pixels.h"

namespace minigin
{
	class Font;
	class Texture2D;

	class TextObject final : public SceneObject
	{
	public:
		//rule of 5
		explicit TextObject(const string& text, const shared_ptr<Font>& font);
		virtual ~TextObject() = default;

		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

		//functions
		void Update() override;
		void Render() const override;

		void SetText(const string& text);
		void SetPosition(float x, float y);
		void SetColor(SDL_Color color);

	private:
		//datamembers
		bool m_NeedsUpdate;
		SDL_Color m_Color;
		string m_Text;
		minigin::TransformComponent m_Transform;

		shared_ptr<Font> m_Font;
		shared_ptr<Texture2D> m_Texture;
	};
}