/* 
 * File:   MyManager.cpp
 * Author: Akela1101
 * 
 * Created on 13 Январь 2011 г., 21:23
 */

#include "MyManager.h"


namespace Sample1
{
	using namespace std;

MyManager::MyManager()
{
}

MyManager::~MyManager()
{
}

void MyManager::AddEntityManager(sh_p<EntityManager> entityManager)
{
	entityManagers.push_back(entityManager);
}

}