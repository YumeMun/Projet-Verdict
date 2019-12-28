#include"GameManager.h"
#include "Enum.h"

int main()
{
	GameManager::Instance()->Start();

	while (GameManager::Instance()->GetWindow()->isOpen())
	{
		GameManager::Instance()->Update();
		GameManager::Instance()->Display();
	}
}