#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Random.h"

class GameLayer : public Walnut::Layer
{
public:
	GameLayer()
	{
		m_ImageData = new uint32_t[960 * 540];

		m_Image = std::make_shared<Walnut::Image>(960, 540, Walnut::ImageFormat::RGBA, m_ImageData);
	}

	virtual void OnUpdate(float ts) override
	{
		for (uint32_t i = 0; i < m_Image->GetWidth() * m_Image->GetHeight(); i++)
		{
			m_ImageData[i] = Walnut::Random::UInt();
		}

		m_Image->SetData(m_ImageData);
	}

	virtual void OnUIRender() override
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("Game");

		uint32_t scaledWindowWidth = (uint32_t)ImGui::GetContentRegionAvail().x / 3;
		uint32_t scaledWindowHeight = (uint32_t)ImGui::GetContentRegionAvail().y / 3;

		ImGui::Image(m_Image->GetDescriptorSet(), ImVec2((float)m_Image->GetWidth() * m_ImageScale, (float)m_Image->GetHeight() * m_ImageScale));

		if (scaledWindowWidth != m_Image->GetWidth() || scaledWindowHeight != m_Image->GetHeight())
		{
			m_Image = std::make_shared<Walnut::Image>(scaledWindowWidth, scaledWindowHeight, Walnut::ImageFormat::RGBA);
			delete[] m_ImageData;
			m_ImageData = new uint32_t[scaledWindowWidth * scaledWindowHeight];
		}

		ImGui::End();

		ImGui::PopStyleVar();
	}

private:
	std::shared_ptr<Walnut::Image> m_Image;
	uint32_t m_ImageScale = 3;
	uint32_t* m_ImageData = nullptr;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Genesis";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<GameLayer>();
	return app;
}