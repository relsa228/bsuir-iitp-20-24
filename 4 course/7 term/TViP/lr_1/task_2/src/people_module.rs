pub fn people_fn(people: Vec<(String, String, u32)>) -> Vec<f32> {
    println!("\nСписок людей:");
    for person in &people {
        println!("{} {} {}", person.1, person.0, person.2);
    }

    let min_age: f32 = *people.iter().map(|(_, _, age)| age).min().unwrap() as f32;
    let max_age: f32 = *people.iter().map(|(_, _, age)| age).max().unwrap() as f32;
    let avg_age: f32 = people.iter().map(|(_, _, age)| *age as f32).sum::<f32>() / people.len() as f32;

    return vec![min_age, max_age, avg_age];
}