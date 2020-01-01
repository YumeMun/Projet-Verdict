#include "Player.h"
#include "ResourceManager.h"

Player::Player()
{

}

Player::Player(int _ID, sf::Vector2f _Pos)
{
	ID = _ID;

	PlayerRect.left = 0, PlayerRect.top = 0, PlayerRect.width = 121, PlayerRect.height = 54;
	spPlayer.setTextureRect(PlayerRect);

	spPlayer.setTexture(*ResourceManager::Instance()->GetTexture("Player2"));
	spPlayer.setOrigin(PlayerRect.width / 2, PlayerRect.height / 2);
	spPlayer.setPosition(_Pos);
	spPlayer.setScale(sf::Vector2f{ 1.7, 1.7 });

	Player_ColliderLimit.x = spPlayer.getOrigin().x * 1.5;
	Player_ColliderLimit.y = spPlayer.getOrigin().y * 2;

	Player_Movement.x = SPEED;

	HasCollectible = false;
	Hasfinished = false;
}

Player::~Player()
{
}

void Player::Update(float _Elapsed, Map* _Map, Cam�ra* _Cam, sf::Vector2f _Pos)
{
	if (spPlayer.getPosition().x < 12000 * 64 && spPlayer.getPosition().y < 34 * 64 &&
		spPlayer.getPosition().x > 0 && spPlayer.getPosition().y > 0 && Alive == true)
		Controls(_Map);
	else if (Alive == true)
	{
		spPlayer.setPosition(_Map->GetCheckPoint(_Cam->GetCamOrigin()));
		Player_Movement.x = 0;
		Player_Movement.y = 0;
		Player_Vector.x = 0;
		Player_Vector.y = 0;
		Alive = false;
	}
	else if (Alive == false && _Pos.x >= GetPos().x)
		Alive = true;

	if (GetPos().x < _Cam->GetCameraCenter().x - _Cam->GetSizeCamera().x / 2)
	{
		spPlayer.setPosition(_Map->GetCheckPoint(_Cam->GetCamOrigin()));
		//Player_Movement.x = 0;
		Player_Movement.y = 0;
		Player_Vector.x = 0;
		Player_Vector.y = 0;
		Alive = false;
	}

	if (spPlayer.getPosition().x < 20400)
	{
		Player_Vector = Player_Movement + Player_SlopVector;
		spPlayer.move(Player_Vector * _Elapsed);
	}
	else
		Hasfinished = true;

	if (CollectID != 0)
		HasCollectible = true;
	else if (CollectID == 0)
		HasCollectible = false;

	/*if (newMissile != NULL)
		MissileCollide();*/

	CollectibleCollide(_Map);
	LauchCollectible();

	Animations();
}

void Player::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spPlayer);
}

