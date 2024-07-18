mod area_module;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let length: u32 = args[1].parse().expect("Введите число!");
    let width: u32 = args[2].parse().expect("Введите число!");

    let area = area_module::get_area(length, width);

    println!("Площадь прямоугольника равна {} квадратных единиц.", area);
}

#[test]
fn it_works() {
    assert_eq!(area_module::get_area(908, 293), 266044);
}