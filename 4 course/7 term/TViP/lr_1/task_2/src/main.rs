use std::io;

mod people_module;
use people_module::people_fn;


fn main() {
    let mut people: Vec<(String, String, u32)> = Vec::new();

    loop {
        println!("Введите имя:");
        let mut first_name = String::new();
        io::stdin().read_line(&mut first_name).expect("Не удалось прочитать имя");

        println!("Введите фамилию:");
        let mut last_name = String::new();
        io::stdin().read_line(&mut last_name).expect("Не удалось прочитать фамилию");

        println!("Введите возраст:");
        let mut age = String::new();
        io::stdin().read_line(&mut age).expect("Не удалось прочитать возраст");

        let first_name = first_name.trim().to_string();
        let last_name = last_name.trim().to_string();
        let age: u32 = age.trim().parse().expect("Введите число");

        people.push((first_name, last_name, age));

        println!("Продолжить ввод? (y/n)");
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Не удалось прочитать ввод");
        if input.trim() != "y" {
            break;
        }
    }

    let out = people_fn(people);

    println!("\nСамый малый возраст: {}", out[0]);
    println!("Самый большой возраст: {}", out[1]);
    println!("Средний возраст: {:.2}", out[2]);
}

#[test]
fn it_works() {
    let out = people_fn(vec![("name_1".to_string(), "sname_1".to_string(), 41 as u32), ("name_2".to_string(), "sname_2".to_string(), 12 as u32), ("name_3".to_string(), "sname_3".to_string(), 181 as u32)]);
    assert_eq!(out, [12 as f32, 181 as f32, 78 as f32]);
}