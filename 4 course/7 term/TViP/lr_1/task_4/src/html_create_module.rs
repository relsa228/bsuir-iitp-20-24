use std::fs::File;
use std::io::prelude::*;

pub fn html_create(target_folder: String) {
    let mut html = String::new();

    html.push_str("<html>\n");
    html.push_str("<head>\n");
    html.push_str("<style>\n");
    html.push_str("table {\n");
    html.push_str("  border-collapse: collapse;\n");
    html.push_str("  width: 100%;\n");
    html.push_str("}\n");
    html.push_str("td, th {\n");
    html.push_str("  border: 1px solid black;\n");
    html.push_str("  padding: 8px;\n"); 
    html.push_str("  border: none;\n");
    html.push_str("}\n");

    let num_rows = 1000;
    let min_color = 255;
    let max_color = 0;

    for i in 0..num_rows {
        let color = min_color + (max_color - min_color) * i / num_rows;
        let row_color = format!("rgb({}, {}, {})", color, color, color);
        html.push_str(&format!("tr:nth-child({}) {{ background-color: {} }}\n", i + 1, row_color));
    }

    html.push_str("</style>\n");
    html.push_str("</head>\n");
    html.push_str("<body>\n");

    html.push_str("<table>\n");
    for _i in 0..num_rows {
        html.push_str("<tr>\n");
        for _j in 0..5 {
            html.push_str(&format!("<td></td>\n"));
        }
        html.push_str("</tr>\n");
    }
    html.push_str("</table>\n");

    html.push_str("</body>\n");
    html.push_str("</html>\n");

    let mut file = File::create(target_folder + "table.html").expect("Failed to create file");
    file.write_all(html.as_bytes()).expect("Failed to write to file");

    println!("HTML-файл с таблицей был успешно сгенерирован.");
}