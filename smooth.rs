
/*
 * /""\
 * |  |
 * |  |
 * \__/
 * 
 *
 * * * * * * * * * * * * */ 
//
//  #
//
// /""\
// \__/
//
//   ##
//   #
//    
// /""""""\
// |   ___/
// |  | <- umm, that may be a slight problem
// \__/

// , - special separator
// ; - section separator
//
// [num] - amount of material
// $ - SPECIAL
// o - ORE: _
// . - AIR (not ore)
// = - PATH (not ore)
// # - HARD_WALL
// I - IRON 
// G - GOLD
// A - AETHERIUM

//For-later ideas:
    //cascading meaningfull text haha
    //  50 by 25; 13 air, 2 Iron Ore, 3 air, 2 modified enemies with: 20 attack, 30 health, 2 speed; of type "Zombie"
    /*let cmt: String = "50x25;13.2oI3.2em:a20,h30,s2;Z".to_string();
    for c in cmt.chars() {
    }*/
//

const X: usize = 50;
const Y: usize = 25;
const Textures: [[char; 8]; 4] = [
   //el    0          1         2         3 

     [  '/','"',   '|','.',  '"','"',  '.','.'  ], //x0
     
     [  '"','\\',  '.','|',  '"','"',  '.','.'  ], //x1
     
     [  '\\','_',  '|','.',  '_','_',  '.','.'  ], //x2

     [  '_','/',   '.','|',  '_','_',  '.','.'  ], //x3

]; // y  0   1      2   3     4   5     6   7

fn main(){
    let mut screen: [[char; Y]; X] = [['.'; Y]; X];
    let mut render: [[char; (Y*2)]; (X*4)] = [['.'; (Y*2)]; (X*4)];
    
    //i - texture part 0/1
    //x, y - position on my matrix
    //access by [x][y*2+i] for example
    screen[10][10] = '#';

    screen[12][10] = '#';
    screen[13][10] = '#';

    screen[15][10] = '#';
    screen[16][10] = '#';
    screen[16][9] = '#';

    screen[18][10] = '#';
    screen[19][10] = '#';
    screen[19][11] = '#';

    /* 2 # # #
     * 1 # # #
     * 0 # # #
     *   0 1 2
     */
    
    //No threads yet, wait for rusty-caves
    
    //+1 -1 makes map smaller but saves shit ton of computational power

    for y in 1..Y-1 {
        for x in 1..X-1 { 
            if screen[x][y] == '.' {
                continue;
            }
    
            let curr = screen[x][y]; 
            
            //input matrix
            let mut ch_x: [bool; 4] = [false; 4];
            let mut ch_y: [bool; 4] = [false; 4];
            
            //Checked! This is bug-free
            if screen[x-1][y] == curr {
                ch_x[0] = true;
                ch_x[2] = true;
            }
            if screen[x+1][y] == curr {
                ch_x[1] = true; 
                ch_x[3] = true;
            }
            if screen[x][y-1] == curr {
                ch_y[2] = true;
                ch_y[3] = true;
            }
            if screen[x][y+1] == curr {
                ch_y[0] = true;
                ch_y[1] = true;
            }   
            
            //NOW calculating each corner, 
            //sadly, coudln't find formula

            //LU corner
            for corner_y in 0..2 {
                for corner_x in 0..2 {
                    let set = corner_x+(corner_y*2);
                    let mut el: usize = 3;
                    
                    //This is also correct, i guess?
                    //Still not sure, but lets igore 
                    //these few lines for a moment 
                    if ch_x[set] && ch_y[set] {
                        el = 3;
                    }
                    if ch_x[set] && !ch_y[set] {
                        el = 2;
                    }
                    if !ch_x[set] && ch_y[set] {
                        el = 1;
                    }
                    if !ch_x[set] && !ch_y[set] {
                        el = 0;
                    }
                    
                    //     el  0          1         2         3       //SET
                    /*   [  '/','"',  '|','.',  '"','"',  '.','.'  ], //x0
                         [  '"','\',  '.','|',  '"','"',  '.','.'  ], //x1
                         [  '\','_',  '|','.',  '_','_',  '.','.'  ], //x2
                         [  '_','/',  '.','|',  '_','_',  '.','.'  ], //x3
                    ]; // y  0   1      2   3     4   5     6   7*/


                    //                            this adjustment
                    //                            is neccesarry            x    y
                    render[x*4+(corner_x*2)][y*2+(1-corner_y)] = Textures[set][el*2];        
                    render[x*4+(corner_x*2)+1][y*2+(1-corner_y)] = Textures[set][el*2+1];
                        
                    
                }
            }
        }  
    }
    println!("{} x {}", X, Y);
    for y in 0..Y {
        for x in 0..X {
            //                    inversion
            print!("{} ", screen[x][Y-y-1]);
        }
        println!();
    }

    println!();
    println!("{} x {}", X*4, Y*2);
    for y in 0..Y*2 {
        for x in 0..X*4 {
            
            //println!("{} {}", x, y);
            
            if render[x][Y*2-y-1] == '.' {
                print!(" ");
                continue;
            }
            
            print!("{}", render[x][Y*2-y-1]);
        
        }
        println!();
    }
}
