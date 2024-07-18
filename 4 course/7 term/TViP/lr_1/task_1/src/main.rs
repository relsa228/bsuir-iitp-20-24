use rand::Rng;

fn main() {
    println!("Hello, world!");
    println!("Andhiagain!");

    let num_exclamation_marks = rand::thread_rng().gen_range(5..=50);
    let exclamation_marks: String = std::iter::repeat('!').take(num_exclamation_marks).collect();
    println!("{}", exclamation_marks);
}

#[test]
fn it_works() {
    for _ in 0..1000 {
        let num_exclamation_marks = rand::thread_rng().gen_range(5..=50);
        assert!(5 <= num_exclamation_marks && num_exclamation_marks <= 50);
    }
}