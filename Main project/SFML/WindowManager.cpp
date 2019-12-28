#include "WindowManager.h"


Window::Window()
{
}

Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
	Window::Setup(l_title, l_size);
	Window:IsDone();
}

Window::~Window()
{
}

void Window::BeginDraw()
{
	m_window.clear();
}

void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{

}

bool Window::IsDone()
{
	if (m_isDone == true)
		return true;
	else
		return false;
}

bool Window::IsFullScreen()
{
	if (m_isFullScreen == true)
		return true;
	else
		return false;
}

sf::Vector2u Window::GetWindowSize()
{
	m_window_size.x = m_window.getSize().x;
	m_window_size.y = m_window.getSize().y;

	return m_window_size;
}

void Window::ToggleFullScreen()
{
	if (m_isFullScreen == false)
	{
		m_window.close();

		m_window.create(sf::VideoMode(m_window_size.x, m_window_size.y), "SFML", sf::Style::Fullscreen);

		m_isFullScreen = true;
	}
	else if (m_isFullScreen == true)
	{
		m_window.close();
		m_window_size.x = 600, m_window_size.y = 600;

		m_window.create(sf::VideoMode(m_window_size.x, m_window_size.y), "SFML");

		m_isFullScreen = false;
	}

}

void Window::Draw(sf::Drawable & l_drawable)
{
	m_window.draw(l_drawable);
}

void Window::Setup(const std::string & l_title, const sf::Vector2u & l_size)
{
	m_window.create(sf::VideoMode(l_size.x, l_size.y), l_title);
}

void Window::Destroy()
{
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Window::Create()
{

}