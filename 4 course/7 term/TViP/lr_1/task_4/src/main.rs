mod html_create_module;

fn main() {
    html_create_module::html_create("/home/relsa/Загрузки/".to_string());
}

#[test]
fn it_works() {
    let _ = std::fs::create_dir_all("/home/test");

    html_create_module::html_create("/home/test/".to_string());

    let contents= std::fs::read_to_string("/home/test/table.html").expect("Error");

    assert!(contents.contains("tr:nth-child(1) { background-color: rgb(255, 255, 255) }"));
    assert!(contents.contains("tr:nth-child(1000) { background-color: rgb(1, 1, 1) }"));
    assert!(contents.contains("table {\n  border-collapse: collapse;\n  width: 100%;\n}"));
    assert!(contents.contains("td, th {\n  border: 1px solid black;\n  padding: 8px;\n  border: none;\n}"));

    let _ = std::fs::remove_dir_all("/home/test");
}