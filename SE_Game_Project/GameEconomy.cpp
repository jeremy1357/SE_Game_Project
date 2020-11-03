//
//  GameEconomy.cpp
//  game economy
//
//  Created by Deonte Daniels on 10/9/20.
//

#include "GameEconomy.hpp"
#include <iostream>
#include <fstream>
#include <cctype>

// intialize items list
void GameEconomy::init(std::string path)
{
    std::fstream File;
    std::string data;
    int index = 0;
    // append location of items onto path
    // need to change / to \\ for Windows
    path.append("Resources/Items/items.txt");
    File.open(path);
    if(File.is_open())
    {
        // While not end of file
        while(File>>data)
        {
            // determine if name or value
            if(!std::isdigit(data[0]))
            {
                // enter name
                itemList.push_back({data});
                // next value for item
                File>>data;
                if(std::isdigit(data[0]))
                {
                    itemList[index].Cost = stoi(data);
                    File>>data;
                    if(std::isdigit(data[0]))
                    {
                        itemList[index].SellCost = stoi(data);
                    }
                    File>>data;
                }
                index++;
            }
            else{
                File>>data;
            }
        }
    }
    else{
        std::cout<<"File could not be opened"<<std::endl;
    }
    
}
// subtracts money after buying item and returns true
bool GameEconomy::Buy_Item(int& playerMoney,std::string item)
{
    for(int index = 0;index<itemList.size();index++)
    {
        if(itemList[index].Name == item)
        {
            if(!(Insufficient_Funds(playerMoney,itemList[index].Cost)))
               {
                playerMoney -= itemList[index].Cost;
                return true;
                }
        }
    }
    return false;
    
}

// determine if player has enough money
bool GameEconomy::Insufficient_Funds(int& playerMoney, int price)
{
    if(playerMoney<price)
        return true;
    else
        return false;
}

// adds money after killing
void GameEconomy::Zombie_Reward(int& playerMoney, std::string zombie)
{
    for(int index = 0;index<itemList.size();index++)
    {
        if(itemList[index].Name == zombie)
        {
                playerMoney += itemList[index].SellCost;
        }
    }
}

// default constructor
GameEconomy::GameEconomy()
{
    std::cout<<"Game Economy made"<<std::endl;
}
// default deconstructor
GameEconomy::~GameEconomy()
{
    std::cout<<"Game Economy deleted"<<std::endl;
}

