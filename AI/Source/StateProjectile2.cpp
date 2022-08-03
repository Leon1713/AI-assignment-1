#include "StateProjectile2.h"
#include "SceneData.h"
#include "SceneTurn.h"

static const float PROJECTILE_SPEED = 100;
static const float HUNGRY_SPEED = 4.f;

StatesSeekProjectile2::StatesSeekProjectile2(const std::string& stateID, GameObject* go)
	: State(stateID),
	m_go(go)
{
}

StatesSeekProjectile2::~StatesSeekProjectile2()
{

}

void StatesSeekProjectile2::Enter()
{
	m_go->moveSpeed = PROJECTILE_SPEED;
	m_go->nearest = NULL;
}

void StatesSeekProjectile2::Update(double dt)
{
	//std::cout << "Seeking" << '\n';
	static float time = 0;
	static bool moved = 0;
	if (!m_go->active)
		return;

	m_go->moveSpeed = PROJECTILE_SPEED;
	m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
	if (m_go->nearest && m_go->nearest->active)
	{
		 m_go->target = m_go->nearest->pos; // update with new target
		 moved = 1;
		 Vector3 dir = m_go->target - m_go->pos;
		 float dirL = dir.Length(); // DEBUG
		if (dir.Length() < m_go->moveSpeed * dt)// hit
		{
			m_go->sm->SetNextState("HitProjectile2");
		}
	}
	else if (moved)
	{
		m_go->nearest = nullptr;
		m_go->active = false;
	}
	else
	{
		if (time >= .5f) {
			PostOffice::GetInstance()->Send("Scene", new MessageWRU(m_go, MessageWRU::SEARCH_TYPE::NEAREST_ENEMY_BASE2, 0));
			time = 0;
		}
	}
	time += dt * SceneData::GetInstance()->getSpeed();
}

void StatesSeekProjectile2::Exit()
{

}






StateHitProjectile2::StateHitProjectile2(const std::string& stateID, GameObject* go)
	: State(stateID),
	m_go(go)
{

}

StateHitProjectile2::~StateHitProjectile2()
{

}

void StateHitProjectile2::Enter()
{
	
}

void StateHitProjectile2::Update(double dt)
{
	//std::cout << "Hit" << '\n';

	if (!m_go->active)
		return;

	if (m_go->nearest) {
		if (!m_go->nearest->active)
		{
			m_go->nearest = nullptr;
			m_go->active = false;
		}
		else if (m_go->nearest->Health > 0) {
			m_go->nearest->Health -= 3.f;
			m_go->active = false;
			m_go->nearest = nullptr;
			//delete m_go;
		}
		/*if (m_go->nearest->Health <= 0.f)
		{
			m_go->nearest = nullptr;
		}*/
	}
	if(m_go->nearest == nullptr)
	{
		//m_go->nearest = NULL;
		m_go->active = false;
		m_go->sm->SetNextState("SeekProjectile2");
	}
			
	
}

void StateHitProjectile2::Exit()
{

}


