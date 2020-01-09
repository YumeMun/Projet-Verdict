#include "Player.h"
#include "ResourceManager.h"

Player::Player()
{

}

Player::Player(int _ID, sf::Vector2f _Pos, Map* _Map, int _skinNumber)
{
	ID = _ID;
	if (ID == 1)
	{
		PlayerRect.left = 0, PlayerRect.top = 0, PlayerRect.width = 360, PlayerRect.height = 135;
		spPlayer.setTextureRect(PlayerRect);

		spPlayer.setTexture(*ResourceManager::Instance()->GetTexture("Player1_Colo" + std::to_string(_skinNumber)));
		spPlayer.setOrigin(PlayerRect.width / 2, PlayerRect.height / 2);
		spPlayer.setPosition(_Map->GetStartPos().x + 450, _Map->GetStartPos().y);

		Player_ColliderLimit[0].x = spPlayer.getOrigin().x * 0.8;
		Player_ColliderLimit[0].y = spPlayer.getOrigin().y * 0.6;

		Player_ColliderLimit[1].x = Player_ColliderLimit[0].x - 100;
		Player_ColliderLimit[1].y = Player_ColliderLimit[0].y;

		Player_ColliderLimit[2].x = Player_ColliderLimit[1].x - 100;
		Player_ColliderLimit[2].y = Player_ColliderLimit[1].y;

		spNumeroJoueur.setTexture(*ResourceManager::Instance()->GetTexture("Numero joueur"));
		spNumeroJoueur.setTextureRect(sf::IntRect{ 0, 0, 101, 105 });
		spNumeroJoueur.setOrigin(101 / 2, 105 / 2);
		spNumeroJoueur.setPosition(spPlayer.getPosition().x, spPlayer.getPosition().y - 100);

		ColliderCircle.setRadius(15);
		ColliderCircle.setFillColor(sf::Color::Black);
		ColliderCircle.setOrigin(15, 15);
	}
	else if (ID == 2)
	{
		PlayerRect.left = 0, PlayerRect.top = 0, PlayerRect.width = 372, PlayerRect.height = 150;
		spPlayer.setTextureRect(PlayerRect);

		spPlayer.setTexture(*ResourceManager::Instance()->GetTexture("Player2_Colo" + std::to_string(_skinNumber)));
		//spPlayer.setTexture(*ResourceManager::Instance()->GetTexture("Player2"));
		spPlayer.setOrigin(PlayerRect.width / 2, PlayerRect.height / 2);
		spPlayer.setPosition(_Map->GetStartPos().x + 200, _Map->GetStartPos().y);

		Player_ColliderLimit[0].x = spPlayer.getOrigin().x * 0.8;
		Player_ColliderLimit[0].y = spPlayer.getOrigin().y * 0.6;

		Player_ColliderLimit[1].x = Player_ColliderLimit[0].x - 100;
		Player_ColliderLimit[1].y = Player_ColliderLimit[0].y;

		Player_ColliderLimit[2].x = Player_ColliderLimit[1].x - 100;
		Player_ColliderLimit[2].y = Player_ColliderLimit[1].y;

		spNumeroJoueur.setTexture(*ResourceManager::Instance()->GetTexture("Numero joueur"));
		spNumeroJoueur.setTextureRect(sf::IntRect{ 0, 105, 101, 105 });
		spNumeroJoueur.setOrigin(101 / 2, 105 / 2);
		spNumeroJoueur.setPosition(spPlayer.getPosition().x, spPlayer.getPosition().y - 100);
	}

	spPlayer.setScale(0.7, 0.7);

	Player_Movement.x = SPEED;

	rectAnimElec = { 0, 0, 351, 168 };
	animElec.setTextureRect(rectAnimElec);
	animElec.setTexture(*ResourceManager::Instance()->GetTexture("Effet_Elec"));
	animElec.setOrigin(sf::Vector2f(animElec.getGlobalBounds().width / 2, animElec.getGlobalBounds().height / 2));
	animElec.setPosition(GetPos());
	timerAnimElec.restart();

	timerCE.restart();

	HasCollectible = false;
	Hasfinished = false;
}

Player::~Player()
{
}

