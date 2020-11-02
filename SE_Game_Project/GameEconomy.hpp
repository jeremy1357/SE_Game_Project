//
//  GameEconomy.hpp
//  game economy
//
//  Created by Deonte Daniels on 10/9/20.
//

#ifndef GameEconomy_hpp
#define GameEconomy_hpp

#include <stdio.h>
#include <string>
#include <vector>

// struct that contains game economy items
struct Item{
    std::string Name;
    int Cost;
    int SellCost;
    int Armor;
};
// class that monitors game economy
class GameEconomy
{
public:
    bool Buy_Item(int& playerMoney, std::string item);
    bool Insufficient_Funds(int& playerMoney, int price);
    void Zombie_Reward(int& playerMoney, std::string size);
    std::vector<Item> itemList;
    void init(std::string path);
    GameEconomy();
    ~GameEconomy();
};
#endif /* GameEconomy_hpp */
