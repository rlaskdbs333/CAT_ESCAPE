#include "gameEntityManager.h"
#include "global.h"
#include "enemy.h"
#include "runEnemy_1.h"
#include "runEnemy_2.h"
#include "runEnemy_3.h"
#include "runEnemy_4.h"
#include "mathManager.h"
//#include "musicDirections.h"

#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

GameEntityManager::GameEntityManager()
{
	timeMax = 100;
	scoreTime = 0;
	time = 0;
	enemySpeed = 16;
	enemyCount = 3;
}

void GameEntityManager::ClearAll()
{
	computer = rand() % 3;
	stop = false;
	isGood = false;
	isMiss = false;
	isRunStage = false;
	isMusicStage = false;
	isRspStage = false;
	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;
	isSpace = false;

	if (runPlayer != nullptr)
		runPlayer->setScore(0);

	m_time1 = 0;
	m_time2 = 0;
	scoreTime = 0;
	time = 0;
	enemySpeed = 15;
	timeMax = 100;
	enemyCount = 3;

	if (directions.size() > 0)
		directions.clear();
	if (enemies.size() > 0)
		enemies.clear();

}




void GameEntityManager::Update()
{
	if (isRunStage)
		runStageUpdate();

	if (isMusicStage)
		musicStageUpdate();

	if (isRspStage)
		rspStageUpdate();
}

void GameEntityManager::Render()
{
	if (isRunStage)
		runStageRender();

	if (isMusicStage)
		musicStageRender();
}


//runStage
void GameEntityManager::AddEnemy(int type, int x)
{
	if (type == 0) {
		Enemy* enemy = new RunEnemy_1();
		x = 1280;
		enemy->setPosX(x - type);
		enemy->setSpeed(enemySpeed);
		enemies.push_back(enemy);
	}
	else if (type == 1) {
		Enemy* enemy = new RunEnemy_2();
		x = 1280;
		enemy->setPosX(x - type);
		enemy->setSpeed(enemySpeed);
		enemies.push_back(enemy);
	}
	else if (type == 2) {
		Enemy* enemy = new RunEnemy_3();
		x = 1280;
		enemy->setPosX(x - type);
		enemy->setSpeed(enemySpeed);
		enemies.push_back(enemy);
	}
	else if (type == 3) {
		Enemy* enemy = new RunEnemy_4();
		x = 1280;
		enemy->setPosX(x - type);
		enemy->setPosY(BOTTOM_Y - CAT_HEIGHT / 2 - RUN_ENEMY4_HEIGHT - 5);
		enemy->setSpeed(enemySpeed);
		enemies.push_back(enemy);
	}
	else if (type == 4) {
		Enemy* enemy = new RunEnemy_4();
		x = 1280;
		enemy->setPosX(x - type);
		enemy->setPosY(BOTTOM_Y - CAT_HEIGHT - RUN_ENEMY4_HEIGHT - 5);
		enemy->setSpeed(enemySpeed);
		enemies.push_back(enemy);

	}
	else if (type == 5) {
		Enemy* enemy = new RunEnemy_4();
		x = 1280;
		enemy->setPosX(x - type);
		enemy->setPosY(BOTTOM_Y - RUN_ENEMY4_HEIGHT - 5);
		enemy->setSpeed(enemySpeed);
		enemies.push_back(enemy);
	}
	else if (type == 6) {
		Enemy* enemy = new RunEnemy_4();
		x = 1280;
		enemy->setPosX(x - type);
		enemy->setPosY(BOTTOM_Y - CAT_HEIGHT / 2 - RUN_ENEMY4_HEIGHT - 5);
		enemy->setSpeed(enemySpeed);
		enemies.push_back(enemy);

		enemy = new RunEnemy_4();
		x = 1280;
		enemy->setPosX(x - type);
		enemy->setPosY(BOTTOM_Y - CAT_HEIGHT - RUN_ENEMY4_HEIGHT - 30);
		enemy->setSpeed(enemySpeed);
		enemies.push_back(enemy);
	}

}
void GameEntityManager::runStageUpdate()
{
	//player�� ���� �ʾ��� ����
	if (!runPlayer->getIsDead())
	{
		time += 1;
		scoreTime += 1;
		if (runPlayer->getScore() > 100)
			enemyCount = 7;

		if (scoreTime > 5) {
			runPlayer->isHit = false;
			runPlayer->AddScore();
			scoreTime = 0;

			//���ǵ��
			if (runPlayer->getScore() % 150 == 0)
			{
				enemySpeed += 1;
				if (enemySpeed >= 17) {
					enemySpeed = 17;
				}
			}
		}
		int type = rand() % enemyCount;
		//���̵��� �ö� �� �ణ�� ƴ
		if (runPlayer->getScore() % 150 != 0)
		{
			//�ð��� ������ ���� enemy�߰� 
			if (time >= timeMax - enemySpeed - 5)
			{
				AddEnemy(type, 0);
				time = 0;
			}
		}
		else {
			time = 0;
		}

	}


	//�÷��̾�� enemy�浹ó��
	//for (auto iter = enemies.begin(); iter != enemies.end();)
	//{
	//	if (isBoxCollided(runPlayer->getPlayerX(), runPlayer->getPlayerY(), runPlayer->getWidth(), runPlayer->getHeight(),
	//		(*iter)->getPosX(), (*iter)->getPosY(), (*iter)->getWidth(), (*iter)->getHeight()))
	//	{
	//		//runPlayer->isHITED();
	//		runPlayer->setIsDead(true);
	//	}
	//	iter++;
	//}



	//enemy
	for (auto iter = enemies.begin(); iter != enemies.end();)
	{

		if ((*iter)->getPosX() < -300)
		{
			iter = enemies.erase(iter);
		}
		else
		{
			(*iter)->Update();
			iter++;
		}
	}
}
void GameEntityManager::runStageRender()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
	}
}