void Player::Controls(Map* _Map)
{
	if (sf::Joystick::isConnected(ID - 1));
	{
		if (sf::Joystick::isButtonPressed(ID - 1, 0) && KeyPress == false && Jump == false && Oiled == false)
		{
			Player_Movement.y = -SPEED * 2;
			Player_Movement.y = -SPEED * 1.5;

			FrameIndex = 0;
			isJumping = true;
			Jump = true;

			KeyPress = true;
		}
		else if (!sf::Joystick::isButtonPressed(ID - 1, 0))
			KeyPress = false;
	}

	if (Jump == false && Player_Direction == NONE && _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit.y) == 1)
	{
		spPlayer.setPosition(sf::Vector2f(GetPos().x, _Map->GetNextTile(1, GetPos()).y - Player_ColliderLimit.y));
	}

	if (_Map->GetTile(GetPos().x, GetPos().y + spPlayer.getOrigin().y) == 1 ||
		_Map->GetTile(GetPos().x, GetPos().y + spPlayer.getOrigin().y) == 2 ||
		_Map->GetTile(GetPos().x + Player_ColliderLimit.x, GetPos().y) == 3)
	{
		Jump = false;
	}

	if ((_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit.y) == 0 || _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit.y) == 8) && Player_Direction != UP)
	{
		Player_Movement.y += GRAVITY * GRAVITYFACTOR;
		Jump = true;
	}
	else if ((_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit.y) == 1 || _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit.y) == 4))
	{
		if (Player_Movement.y > 0)
		{
			Player_Movement.y = 0;
			Jump = false;
		}

		if (Player_SlopVector.y != 0)
			Player_SlopVector.y = 0;

		if (_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit.y) == 4 && Boost == false)
		{
			Boost = true;
			BoostClock.restart();
		}
	}

	if (BoostClock.getElapsedTime().asSeconds() >= 2)
		Boost = false;

	if (_Map->GetTile(GetPos().x, GetPos().y - Player_ColliderLimit.y / 2) == 1)
	{
		if (Player_Movement.y < 0)
			Player_Movement.y = 0;

		if (Player_SlopVector.y < 0)
			Player_SlopVector.y = 0;
	}

	if (Player_Direction == NONE)
	{
		spPlayer.setRotation(0);

		if (_Map->GetTile(GetPos().x + Player_ColliderLimit.x, GetPos().y) == 1 || _Map->GetTile(GetPos().x + Player_ColliderLimit.x, GetPos().y) == 7)
		{
			Player_Movement.x = 0;

			if (_Map->GetTile(GetPos().x + Player_ColliderLimit.x, GetPos().y + 20) == 7)
				_Map->SetTile(GetPos().x + Player_ColliderLimit.x, GetPos().y + 20, 0);
		}
		else
		{
			if (Player_Movement.x < SPEED && Oiled == false)
				Player_Movement.x += 10;
			else if (Player_Movement.x >= SPEED && Boost == false && Oiled == false)
				Player_Movement.x = SPEED;
			else if (Boost == true)
				Player_Movement.x = SPEED * 1.5;
			else if (Oiled == true)
			{
				if (Player_Movement.x >= SPEED / 2)
					Player_Movement.x = SPEED / 2;
			}
		}

		if (_Map->GetTile(GetPos().x + Player_ColliderLimit.x * 2, GetPos().y) == 3 || _Map->GetTile(GetPos().x + Player_ColliderLimit.x * 2, GetPos().y) == 6)
		{
			Player_Direction = UP;
		}
		else if (_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit.y) == 2 || _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit.y) == 5)
		{
			Player_Direction = DOWN;
		}
	}
	else if (Player_Direction == UP)
	{
		spPlayer.setRotation(315);

		//Player_Movement.x = SPEED;
		Player_SlopVector.y = -Player_Movement.x;

		if (_Map->GetTile(GetPos().x + Player_ColliderLimit.x, GetPos().y + Player_ColliderLimit.y) == 6 && Boost == false)
		{
			Boost = true;
			BoostClock.restart();
		}

		if (_Map->GetTile(GetPos().x + 200, GetPos().y + 100) == 0)
			Player_Direction = NONE;
	}
	else if (Player_Direction == DOWN)
	{
		spPlayer.setRotation(45);

		Player_Movement.x = SPEED;
		Player_SlopVector.y = Player_Movement.x;

		if (_Map->GetTile(GetPos().x - Player_ColliderLimit.x, GetPos().y + Player_ColliderLimit.y) == 6 && Boost == false)
		{
			Boost = true;
			BoostClock.restart();
		}

		if (_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit.y) == 1)
			Player_Direction = NONE;
	}
}

bool Player::IsAlive()
{
	return Alive;
}

