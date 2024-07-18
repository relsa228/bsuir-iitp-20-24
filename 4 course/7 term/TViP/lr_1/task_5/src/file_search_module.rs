use std::fs;
use std::path::Path;

pub fn find_files_with_extension(folder_path: &Path, extension: &str) -> Vec<std::path::PathBuf> {
    let mut files = Vec::new();

    if let Ok(entries) = fs::read_dir(folder_path) {
        for entry in entries {
            if let Ok(entry) = entry {
                let path = entry.path();

                if path.is_file() && path.extension().map_or(false, |ext| ext == extension) {
                    files.push(path);
                } else if path.is_dir() {
                    let subfolder_files = find_files_with_extension(&path, extension);
                    files.extend(subfolder_files);
                }
            }
        }
    }

    files
}