//musicStage
void GameEntityManager::AddDirections(int type)
{


	/*if (type == left)
	{
		MusicDirections* direction = new MusicDirections();
		direction->setPosx(15);
		direction->setType(left);
		directions.push_back(direction);
	}
	else if (type == up)
	{
		MusicDirections* direction = new MusicDirections();
		direction->setPosx(15 + 150);
		direction->setType(up);
		directions.push_back(direction);
	}
	else if (type == space)
	{
		MusicDirections* direction = new MusicDirections();
		direction->setPosx(15 + 150 * space);
		direction->setType(space);
		directions.push_back(direction);
	}
	else if (type == down)
	{
		MusicDirections* direction = new MusicDirections();
		direction->setPosx(15 + 150 * down);
		direction->setType(down);
		directions.push_back(direction);
	}
	else if (type == right)
	{
		MusicDirections* direction = new MusicDirections();
		direction->setPosx(15 + 150 * right);
		direction->setType(right);
		directions.push_back(direction);
	}*/

}
void GameEntityManager::musicStageUpdate()
{
	//if (!musicPlayer->getIsFinish())
	//{
	//	m_time1 += 1;
	//	m_time2 += 1;
	//	m_time3 += 1;


	//	if (m_time3 > 30) {
	//		isGood = false;
	//		isMiss = false;
	//		m_time3 = 0;
	//	}

	//	//direction �߰�
	//	int type = rand() % 5;
	//	if (m_time1 > 50) {
	//		AddDirections(type);
	//		m_time1 = 0;
	//	}
	//	if (m_time2 > 500) {
	//		AddDirections(type);
	//		m_time2 = 0;
	//	}



	//	//�浹ó��
	//	for (auto iter = directions.begin(); iter != directions.end();)
	//	{
	//		if ((*iter)->getPosY() > 530 && (*iter)->getPosY() < 580)
	//		{
	//			if ((*iter)->getType() == left && isLeft)
	//			{
	//				iter = directions.erase(iter);
	//				musicPlayer->AddScore();
	//				isLeft = false;
	//				isGood = true;
	//			}
	//			else if ((*iter)->getType() == up && isUp)
	//			{
	//				iter = directions.erase(iter);
	//				musicPlayer->AddScore();
	//				isUp = false;
	//				isGood = true;
	//			}
	//			else if ((*iter)->getType() == space && isSpace)
	//			{
	//				iter = directions.erase(iter);
	//				musicPlayer->AddScore();
	//				isSpace = false;
	//				isGood = true;
	//			}
	//			else if ((*iter)->getType() == down && isDown)
	//			{
	//				iter = directions.erase(iter);
	//				musicPlayer->AddScore();
	//				musicPlayer->AddScore();
	//				isDown = false;
	//				isGood = true;
	//			}
	//			else if ((*iter)->getType() == right && isRight)
	//			{
	//				iter = directions.erase(iter);
	//				musicPlayer->AddScore();
	//				isRight = false;
	//				isGood = true;
	//			}

	//			else
	//				iter++;

	//		}
	//		else {
	//			iter++;
	//		}

	//	}

	//	//
	//	for (auto iter = directions.begin(); iter != directions.end();)
	//	{
	//		if ((*iter)->getPosY() > 710)
	//		{
	//			iter = directions.erase(iter);
	//			musicPlayer->MinusHp();
	//			isMiss = true;
	//		}
	//		else
	//		{
	//			(*iter)->Update();
	//			iter++;
	//		}
	//	}

	//}


}
void GameEntityManager::musicStageRender()
{
	/*for (int i = 0; i < directions.size(); i++) {
		directions[i]->Render();
	}*/

}

void GameEntityManager::rspStageUpdate()
{

	//if (!rspPlayer->getIsClick())
	//{

	//	if (!stop)
	//	{
	//		int a = computer - (rspPlayer)->type;
	//		int result = (computer - (rspPlayer->type) + 2) % 3;
	//		//���а�����
	//		switch (result)
	//		{
	//		case 0://��
	//			rspPlayer->result = rspPlayer->lose;
	//			rspPlayer->computerType = computer;
	//			rspPlayer->isDead = (true);
	//			break;
	//		case 1://�̱�
	//			rspPlayer->result = rspPlayer->win;
	//			rspPlayer->computerType = computer;
	//			rspPlayer->score += 1;
	//			break;
	//		case 2://���
	//			rspPlayer->result = rspPlayer->draw;
	//			rspPlayer->computerType = computer;
	//			break;
	//		default:
	//			break;
	//		}

	//		stop = true;
	//	}


	//	time++;
	//	if (time > 100)
	//	{
	//		stop = false;
	//		rspPlayer->setIsClick(true);
	//		time = 0;
	//		computer = rand() % 3;
	//	}
	//}
	//else
	//{

	//}

}