//
//  GameEconomy.hpp
//  game economy
//
//  Created by Deonte Daniels on 10/9/20.
//

#ifndef GameEconomy_hpp
#define GameEconomy_hpp

#include <string>
#include <vector>

// struct that contains game economy items
struct Item {
    int Type;
    std::string Name;
    int Cost;
    int SellCost;
    int Armor;
    int damage;
    int bulletsPerShot;
    bool isEquipped = false;
    int healthRegen;
};

// class that monitors game economy
class GameEconomy
{
public:
    Item Buy_Item(int& playerMoney, std::string item);
    Item get_item(const std::string& itemName);
    bool Insufficient_Funds(int& playerMoney, int price);
    void Zombie_Reward(int& playerMoney);
    std::vector<Item> itemList;
    void init(std::string path, int reward);
    GameEconomy();
    ~GameEconomy();
    int zombieKill;

};
#endif /* GameEconomy_hpp */
