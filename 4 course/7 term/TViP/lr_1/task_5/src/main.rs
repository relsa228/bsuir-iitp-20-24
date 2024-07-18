use std::path::Path;

mod file_search_module;
pub use file_search_module::find_files_with_extension;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let folder_path: &str = &args[1];
    let extension: &str = &args[2];
    
    let path = Path::new(folder_path);

    let files = find_files_with_extension(path, extension);

    for file in files {
        println!("{}", file.display());
    }
}

#[test]
fn it_works() {
    let _ = std::fs::create_dir_all("/home/test");
    let _ = std::fs::create_dir_all("/home/test/recursive");

    let _ = std::fs::File::create("/home/test/test1.txt");
    let _ = std::fs::File::create("/home/test/recursive/test2.txt");
    let _ = std::fs::File::create("/home/test/recursive/test3.pdf");
    let _ = std::fs::File::create("/home/test/recursive/test4.txt");

    let control_vec: Vec<std::path::PathBuf> = vec!["/home/test/test1.txt".into(), "/home/test/recursive/test2.txt".into(), "/home/test/recursive/test4.txt".into()];

    let _ = std::fs::remove_dir_all("/home/test");
    
    assert_eq!(find_files_with_extension(Path::new("/home/test"), "txt"), control_vec);
}