void Player::Update(float _Elapsed, Map* _Map, Caméra* _Cam, sf::Vector2f _PosJ2)
{
	if (spPlayer.getPosition().x + 20 > _Map->GetEndFlag().x)
		Hasfinished = true;

	if (spPlayer.getPosition().x < _Map->GetSizeX() * 64 && spPlayer.getPosition().y < (_Map->GetSizeY() * 64) - 2 && Alive == true)
	{
		Controls(_Map, _Elapsed);

		if (Invincible == false)
		{
			Traps(_Map, _Cam);
		}

		CollectibleCollide(_Map, _PosJ2);
		LauchCollectible();

		if (Invincible == false)
			Traps(_Map, _Cam);

		if (isNumeroDisplay == false)
		{
			DisplayNumeroTimer.restart();
			isNumeroDisplay = true;
		}
	}
	else if (Alive == true && spPlayer.getPosition().x >= _Map->GetSizeX() * 64 && spPlayer.getPosition().y >= _Map->GetSizeY() * 64)
	{
		spPlayer.setPosition(_Map->GetCheckPoint(_Cam->GetCameraCenter()));
		spPlayer.setRotation(0);
		Player_Direction = NONE;
		Player_Movement.x = 0;
		Player_Movement.y = 0;
		Player_SlopVector.x = 0;
		Player_SlopVector.y = 0;
		Player_Vector.x = 0;
		Player_Vector.y = 0;
		Alive = false;


		scoreFall += 30; /// FACTOR_DIVIDE;

		m_engineoff.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("EngineOff"));
		m_engineoff.setVolume(GameManager::Instance()->VolumeFX);
		m_engineoff.play();

		m_death.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Mort Hors Ecran"));
		m_death.setVolume(GameManager::Instance()->VolumeFX);
		m_death.play();

		//scoreFall += 50 / FACTOR_DIVIDE;

	}
	else if (Alive == false && _Cam->GetCameraCenter().x >= GetPos().x)
	{
		Alive = true;

		m_respawn.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Respawn"));
		m_respawn.setVolume(GameManager::Instance()->VolumeFX);
		m_respawn.play();

		m_engineon.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("EngineOn"));
		m_engineon.setVolume(GameManager::Instance()->VolumeFX);
		m_engineon.play();
	}

	if (((GetPos().x < _Cam->GetCameraCenter().x - _Cam->GetSizeCamera().x / 2) || (GetPos().y > _Cam->GetCameraCenter().y + _Cam->GetSizeCamera().y / 2) || (GetPos().y < _Cam->GetCameraCenter().y - _Cam->GetSizeCamera().y / 2)) && Alive == true)
	{
		spPlayer.setPosition(_Map->GetCheckPoint(_Cam->GetCameraCenter()));
		spPlayer.setRotation(0);
		Player_Direction = NONE;
		Player_Movement.x = 0;
		Player_Movement.y = 0;
		Player_SlopVector.x = 0;
		Player_SlopVector.y = 0;
		Player_Vector.x = 0;
		Player_Vector.y = 0;
		DisplayNumeroTimer.restart();

		Alive = false;
	}

	if (Hasfinished == false)
	{
		Player_Vector = Player_Movement + Player_SlopVector;

		if (Shocked == false)
			spPlayer.move(Player_Vector * _Elapsed);
		else if (Shocked == true)
			spPlayer.move(Shocked_Move * _Elapsed);
	}


	if (InvincibleTime.getElapsedTime().asSeconds() >= 3 && Invincible == true)
		Invincible = false;
	else if (Invincible == true)
	{
		Oiled = false;
		Shocked = false;
	}

	if (CollectID != 0)
		HasCollectible = true;
	else if (CollectID == 0)
		HasCollectible = false;

	if (Player_Direction == NONE)
	{
		if (spPlayer.getRotation() >= 315 && spPlayer.getRotation() < 355)
			spPlayer.rotate(SPEED / 1.5 * _Elapsed);
		else if (spPlayer.getRotation() <= 45 && spPlayer.getRotation() > 5)
			spPlayer.rotate(-SPEED / 1.5 * _Elapsed);
		else if (spPlayer.getRotation() >= 355 && spPlayer.getRotation() <= 5)
			spPlayer.setRotation(0);
		else 
			spPlayer.setRotation(0);
	}
	else if (Player_Direction == UP)
	{
		if (spPlayer.getRotation() <= 310 || spPlayer.getRotation() >= 320)
			spPlayer.rotate(-SPEED / 1.5 * _Elapsed);
		else if (spPlayer.getRotation() <= 320 && spPlayer.getRotation() >= 310)
			spPlayer.setRotation(315);
		else
			spPlayer.setRotation(315);
	}
	else if (Player_Direction == DOWN)
	{
		if (spPlayer.getRotation() <= 40 || spPlayer.getRotation() >= 355)
			spPlayer.rotate(SPEED / 1.5 * _Elapsed);
		else if (spPlayer.getRotation() <= 50 && spPlayer.getRotation() >= 40)
			spPlayer.setRotation(45);
		else
			spPlayer.setRotation(45);
	}

	Animations();

}

