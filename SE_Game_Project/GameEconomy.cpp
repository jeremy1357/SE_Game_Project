//
//  GameEconomy.cpp
//  game economy
//
//  Created by Deonte Daniels on 10/9/20.
//

#include "GameEconomy.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cctype>

// intialize items list
void GameEconomy::init(std::string path, int reward)
{
    std::fstream File;
    std::string data;
    // set price of zombies
    zombieKill = reward;
    // append location of items onto path
    // need to change / to \\ for Windows
    path.append("Resources/Items/items.txt");
    File.open(path);
    if (File.is_open())
    {
        // While not end of file
        while (File >> data)
        {
            // initialize item in array
            itemList.push_back(Item());
            // Name item
            itemList.back().Type = stoi(data);
            // next value for item
            File >> data;
            itemList.back().Name = data;
            // next value for item
            File >> data;
            itemList.back().Cost = stoi(data);
            // next value for item
            File >> data;
            itemList.back().SellCost = stoi(data);
            // next value for item
            File >> data;
            itemList.back().Armor = stoi(data);
            // gun damage
            File >> data;
            itemList.back().damage = stoi(data);
            // gun bullets
            File >> data;
            itemList.back().bulletsPerShot = stoi(data);

        }
    }
    else {
        std::cout << "File could not be opened" << std::endl;
    }
    File.close();
}
// subtracts money after buying item and returns true
Item GameEconomy::Buy_Item(int& playerMoney, std::string item)
{
    for (int index = 0; index < itemList.size(); index++)
    {
        if (itemList[index].Name == item)
        {
            if (!(Insufficient_Funds(playerMoney, itemList[index].Cost)))
            {
                playerMoney -= itemList[index].Cost;
                // return item bought
                return itemList[index];
            }
        }
    }
    // return empty object
    return Item();

}

Item GameEconomy::get_item(const std::string& itemName)
{
    for (auto& it : itemList) {
        if (it.Name == itemName) {
            return it;
        }
    }
    return Item();
}

// determine if player has enough money
bool GameEconomy::Insufficient_Funds(int& playerMoney, int price)
{
    if (playerMoney >= price)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// adds money after killing
void GameEconomy::Zombie_Reward(int& playerMoney)
{
    playerMoney += zombieKill;
}

// default constructor
GameEconomy::GameEconomy()
{
    std::cout << "Game Economy made" << std::endl;
}
// default deconstructor
GameEconomy::~GameEconomy()
{
    std::cout << "Game Economy deleted" << std::endl;
}

