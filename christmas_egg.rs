fn rot(c: (f32, f32), deg: f32) -> (f32, f32){
    let deg = deg.to_radians();
    (
    (c.0 * deg.cos()) - (c.1 * deg.sin()),
    (c.0 * deg.sin()) + (c.1 * deg.cos())
    )
}

fn main() {
    let mut arr: [[char; 40]; 40] = [['`'; 40]; 40];
    let half: f32 = 20.0;

    //mult y
    //0.0 - 0.5 -> 0.0 - 0.8
    let cor: (f32, f32) = (-half + 1.0, 0.0);
    println!("{:?}", cor);
    for deg in 0..180 {
        let (x, y) = rot(cor, deg as f32); 
        let (x, y) = (x, (y * 1.5) + (half/2.0));
        arr[(x+half) as usize][(y+half) as usize] = '*'; 
    }
    
    //mult y
    //0.5 - 1.0 -> 0.8 - 1.0
    let cor: (f32, f32) = (half - 1.0, 0.0);
    println!("{:?}", cor);
    for deg in 0..180 {
        let (x, y) = rot(cor, deg as f32);
        let (x, y) = (x, (y / 1.5) + 7.0);
        arr[(x+half) as usize][(y+half) as usize] = '*';   
    }

    //wypełnianie
    let mut fill = false;
    for y in 0..half as usize * 2 {
        for x in 0..half as usize * 2 {
            if fill == true {
                if arr[x][y] == '*' {
                    fill = false;
                    break;
                }
                else {
                    arr[x][y] = '#';
                }
            }
            if arr[x][y] == '*' {
                fill = true;
                if arr[x+1][y] == '*' {
                    fill = false;
                    break;
                }
                continue;
            }
        }
    }
    

    for y in 0..half as usize*2 {
        for x in 0..half as usize*2 {
            print!("{} ", arr[x][y]);
        }
        println!();
    }
}
