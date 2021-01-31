#include "Camera2D.h"

namespace helix
{
	Camera2D::Camera2D()
		: m_update{ true }
		, m_width{ 800 }
		, m_height{ 600 }
		, m_scale{ 1.0f }
		, m_position{ 0.0f, 0.0f }
		, m_camera_matrix{ 1.0f }
		, m_ortho_matrix{ 1.0f }
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::Update()
	{
		if (m_update)
		{
			glm::vec3 translate(-m_position.x + m_width / 2, -m_position.y + m_height / 2, 0.0f);
			m_camera_matrix = glm::translate(m_ortho_matrix, translate);
			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_camera_matrix = glm::scale(glm::mat4(1.0f), scale) * m_camera_matrix;
			//translate = glm::vec3(m_width/2, m_height/2, 0.0f);
			//m_camera_matrix = glm::translate(m_camera_matrix, translate);
			m_update = false;
		}
	}

	void Camera2D::Init(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_ortho_matrix = glm::ortho(0.0f, static_cast<float>(m_width), 0.0f, static_cast<float>(m_height));
	}
	glm::vec2 Camera2D::ConvertScreenToWorld(glm::vec2 screen_coords)
	{
		// center at 0
		screen_coords -= glm::vec2(m_width / 2, m_height / 2);
		screen_coords.y = -screen_coords.y;
		// fix the scaling
		screen_coords /= m_scale;
		// translate to camera coordinates
		screen_coords += m_position;
		return screen_coords;
	}
}