void Player::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spPlayer);
	//_Window->draw(ColliderCircle);

	if (isCollideCE)
		_Window->draw(animElec);

	if (DisplayNumeroTimer.getElapsedTime().asSeconds() < 15)
	{
		spNumeroJoueur.setPosition(spPlayer.getPosition().x, spPlayer.getPosition().y - 100);
		_Window->draw(spNumeroJoueur);
	}
}

void Player::Controls(Map* _Map, float _Elapsed)
{
	//ColliderCircle.setPosition(GetPos().x + 75, GetPos().y + Player_ColliderLimit.y + 50);

	if (sf::Joystick::isConnected(ID - 1));
	{
		if (sf::Joystick::isButtonPressed(ID - 1, 0) && KeyPress == false && Jump == false && Oiled == false)
		{
			Player_Movement.y = -SPEED * 2;

			FrameIndex = 0;
			isJumping = true;
			if (Player_Movement.x >= SPEED)
			{
				PlayerRect.top = PlayerRect.height * 3;
				isStartJumpSpeedMax = true;
			}
			else
			{
				PlayerRect.top = PlayerRect.height * 4;
				isStartJumpSpeedMax = false;
			}

			Jump = true;

			KeyPress = true;
		}
		else if (!sf::Joystick::isButtonPressed(ID - 1, 0))
			KeyPress = false;
	}

	if (Jump == true)
	{
		if (Player_SlopVector.y < 0)
			Player_SlopVector.y = 0;
	}

	if (_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) == 8 || _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) == 13 && Player_Direction == NONE)
	{
		if (Jump == true)
		{
			Jump = false;
		}

		if (Player_Movement.y > 0)
			Player_Movement.y = 0;
	}
	else if (_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) == 7 || _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) == 12 && Player_Direction == NONE)
	{
		if (Jump == true)
		{
			Jump = false;

			if (Player_Movement.x > 0)
				Player_Movement.x = 0;
		}

		if (Player_Movement.y > 0)
			Player_Movement.y = 0;
	}

	for (int i = 1; i < 7; i++)
	{
		if (Jump == false && Player_Direction == NONE && _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) == i)
		{
			spPlayer.setPosition(sf::Vector2f(GetPos().x, _Map->GetNextTile(i, GetPos()).y - Player_ColliderLimit[0].y));
		}
	}

	if (Jump == false && Player_Direction == NONE && _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) == 11)
	{
		spPlayer.setPosition(sf::Vector2f(GetPos().x, _Map->GetNextTile(11, GetPos()).y - Player_ColliderLimit[0].y));
	}

	if (_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) >= 1 && _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) <= 6)
	{
		Jump = false;
	}

	if ((_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) == 0 || _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) == 8 ||
		_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) >= 20) && Player_Direction == NONE)
	{
		Player_Movement.y += GRAVITY * GRAVITYFACTOR * _Elapsed;
		Jump = true;
	}
	else if ((_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) >= 1 && _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) <= 6) || _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) == 11)//
	{
		if (Player_Movement.y > 0)
		{
			Player_Movement.y = 0;
			Jump = false;
		}

		if (Player_SlopVector.y != 0)
			Player_SlopVector.y = 0;

		if (_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) >= 11 && _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y) <= 13 && Boost == false)
		{
			m_Boost.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Boost"));
			m_Boost.setVolume(GameManager::Instance()->VolumeFX);
			m_Boost.play();

			Boost = true;
			BoostClock.restart();
		}
	}

	if (BoostClock.getElapsedTime().asSeconds() >= 2)
	{
		Boost = false;
		Boosted = false;
	}

	if (GetPos().y - Player_ColliderLimit[0].y > 0)
	{
		if ((_Map->GetTile(GetPos().x, GetPos().y - Player_ColliderLimit[0].y / 2) != 0 && _Map->GetTile(GetPos().x, GetPos().y - Player_ColliderLimit[0].y / 2) < 20))
		{
			if (Player_Movement.y < 0)
				Player_Movement.y = 0;

			if (Player_SlopVector.y < 0)
				Player_SlopVector.y = 0;
		}
	}

	if (Player_Direction == NONE)
	{
		if (_Map->GetTile(GetPos().x + 50, GetPos().y) == 7 || _Map->GetTile(GetPos().x + 50, GetPos().y) == 12)
		{
			if (Player_Movement.y > 0)
				Player_Movement.y = 0;

			Player_Direction = UP;
		}
		else if (_Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y * 2) == 8 || _Map->GetTile(GetPos().x, GetPos().y + Player_ColliderLimit[0].y * 2) == 13)
		{
			Player_Direction = DOWN;
		}
	}
	else if (Player_Direction == UP)
	{
		if (Boost == true)
			Player_Movement.x = SPEED * 1.5;

		Player_SlopVector.y = -Player_Movement.x;

		if (_Map->GetTile(GetPos().x + 50, GetPos().y + 50) == 12 && Boost == false)
		{
			Boost = true;
			BoostClock.restart();
		}

		if (_Map->GetTile(GetPos().x + 50, GetPos().y + 50) == 0)
		{
			Player_Direction = NONE;
		}
	}
	else if (Player_Direction == DOWN)
	{
		if (Player_Movement.y < 0)
			Player_Movement.y = 0;

		if (Boost == false)
			Player_Movement.x = SPEED;
		else if (Boost == true)
			Player_Movement.x = SPEED * 1.5;

		Player_SlopVector.y = Player_Movement.x;

		if (_Map->GetTile(GetPos().x - Player_ColliderLimit[0].x, GetPos().y + Player_ColliderLimit[0].y) == 13 && Boost == false)
		{
			Boost = true;
			BoostClock.restart();
		}

		if ((_Map->GetTile(GetPos().x + Player_ColliderLimit[0].x, GetPos().y + Player_ColliderLimit[0].y) >= 1 && _Map->GetTile(GetPos().x + Player_ColliderLimit[0].x, GetPos().y + Player_ColliderLimit[0].y) <= 6) || _Map->GetTile(GetPos().x + Player_ColliderLimit[0].x, GetPos().y + Player_ColliderLimit[0].y) == 11)
		{
			if (Player_Movement.y > 0)
				Player_Movement.y = 0;

			Player_Direction = NONE;
		}
	}

	if (Player_Movement.x < SPEED && Oiled == false)
	{
		Player_Movement.x += 10;
	}
	else if (Player_Movement.x >= SPEED && Boost == false && Oiled == false)
		Player_Movement.x = SPEED;
	else if (Boost == true)
		Player_Movement.x = SPEED * 1.5;
	else if (Oiled == true)
	{
		if (Player_Movement.x >= SPEED / 2)
			Player_Movement.x = SPEED / 2;
	}

	if (sf::Joystick::getAxisPosition(ID - 1, sf::Joystick::X) >= 50)
	{
		Rocket_Direction = 0;
	}
	else if (sf::Joystick::getAxisPosition(ID - 1, sf::Joystick::X) <= -50)
	{
		Rocket_Direction = 1;
	}
}

