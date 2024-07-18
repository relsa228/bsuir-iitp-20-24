mod network_download_module;


#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    let url: &str = &args[1];
    let save: &str = &args[2];
    let extension: &str = &args[3];
    network_download_module::download(url.to_string(), save.to_string(), extension).await?;
    return Ok(());
}

#[tokio::test]
async fn it_works() {
    let test_str = "Utilitatis causa amicitia est quaesita.\nLorem ipsum dolor sit amet, consectetur adipiscing elit. Collatio igitur ista te nihil iuvat. Honesta oratio, Socratica, Platonis etiam. Primum in nostrane potestate est, quid meminerimus? Duo Reges: constructio interrete. Quid, si etiam iucunda memoria est praeteritorum malorum? Si quidem, inquit, tollerem, sed relinquo. An nisi populari fama?\n\nQuamquam id quidem licebit iis existimare, qui legerint. Summum a vobis bonum voluptas dicitur. At hoc in eo M. Refert tamen, quo modo. Quid sequatur, quid repugnet, vident. Iam id ipsum absurdum, maximum malum neglegi.";
    
    let _ = std::fs::create_dir_all("/home/test");
    let _ = network_download_module::download("https://filesamples.com/samples/document/txt/sample1.txt".to_string(), "/home/test".to_string(), "txt").await;

    let contents_s= std::fs::read_to_string("/home/test/output.txt").expect("Error");

    let _ = std::fs::remove_dir_all("/home/test");
    
    assert_eq!(test_str, contents_s);
}