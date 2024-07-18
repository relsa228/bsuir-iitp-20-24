extern crate reqwest;
use std::io;
use std::fs::OpenOptions;

pub async fn download(request_link: String, target_folder: String, doc_type: &str) -> Result<(), Box<dyn std::error::Error>> {
    let resp = reqwest::get(request_link).await?;
    
    let mut out = OpenOptions::new()
        .write(true)
        .create(true)
        .open(target_folder + "/output." + doc_type)
        .expect("failed to create file");
    io::copy(&mut resp.bytes().await?.as_ref(), &mut out)?;
    return Ok(());
}