void Player::Traps(Map* _Map, Caméra* _Cam)
{
	if (Player_Direction == NONE)
	{
		for (int nbPts = 0; nbPts < 3; nbPts++)
		{
			if (_Map->GetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y) >= 1 && _Map->GetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y) <= 6)
				/*|| (_Map->GetTile(GetPos().x + Player_ColliderLimit.x, GetPos().y) >= 17 && _Map->GetTile(GetPos().x + Player_ColliderLimit.x, GetPos().y) <= 19))*/
			{
				Player_Movement.x = 0;
			}
			else if (_Map->GetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y) >= 17 && _Map->GetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y) <= 19)
			{
				if (_Map->GetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y) == 17)
					_Map->SetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y, 35);

				else if (_Map->GetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y) == 18)
					_Map->SetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y, 36);

				else if (_Map->GetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y) == 19)
					_Map->SetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y, 37);

				scoreHitTrap += 15; /// FACTOR_DIVIDE;

				timerTrapFactor.restart();
				SetHitTrap();
				Player_Movement.x = Player_Movement.x / trapSpeedFactor;
			}
			else if (_Map->GetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y) == 22 || _Map->GetTile(GetPos().x + Player_ColliderLimit[nbPts].x, GetPos().y) == 29)
			{
				if (_Map->GetIsLazerOn() == 1)
				{
					spPlayer.setPosition(_Map->GetCheckPoint(_Cam->GetCamOrigin()));
					Player_Movement.x = 0;
					Player_Movement.y = 0;
					Alive = false;
					if (!isHitLazer)
					{
						scoreHitTrap += 15;
						isHitLazer = true;
					}
				}
				else
					isHitLazer = false;
			}

			for (int i = 0; i < 3; i++)
			{
				if (_Map->GetTile(GetPos().x + Player_ColliderLimit[i].x, GetPos().y) == 20 || _Map->GetTile(GetPos().x + Player_ColliderLimit[i].x, GetPos().y) == 28)
				{
					timerTrapFactor.restart();
					isCollideCE = true;
					if (timerCE.getElapsedTime().asMilliseconds() > 1000)
					{
						scoreHitTrap += 15; 
						timerCE.restart();
					}
					SetHitLazer();
				}
				else
					isCollideCE = false;
			}
		}
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
			AnimClock.restart();
		}
		else if (lastFrameSpeed < SPEED && Player_Movement.x >= SPEED)
		{
			isSwitching = true;
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
			if (!isSwitching)
			{
				FrameIndex = 0;
				PlayerRect.left = 0;
				PlayerRect.top = 1 * PlayerRect.height;
				spPlayer.setTextureRect(PlayerRect);
			}
			else
			{
				PlayerRect.top = 0;
				if (AnimClock.getElapsedTime().asMilliseconds() > 100)
				{
					if (FrameIndex < 4)
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
				PlayerRect.top = 2 * PlayerRect.height;
				if (AnimClock.getElapsedTime().asMilliseconds() > 100)
				{
					if (FrameIndex < 3)
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
			isSwitchingBack = true;
		else if (lastFrameSpeed < SPEED && Player_Movement.x >= SPEED)
			isSwitching = true;

		if (AnimClock.getElapsedTime().asMilliseconds() > 100)
		{
			if (FrameIndex < 11)
				FrameIndex++;
			else
			{
				FrameIndex = 0;
				if (isStartJumpSpeedMax)
				{
					if (isSwitchingBack)
						PlayerRect.top = 2 * PlayerRect.height;
					else
						PlayerRect.top = 1 * PlayerRect.height;
				}
				else
					PlayerRect.top = 0 * PlayerRect.height;

				StartAnim = true;
				isJumping = false;
			}

			PlayerRect.left = FrameIndex * PlayerRect.width;
			spPlayer.setTextureRect(PlayerRect);

			AnimClock.restart();
		}
	}

	lastFrameSpeed = Player_Movement.x;

	if (isCollideCE)
	{
		animElec.setPosition(GetPos());

		if (timerAnimElec.getElapsedTime().asMilliseconds() > 60)
		{
			rectAnimElec.left += 351;
			if (rectAnimElec.left == 3 * 351)
				rectAnimElec.left = 0;

			animElec.setTextureRect(rectAnimElec);
			timerAnimElec.restart();

		}
	}

	if (AnimNumero.getElapsedTime().asMilliseconds() > 30)
	{
		if (FrameIndexNumero < 18)
			FrameIndexNumero++;
		else
			FrameIndexNumero = 0;

		if (ID == 1)
			spNumeroJoueur.setTextureRect(sf::IntRect{ FrameIndexNumero * 101, 0, 101, 105 });
		else if (ID == 2)
			spNumeroJoueur.setTextureRect(sf::IntRect{ FrameIndexNumero * 101, 105, 101, 105 });

		AnimNumero.restart();
	}
}

sf::Sprite Player::GetSprite()
{
	return spPlayer;
}

sf::Vector2f Player::GetPos()
{
	return spPlayer.getPosition();
}


bool Player::CollectibleCollide(Map* _Map, sf::Vector2f _PosJ2)
{
	srand(time(NULL));

	if (_Map->GetTile(GetPos().x, GetPos().y) == 23)
	{
		if (HasCollectible == false)
		{
			_Map->SetTile(GetPos().x, GetPos().y, 0);

			Collectible.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Collecte Objet"));
			Collectible.setVolume(GameManager::Instance()->VolumeFX);
			Collectible.play();

			RandomCollect = rand() % 100 + 1;

			if (spPlayer.getPosition().x > _PosJ2.x)
			{
				if (RandomCollect <= 30)
					CollectID = e_Enum::e_Collects::ROCKET;
				else if (RandomCollect > 30 && RandomCollect <= 50)
					CollectID = e_Enum::e_Collects::OILFLAKE;
				else if (RandomCollect > 50 && RandomCollect <= 70)
					CollectID = e_Enum::e_Collects::SHOCKWAVE;
				else if (RandomCollect > 70 && RandomCollect <= 85)
					CollectID = e_Enum::e_Collects::SWAP;
				else if (RandomCollect > 85)
					CollectID = e_Enum::e_Collects::BUMPER;
			}
			else if (spPlayer.getPosition().x < _PosJ2.x)
			{
				if (RandomCollect <= 30)
					CollectID = e_Enum::e_Collects::ROCKET;
				else if (RandomCollect > 30 && RandomCollect <= 50)
					CollectID = e_Enum::e_Collects::LEVITATION;
				else if (RandomCollect > 50 && RandomCollect <= 70)
					CollectID = e_Enum::e_Collects::SWAP;
				else if (RandomCollect > 70 && RandomCollect <= 90)
					CollectID = e_Enum::e_Collects::BUMPER;
				else if (RandomCollect > 90)
					CollectID = e_Enum::e_Collects::SHOCKWAVE;
			}

			return true;
		}
	}

	return false;
}

int Player::GetCollectID()
{
	return CollectID;
}

int Player::GetAimDir()
{
	return Rocket_Direction;
}

void Player::LauchCollectible()
{
	if (HasCollectible == true)
	{
		if (sf::Joystick::isButtonPressed(ID - 1, 1) && ItemPress == false)
		{
			UseIt = true;
			HasCollectible = false;
			ItemPress = true;
		}
		else if (!sf::Joystick::isButtonPressed(ID - 1, 1))
			ItemPress = false;
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

void Player::SetHitTrap()
{
	Alteration.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Alteration"));
	Alteration.setVolume(GameManager::Instance()->VolumeFX*0.5);
	Alteration.play();
	if (timerTrapFactor.getElapsedTime().asSeconds() < 3)  //courbe active dans un delai de :3s
	{
		trapSpeedFactor = -(-(0.1 * trapHitCount) * ((-3) * log(trapHitCount)) - 3.5); // -3 = a (amplitude courbe en x),   3.5 = ymax quand x = 1
		if (trapHitCount < 4)
		{
			trapHitCount++;
		}
		else
			trapHitCount = 1;
	}
	else
	{
		trapSpeedFactor = 1;
		trapHitCount = 1;
	}
}

void Player::SetHitLazer()
{
	//trapSpeedFactor = 5;
	Player_Movement.x = 800 / 3;


}

void Player::SetAnimWheelStart()
{
	PlayerRect.top = 0;
	if (AnimClock.getElapsedTime().asMilliseconds() > 100)
	{
		if (FrameIndex < 4)
			FrameIndex++;
		else
		{
			FrameIndex = 0;
			PlayerRect.top = 1 * PlayerRect.height;
			isAnimStartEnd = true;
		}

		PlayerRect.left = FrameIndex * PlayerRect.width;
		spPlayer.setTextureRect(PlayerRect);
		AnimClock.restart();
	}
}

void Player::SetAnimClockRestart()
{
	AnimClock.restart();
	FrameIndex = 0;
}

int Player::GetFrameIndex()
{
	return FrameIndex;
}

bool Player::CollectibleUsed()
{
	return UseIt;
}
