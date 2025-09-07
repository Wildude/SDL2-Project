// script processing test template
// tests a class made for script processing
#include <iostream>
#include <scriptProcessor.hpp>
int main(){
    script scr("../Files/scripts/script_template.lua");
    std::cout << " player name: " << scr.getglobal("player") << std::endl;
    std::cout << " player health: " << scr.getglobal("health", "number") << std::endl;
    std::cout << " player state: " << scr.getglobal("alive", "boolean") << std::endl;
    std::cout << " before function calling process\n";
    if(!scr.getglobalFunc("killPlayer"))std::cout << " func killPlayer not found\n";
    std::cout << " type of top: " << scr.gettype() << std::endl;
    scr.newtab();
    std::cout << " type of top: " << scr.gettype() << std::endl;
    scr.pushstr("Firaol");
    std::cout << " type of top: " << scr.gettype() << std::endl;
    scr.setfield("playerName", -2);
    std::cout << " type of top: " << scr.gettype() << std::endl;
    scr.pushnum(100);
    std::cout << " type of top: " << scr.gettype() << std::endl;
    scr.setfield("health", -2);
    std::cout << " type of top: " << scr.gettype() << std::endl;
    scr.pushbool(1);
    std::cout << " type of top: " << scr.gettype() << std::endl;
    scr.setfield("alive", -2);
    std::cout << " type of top: " << scr.gettype() << std::endl;
    scr.checkRunStatus(1, 1);
    std::cout << " type of top: " << scr.gettype() << std::endl;
    std::cout << " returned table contents: \n";
    scr.getfield("playerName");
    std::cout << " playerName: " << scr.tostr() << std::endl;
    scr.pop();
    std::cout << " playerHealth: " << scr.tonum() << std::endl;
    scr.pop();
    std::cout << " playerStatus: " << scr.tobool() << std::endl;
    scr.pop();
}