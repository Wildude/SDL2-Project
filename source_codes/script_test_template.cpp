// script processing test template
// tests a class made for script processing
#include "../Headers/Basic.hpp" // contains standarg template libraries
#include "../Headers/scriptProcessor.hpp"
int main(){
    script scr("../Files/scripts/script_template.lua");
    cout << " player name: " << scr.getglobal("player") << endl;
    cout << " player health: " << scr.getglobal("health", "number") << endl;
    cout << " player state: " << scr.getglobal("alive", "boolean") << endl;
    cout << " before function calling process\n";
    if(!scr.getglobalFunc("killPlayer"))cout << " func killPlayer not found\n";
    cout << " type of top: " << scr.gettype() << endl;
    scr.newtab();
    cout << " type of top: " << scr.gettype() << endl;
    scr.pushstr("Firaol");
    cout << " type of top: " << scr.gettype() << endl;
    scr.setfield("playerName", -2);
    cout << " type of top: " << scr.gettype() << endl;
    scr.pushnum(100);
    cout << " type of top: " << scr.gettype() << endl;
    scr.setfield("health", -2);
    cout << " type of top: " << scr.gettype() << endl;
    scr.pushbool(1);
    cout << " type of top: " << scr.gettype() << endl;
    scr.setfield("alive", -2);
    cout << " type of top: " << scr.gettype() << endl;
    scr.checkRunStatus(1, 1);
    cout << " type of top: " << scr.gettype() << endl;
    cout << " returned table contents: \n";
    scr.getfield("playerName");
    cout << " playerName: " << scr.tostr() << endl;
    scr.pop();
    cout << " playerHealth: " << scr.tonum() << endl;
    scr.pop();
    cout << " playerStatus: " << scr.tobool() << endl;
    scr.pop();
}