void Player::Animations()
{
	if (!isJumping)
	{
			if (Player_Movement.x < SPEED && lastFrameSpeed >= SPEED)
			{
				isSwitchingBack = true;
				//isSpeedMax = false;
				AnimClock.restart();
			}
			else if (lastFrameSpeed < SPEED && Player_Movement.x >= SPEED)
			{
				isSwitching = true;
				//isSpeedMax = true;
				AnimClock.restart();
			}
			
			if (Player_Movement.x >= SPEED)
			{
				isSpeedMax = true;
			}
			else
			{
				isSpeedMax = false;
			}

			if (isSpeedMax)
			{
				if (isSwitching)
				{
					FrameIndex = 0;
					PlayerRect.left = 0;
					PlayerRect.top = 54;
					spPlayer.setTextureRect(PlayerRect);
				}
				else
				{
					if (AnimClock.getElapsedTime().asMilliseconds() > 100)
					{
						if (FrameIndex < 5)
							FrameIndex++;
						else
						{
							FrameIndex = 0;
							isSwitching = false;
						}

						PlayerRect.left = FrameIndex * PlayerRect.width;
						spPlayer.setTextureRect(PlayerRect);
						AnimClock.restart();
					}
				}
			}
			else
			{
				if (!isSwitchingBack)
				{
					FrameIndex = 0;
					PlayerRect.left = 0;
					PlayerRect.top = 0;
					spPlayer.setTextureRect(PlayerRect);
				}
				else
				{
					if (AnimClock.getElapsedTime().asMilliseconds() > 100)
					{
						if (FrameIndex < 4)
							FrameIndex++;
						else
						{
							FrameIndex = 0;
							isSwitchingBack = false;
						}

						PlayerRect.left = FrameIndex * PlayerRect.width;
						spPlayer.setTextureRect(PlayerRect);
						AnimClock.restart();
					}
				}
			}
	}
	else
	{
			if (Player_Movement.x < SPEED && lastFrameSpeed >= SPEED)
			{
				isSwitchingBack = true;
			}
			else if (lastFrameSpeed < SPEED && Player_Movement.x >= SPEED)
			{
				isSwitching = true;
			}

			PlayerRect.top = PlayerRect.height*4;
			PlayerRect.top = PlayerRect.height * 4;

			if (AnimClock.getElapsedTime().asMilliseconds() > 100)
			{
				if (FrameIndex < 12)
					FrameIndex++;
				else
				{
					FrameIndex = 0;
					PlayerRect.top = 1 * PlayerRect.height;
					StartAnim = true;
					isJumping = false;
				}

				PlayerRect.left = FrameIndex * PlayerRect.width;
				spPlayer.setTextureRect(PlayerRect);

				AnimClock.restart();
			}
	}
		lastFrameSpeed = Player_Movement.x;
}

sf::Sprite Player::GetSprite()
{
	return spPlayer;
}

sf::Vector2f Player::GetPos()
{
	return spPlayer.getPosition();
}

//void Player::MissileCollide()
//{
//	if (spPlayer.getPosition().x - spPlayer.getGlobalBounds().width / 2 >= newMissile->GetMissile().getPosition().x
//		&& spPlayer.getPosition().x + spPlayer.getGlobalBounds().width / 2 <= newMissile->GetMissile().getPosition().x + newMissile->GetMissile().getGlobalBounds().width
//		&& spPlayer.getPosition().y - spPlayer.getGlobalBounds().height / 2 >= newMissile->GetMissile().getPosition().y
//		&& spPlayer.getPosition().y + spPlayer.getGlobalBounds().width / 2 <= newMissile->GetMissile().getPosition().y + newMissile->GetMissile().getGlobalBounds().height)
//	{
//		Player_Movement.x = 0;
//		delete newMissile;
//	}
//	else
//	{
//		if (Player_Movement.x < SPEED)
//			Player_Movement.x += 10;
//		else if (Player_Movement.x >= SPEED)
//			Player_Movement.x = SPEED;
//	}
//}

bool Player::CollectibleCollide(Map* _Map)
{
	srand(time(NULL));

	if (_Map->GetTile(GetPos().x + spPlayer.getOrigin().x, GetPos().y) == 9)
	{
		_Map->SetTile(GetPos().x + spPlayer.getOrigin().x, GetPos().y, 0);

		if (HasCollectible == false)
		{
			CollectID = e_Enum::OILFLAKE;//rand() % 6 + 1;
		}

		return true;
	}

	return false;
}

int Player::GetCollectID()
{
	return CollectID;
}

void Player::LauchCollectible()
{
	/*if (sf::Joystick::getAxisPosition(ID - 1, sf::Joystick::X) >= 50)
	{
		Missile_Direction = 0;
	}
	else if (sf::Joystick::getAxisPosition(ID - 1, sf::Joystick::X) >= -50)
	{
		Missile_Direction = 1;
	}*/

	if (HasCollectible == true)
	{
		if (sf::Joystick::isButtonPressed(ID - 1, 1))
		{
			UseIt = true;
			//newMissile = new Missile(Missile_Direction, spPlayer.getPosition());
		}
	}
	else
	{
		UseIt = false;
	}
}

void Player::SetCollectID(int _CollectID)
{
	CollectID = _CollectID;
}

bool Player::CollectibleUsed()
{
	return UseIt;
}
