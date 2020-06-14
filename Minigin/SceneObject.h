#pragma once
namespace minigin
{
	class SceneObject
	{
	public:
		//rule of 5
		SceneObject();
		virtual ~SceneObject() = default;

		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

		//functions
		virtual void Update() = 0;
		virtual void Render() const = 0;

		void DestroyObject();
		bool Destroy() const { return m_Delete; }

		void SetVisibility(bool value);

	protected:
		//datamember
		bool m_Visible;
	private:
		//datamember
		bool m_Delete;
	};
}
