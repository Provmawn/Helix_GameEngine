#ifndef CAMERA2D_H
#define CAMERA2D_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace helix
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void Update();

		void Init(int width, int height);

		void SetPosition(const glm::vec2 &position) { m_position = position; m_update = true; }
		void SetScale(float scale) { m_scale = scale; m_update = true; }

		float GetScale() { return m_scale; }
		glm::vec2 GetPosition() { return m_position; }
		glm::mat4 GetCameraMatrix() { return m_camera_matrix; }
		glm::vec2 ConvertScreenToWorld(glm::vec2 screen_coords);

	private:
		bool m_update{};
		int m_width{};
		int m_height{};
		float m_scale{};
		glm::vec2 m_position{};
		glm::mat4 m_camera_matrix{};
		glm::mat4 m_ortho_matrix{};
	};
}
#endif
