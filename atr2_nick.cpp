#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int print_code(int n, int p) {

    int i;
    std::cout << std::hex << p << ": ";
    for (i = 0; max_op; i++) {
        cout << setfill("0") << setw(5) << robot[n]^.code[p].op[i] << " ";
    }
    cout << " = ";
    for (i = 0; max_op; i++) {
        std::cout << std::hex << robot[n]^.code[p].op[i] << "h" << "\n\n";
    }

}

int check_plen(int plen) {

    if (plen>maxcode) {
        prog_error(16,#13#10+"Maximum program length exceeded, (Limit: "+ cstr(maxcode+1)+" compiled lines)");
}

int reset_software(int n) {

    int i;

//     with robot[n]^ do

       for (i; max_ram; i++ to max_ram){
             ram[i]:=0;
     }

       n.ram[71] = 768;
       n.thd = hd;
       n.tspd = 0;
       n.scanarc = 8;
       n.shift = 0;
       n.err = 0;
       n.overburn = false;
       n.keepshift = false;
       n.ip = 0;
       n.accuracy = 0;
       n.meters = 0;
       n.delay_left = 0;
       n.time_left = 0;
       n.shields_up = false;

}

int init_robot(int n) {

    int i,j,k,l;

    robot[n].wins = 0;
    robot[n].trials = 0;
    robot[n].kills = 0;
    robot[n].deaths = 0;
    robot[n].shots_fired = 0;
    robot[n].match_shots = 0;
    robot[n].hits = 0;
    robot[n].damage_total = 0;
    robot[n].cycles_lived = 0;
    robot[n].error_count = 0;
    robot[n].plen = 0;
    robot[n].max_time = 0;
    robot[n].name = '';
    robot[n].fn = '';
    robot[n].speed = 0;
    robot[n].arc_count = 0;
    robot[n].sonar_count = 0;
    robot[n].robot_time_limit = 0;
    robot[n].scanrange = 1500;
    robot[n].shotstrength = 1;
    robot[n].damageadj = 1;
    robot[n].speedadj = 1;
    robot[n].mines = 0;

    robot.config.scanner = 5;
    robot.config.weapon = 2;
    robot.config.armor = 2;
    robot.config.engine = 2;
    robot.config.heatsinks = 1;
    robot.config.shield = 0;
    robot.config.mines = 0;

    for (i = 0; i < max_ram; i++) {
        ram[i] = 0;
    }

    ram[71] = 768;

    for (i = 0; i < max_code; i++) {
        for (k = 0; k < max_op; k++) {
            code[i].op[k] = 0;
        }
    }
   reset_hardware(n);
   reset_software(n);
}





void shutdown() {

    int i,j,k;

// graph_mode(false);
    if (show_cnotice = true) {

//   textcolor(3);
    cout << progname << " " << version << " ";
    cout << cnotice1 << "\n";
    cout << cnotice2 << "\n";
    cout << cnotice3 << "\n";
  }

// textcolor(7);
    if (registered = false) {
//        textcolor(4);
        cout << "Unregistered version";
    } else {
        cout << "Registered to: " << reg_name;
    }
// textcolor(7);
    cout << "\n";
    if (logging_errors = true) {

    for (i = 0; i < num_robots; i++){
        cout << "Robot error-log created: " << robot[i].base_name(fn) << ".ERR";
        close(errorlog);
    }
   exit();
}












