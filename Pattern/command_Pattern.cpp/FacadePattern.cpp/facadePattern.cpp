#include<iostream>
using namespace std;

// Subsystems
class powerSupply{
    public:
        void providePower(){
            cout<<" Power Supply: Providing power..."<<endl;
        }
};
class CoolingSystem{
    public:
        void startFans(){
            cout<<"Cooling system:Fans started..."<< endl;
        }
};
class CPU{
    public:
        void initialize(){
            cout<<"CPU : Initialization started..."<<endl;
        }
};
class Memory{
    public:
        void selfTest(){
            cout<<"Memory: Self test passed..."<<endl;
        }
};
class HardDrive{
    public:
        void spinUp(){
            cout<<"Hard Drive: Spinning up...."<<endl;
        }
};
class BIOS{
    public:
        void boot(CPU& cpu, Memory& memory){
            cout<<"BIOS:Booting CPU and memory checks.."<<endl;
            cpu.initialize();
            memory.selfTest();
        }
};
class OperatingSystem{
    public:
        void load(){
            cout<<" Operating system:Loading into memory..."<<endl;
        }
};
// Facade
class ComputerFacade{
    private:
        powerSupply powerSupply;
        CoolingSystem CoolingSystem;
        CPU cpu;
        Memory memory;
        HardDrive HardDrive;
        BIOS bios;
        OperatingSystem os;
    public:
        void startComputer(){
            cout<<"---Starting computer---"<<endl;
            powerSupply.providePower();
            CoolingSystem.startFans();
            bios.boot(cpu,memory);
            HardDrive.spinUp();
            os.load();
            cout<<"Computer booted successfully"<<endl;
        }
};
// Client
int main(){
    ComputerFacade computer;
    computer.startComputer();

    return 0;
}